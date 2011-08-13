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

CodingParams Encoder::GetParams() const
{
    return params;
}

void Encoder::SetParams(CodingParams params)
{
    this->params = params;
    pictureBuffer = PictureBuffer(params.size.depth);
    pictureOutputBuffer = PictureBuffer(params.size.depth);
    coeffCube.Init(params.size, params.levels, params.subSize);
}

EncoderState Encoder::Encode()
{
    //check if enough pictures are available
    if (pictureBuffer.GetCount() >= params.size.depth)
    {
        //copy the pictures to the coeffCube
        PictureVector gop;
        pictureBuffer.GetGOP(params.size.depth, gop);
        assert(gop.size() == (size_t) params.size.depth);
        //if we have valid gop
        if (gop.size() == (size_t) params.size.depth)
        {
            cubeNumber++;
            bool ret = coeffCube.LoadGOP(gop);
            pictureBuffer.RemoveOldGOP(params.size.depth);
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

                coeffCube.SmoothTime();

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
    pictureOutputBuffer.GetGOP(params.size.depth, *gop);
    return gop;
}

//Picture Encoder::GetNextDecodedPicture()
//{
//    pictureOutputBuffer;
//}

bool Encoder::DeleteOldOutputGOP()
{
    return pictureOutputBuffer.RemoveOldGOP(params.size.depth);
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
        *packetIT = compressor.Compress(subcube->GetView(), location);
    }
    return true;
}