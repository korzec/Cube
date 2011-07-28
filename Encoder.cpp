/*
 * Encoder.cpp
 *
 *  Created on: Jul 17, 2011
 *      Author: korzec
 */

#include "Encoder.h"

Encoder::Encoder() : pictureBuffer(0), pictureOutputBuffer(0), pictureNumber(0)
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
    pictureBuffer = PictureBuffer(params.cubeDepth);
    pictureOutputBuffer = PictureBuffer(params.cubeDepth);
    coeffCube = CoeffCube(params.width, params.height, params.cubeDepth);
}

EncoderState Encoder::Encode()
{
    //check if enough pictures are available
    if (pictureBuffer.GetCount() >= params.cubeDepth)
    {
        //copy the pictures to the coeffCube
        PictureVector gop;
        pictureBuffer.GetGOP(params.cubeDepth, gop);
        assert(gop.size() == (size_t) params.cubeDepth);
        //if we have valid gop
        if(gop.size() == (size_t) params.cubeDepth)
        {
            bool ret = coeffCube.LoadGOP(gop);
            pictureBuffer.RemoveOldGOP(params.cubeDepth);
            assert(ret == true);
            if( coeffCube.ForwardTransform() && coeffCube.ReverseTransform())
            {
                PictureVectorPtr outputGOP = coeffCube.GetGOP();
                bool ret = pictureOutputBuffer.AddGOP(*outputGOP);
                //delete outputGOP;
                ///check if gop could have been added
                ///if not return WAIT state; or just PIC AVAILABLE ?
                ///or INVALID if there was no space for new pictures;
                if(ret == false)
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
    pictureOutputBuffer.GetGOP(params.cubeDepth, *gop );
    return gop;
}

//Picture Encoder::GetNextDecodedPicture()
//{
//    pictureOutputBuffer;
//}

bool Encoder::DeleteOldOutputGOP()
{
    return pictureOutputBuffer.RemoveOldGOP(params.cubeDepth);
}