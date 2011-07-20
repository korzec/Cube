/*
 * PictureBuffer.cpp
 *
 *  Created on: Jul 17, 2011
 *      Author: korzec
 */

#include "PictureBuffer.h"
//#include <algorithm>

PictureBuffer::PictureBuffer(size_t _size)
{
    if (_size < 0)
        maxSize = 0;
    else
        maxSize = _size;
}

bool PictureBuffer::Add(Picture &p)
{
    if (pictures.size() < maxSize)
    {
        pictures.push_back(p);
        return true;
    }
    else
        return false;
}

bool PictureBuffer::RemoveOldest()
{
    if (pictures.size() > 0)
    {
        pictures.erase(pictures.begin());
        return true;
    }
    else
        return false;
}

int PictureBuffer::GetCount()
{
    return pictures.size();
}

bool PictureBuffer::isNotFull()
{
    if (pictures.size() < maxSize)
    {
        return true;
    }
    else
        return false;
}

bool PictureBuffer::GetGOP(size_t size, PictureVector& gop)
{
    ///check if theres enough pictures 
    if (pictures.size() >= size)
    {
        ///copy size elements to the gop       
        gop.assign(pictures.begin(), pictures.begin() + size);
        return true;
    }
    else
        return false;
}

bool PictureBuffer::RemoveOldGOP(size_t size)
{
    if (pictures.size() >= size)
    {
        //remove last gop's pictures
        pictures.erase(pictures.begin(), pictures.begin() + size);
        return true;
    }
    else
        return false;
}

bool PictureBuffer::AddGOP(PictureVector& gop)
{
    if (maxSize - pictures.size() >= gop.size())
    {
        pictures.insert(pictures.end(), gop.begin(), gop.end());
        return true;
    }
    else
        return false;
}