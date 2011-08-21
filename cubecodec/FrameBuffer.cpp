/* 
 * File:   FrameBuffer.cpp
 * Author: korzec
 * 
 * Created on August 20, 2011, 1:13 AM
 */

#include "FrameBuffer.h"

FrameBuffer::FrameBuffer() : data(NULL), width(0), height(0)
{
    buf[0] = NULL;
    buf[1] = NULL;
    buf[2] = NULL;
}

FrameBuffer::FrameBuffer(int _width, int _height) : data(NULL), width(0), height(0)
{
    buf[0] = NULL;
    buf[1] = NULL;
    buf[2] = NULL;
    if (_width < 0 || _height < 0)
        return;
    width = _width;
    height = _height;
    int sizeY = width*height;
    int sizeU = sizeY / 4;
    int size = width * height * 3 / 2;
    data = new unsigned char [size];
    /// Set poiners to Y U V planes
    buf[0] = data;
    buf[1] = data + sizeY;
    buf[2] = data + sizeY + sizeU;
}
///reset pointers and free memory

FrameBuffer::~FrameBuffer()
{
    buf[0] = NULL;
    buf[1] = NULL;
    buf[2] = NULL;
    if (data)
        delete [] data;
    data = NULL;
}

int FrameBuffer::SizeY()
{
    return width*height;
}

int FrameBuffer::SizeU()
{
    return width * height / 4;
}

int FrameBuffer::Size()
{
    return width * height * 3 / 2;
}
