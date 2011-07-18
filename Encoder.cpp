/*
 * Encoder.cpp
 *
 *  Created on: Jul 17, 2011
 *      Author: korzec
 */

#include "Encoder.h"

Encoder::Encoder() : pictureBuffer(0)
{
    coeffCube = CoeffCube(params.width, params.height, params.cubeDepth);
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
}

EncoderState Encoder::Encode()
{
    //check if enough pictures are available
    if (pictureBuffer.GetCount() >= params.cubeDepth)
    {
        int buffer = pictureBuffer.GetCount();
        //copy the pictures to the coeffCube
        PictureVector gop;
        pictureBuffer.GetGOP(params.cubeDepth, gop);
        int size = gop.size();
        assert(gop.size() == 4);
        //if we have valid gop
        if(gop.size() == params.cubeDepth)
        {
            bool ret = coeffCube.LoadGOP(gop);
            assert(ret == true);
//            coeffCube.Forward();
//            coeffCube.Split();
//            coeffCube.Synth();
//            coeffCube.Backward();
        }
        
        return PICAVAIL;
    }
    else //if not enough buffer
    {
        return NEEDBUFFER;
    }
        
}