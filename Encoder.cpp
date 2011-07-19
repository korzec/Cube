/*
 * Encoder.cpp
 *
 *  Created on: Jul 17, 2011
 *      Author: korzec
 */

#include "Encoder.h"

Encoder::Encoder() : pictureBuffer(0)
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
            assert(ret == true);
            if( coeffCube.ForwardTransform() && coeffCube.ReverseTransform())
                return PICAVAIL;
            else
                return INVALID;
        }
        else //when buffer was enough but not gop
            return INVALID;
    }
    else //if not enough buffer
    {
        return NEEDBUFFER;
    }
        
}
