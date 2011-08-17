/*
 * Encoder.cpp
 *
 *  Created on: Jul 17, 2011
 *      Author: korzec
 */

#include "Encoder.h"

Encoder::Encoder() : pictureBuffer(0), pictureOutputBuffer(0), pictureNumber(0), cubeNumber(0)
{
}

bool Encoder::LoadNextPicture(Picture& picture)
{
    if (pictureBuffer.isNotFull())
    {
        pictureBuffer.Add(picture);
        return true;
    }
    else
        return false;
}

Parameters Encoder::GetParams() const
{
    return params;
}

bool Encoder::SetParams(Parameters params)
{
    this->params = params;
    pictureBuffer = PictureBuffer(params.codecParams.cubeSize.depth);
    pictureOutputBuffer = PictureBuffer(params.codecParams.cubeSize.depth);
    coeffCube.Init(params.codecParams.cubeSize, params.codecParams.levels, params.codecParams.subcubeSize);
    //check if subcubeSize divides by cube size
    if( params.codecParams.cubeSize.width % params.codecParams.subcubeSize.width != 0 ||
        params.codecParams.cubeSize.height % params.codecParams.subcubeSize.height != 0 ||
        params.codecParams.cubeSize.depth % params.codecParams.subcubeSize.depth != 0)
        return false;
    return true;
}

EncoderState Encoder::Encode()
{
    //check if enough pictures are available
    if (pictureBuffer.GetCount() >= params.codecParams.cubeSize.depth)
    {
        //copy the pictures to the coeffCube
        PictureVector gop;
        pictureBuffer.GetGOP(params.codecParams.cubeSize.depth, gop);
        assert(gop.size() == (size_t) params.codecParams.cubeSize.depth);
        //if we have valid gop
        if (gop.size() == (size_t) params.codecParams.cubeSize.depth)
        {
            cubeNumber++;
            bool ret = coeffCube.LoadGOP(gop);
            pictureBuffer.RemoveOldGOP(params.codecParams.cubeSize.depth);
            assert(ret == true);

            if (coeffCube.ForwardTransform())
            {
                if (params.analysis)
                {
                    std::stringstream ss1;
                    ss1 << OUTDIR << "tr" << cubeNumber << "cube.raw";
                    coeffCube.dumpCoeffs(ss1.str());
                    std::stringstream ss3;
                    ss3 << OUTDIR << "we" << cubeNumber << "cube.raw";
                    coeffCube.dumpWeights(ss3.str());
                }

                //coeffCube.SmoothTime();
                
                //testing: compress and decompress cube to validate
                //compress data
                CompressAll();
                DecompressAll();

                if (params.analysis)
                {
                    std::stringstream ss2;
                    ss2 << OUTDIR << "sm" << cubeNumber << "cube.raw";
                    coeffCube.dumpCoeffs(ss2.str());
                }

                coeffCube.ReverseTransform();

                PictureVectorPtr outputGOP = coeffCube.GetGOP();
                bool ret = pictureOutputBuffer.AddGOP(*outputGOP);
                //delete outputGOP;
                ///check if gop could have been added
                ///if not return WAIT state; or just PIC AVAILABLE ?
                ///or INVALID if there was no space for new pictures;
                if (ret == false)
                {
                    std::cerr << "buffer full, couldn't output pictures";
                    return INVALID;
                }
                
                
                return PICTURE_AVAILABLE;

            }
            else //transform failed
                return INVALID;
        }
        else //when buffer was enough but not gop
        {
            std::cerr << "not enough pictures in gop";
            return INVALID;
        }
    }
    else //if not enough buffer
    {
        return NEED_BUFFER;
    }

}

bool Encoder::EndOfSequence()
{
    return true;
}

PictureVectorPtr Encoder::GetDecodedGOP()
{
    PictureVectorPtr gop(new PictureVector);
    pictureOutputBuffer.GetGOP(params.codecParams.cubeSize.depth, *gop);
    return gop;
}

//Picture Encoder::GetNextDecodedPicture()
//{
//    pictureOutputBuffer;
//}

bool Encoder::DeleteOldOutputGOP()
{
    return pictureOutputBuffer.RemoveOldGOP(params.codecParams.cubeSize.depth);
}

