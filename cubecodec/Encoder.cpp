/*
 * Encoder.cpp
 *
 *  Created on: Jul 17, 2011
 *      Author: korzec
 */

#include "Encoder.h"
#include "general.h"
#include "types.h"
#include <cassert>

Encoder::Encoder() : Decoder(),  pictureInputBuffer(0)
{
}

bool Encoder::LoadNextPicture(Picture& picture)
{
    if (pictureInputBuffer.isNotFull())
    {
        pictureInputBuffer.Add(picture);
        return true;
    }
    else
        return false;
}


bool Encoder::SetParams(Parameters params)
{
    this->params = params;
    pictureInputBuffer = PictureBuffer(this->params.codecParams.cubeSize.depth);
    return Init();
}

BufferState Encoder::Encode()
{
    //check if enough pictures are available
    if (pictureInputBuffer.GetCount() >= params.codecParams.cubeSize.depth)
    {
        //copy the pictures to the coeffCube
        PictureVector gop;
        pictureInputBuffer.GetGOP(params.codecParams.cubeSize.depth, gop);
        assert(gop.size() == (size_t) params.codecParams.cubeSize.depth);
        //if we have valid gop
        if (gop.size() == (size_t) params.codecParams.cubeSize.depth)
        {
            cubeNumber++;
            bool ret = coeffCube.LoadGOP(gop);
            pictureInputBuffer.RemoveOldGOP(params.codecParams.cubeSize.depth);
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
                
                CompressAll();
                
                // get statistics for the cube
                if(params.analysis)
                {
                    SubbandList* list = coeffCube.GetSubbandList();
                    CoeffView3D* view;
                    //for each channel
                    for(int ch=0; ch < NOFCHANNELS; ch++)
                    //for each level, 
                        for(int level=0; level <= list[ch].GetLevel(); level++)
                    //for each subband
                            for(int orient = 0; orient < list[ch].SubbandCountForLevel(level); orient++)
                            {
                                //find and output statistics of subbands
                                view = &list[ch].GetSubband(level, (Orientation)orient );
                                std::stringstream name;
                                name << OUTDIR << "stats_ch" << ch << "_level"
                                        << level << "_orient" << orient <<".csv";
                                writeMap(getSymbolStatistics(*view), name.str() );
                            }
                }

                if (!params.nolocal)
                {
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
                }
                return OUTPUT_AVAILABLE;
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
                compressor->Compress(subcube->GetView(), location,
                                    subcube->GetChannel() , coeffCube.GetCubeNumber() )));
    }
    //here we have list of all packts sorted with weights
    return true;
}

bool Encoder::WriteSequenceHeader(std::ostream* stream)
{
    CubeStream cubeStream(stream);
    VideoParams vparams;
    cubeStream.WriteSequenceHeader(params.codecParams, vparams);
    
    return true;
}

bool Encoder::WriteCubeData(std::ostream* stream)
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