bool Encoder::CompressSubcubes(Channel channel)
{
    SubcubeIndex* index = coeffCube.GetSubcubeIndex(channel);
    Coords3D dims = index->GetIndexDims();
    //resize packetList to fit dimensions of the Subcube array
    packetList[channel].resize(dims.width * dims.height * dims.height);

    Coords3D location;
    Subcube* subcube;

    //set up iterators
    std::deque<Packet>::iterator packetIT = packetList[channel].begin();
    WeightsMap& weightsMap = index->GetWeightsMap();
    WeightsMap::iterator weightIT = weightsMap.end();
    assert(weightsMap.size() == packetList[channel].size());
    //iterate over all subcubes and compress them
    //then add a compressed Packet to #packetList
    for (; packetIT != packetList[channel].end(); packetIT++)
    {
        weightIT--; //set iterator to next pair
        //locaiton of current subcube in the index
        location = weightIT->second->GetLocation();
        subcube = weightIT->second; //get subcube
        *packetIT = compressor.Compress(subcube->GetView(), location, channel, coeffCube.GetCubeNumber());
    }
    return true;
}

bool Encoder::CompressAll()
{
    //get indexes of all subcubes and then create a packet list with all of them
    WeightsMap* weights[NOFCHANNELS];
    WeightsMap allWeights;
    //get list of all subcubes together in a single sorted list;
    for (int i = 0; i < NOFCHANNELS; i++)
    {
        coeffCube.GetSubcubeIndex(Channel(i))->ComputeWeights();
        weights[i] = &coeffCube.GetSubcubeIndex(Channel(i))->GetWeightsMap();
        allWeights.insert(weights[i]->begin(), weights[i]->end());
    }
    //now create a list of packets
    allPackets.clear();
    
    WeightsMap::iterator iterator = allWeights.begin();
    Subcube* subcube;
    Coords3D location;
    //compress and add to list;
    for(; iterator != allWeights.end(); iterator++)
    {
        subcube = iterator->second;
        location =  subcube->GetLocation();
        allPackets.insert(PacketPair(iterator->first, 
                compressor.Compress(subcube->GetView(), location,
                                    subcube->GetChannel() , coeffCube.GetCubeNumber() )));
    }
    //here we have list of all packts sorted with weights
    return true;
}

bool Encoder::DecompressAll()
{
    //zero all values in all cube arrays
    coeffCube.ZeroAll();
    
    //for all packets in list decompress and copy to location
    PacketMap::reverse_iterator iterator = allPackets.rbegin();
    Subcube *subcube = NULL;
    CoeffArray3DPtr newArrayPtr;
    for (; iterator != allPackets.rend(); iterator++)
    {
        // get subcube to copy the data
        subcube = &coeffCube.GetSubcubeIndex(iterator->second.channel)
                ->GetSubcube(iterator->second.location);
        
        newArrayPtr = compressor.Decompress(iterator->second, params.codecParams.subcubeSize);
        subcube->CopyNewValues(newArrayPtr);
    }
    return true;
}

bool Encoder::OutputSequenceHeader(std::ostream* stream)
{
    CubeStream cubeStream(stream);
    VideoParams vparams;
    cubeStream.WriteSequenceHeader(params.codecParams, vparams);
    
    return true;
}

bool Encoder::ReadSequenceHeader(std::istream* stream)
{
    CubeStream cubeStream(stream);
    VideoParams vparams;
    return cubeStream.ReadSequenceHeader(params.codecParams, vparams);
}

bool Encoder::OutputCube(std::ostream* stream)
{
    CubeStream cubeStream(stream);
    cubeStream.WriteCubeHeader(coeffCube.GetCubeNumber());

    //write all packets with the order of weights
    PacketMap::reverse_iterator iterator = allPackets.rbegin();
    //compress and add to list;
    for(; iterator != allPackets.rend(); iterator++)
    {
        //write packet to stream
        cubeStream.WritePacket(iterator->second);
    }
    
    return true;
}

bool Encoder::ReadCube(std::istream* stream)
{
    //open file for read
    CubeStream cubeStream(stream);
    cubeStream.ReadCubeHeader(coeffCube.GetCubeNumber());
    
    //read in all packets
    //read packets until packet of new cube comes in
    Packet packet;
    allPackets.clear();
    for(int counter=0 ; cubeStream.CheckNextCube() == false; counter++ )
    {
        packet = cubeStream.ReadPacket();
        allPackets.insert(PacketPair((float)counter, packet ));
    }
    return true;
}