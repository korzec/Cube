/* 
 * File:   FrameBuffer.h
 * Author: korzec
 *
 * Created on August 20, 2011, 1:13 AM
 */

#ifndef FRAMEBUFFER_H
#define	FRAMEBUFFER_H

#include <iostream>
#include <boost/smart_ptr.hpp>

class FrameBuffer;
typedef boost::shared_ptr<FrameBuffer> FrameBufferPtr;

class FrameBuffer
{
public:
    /*! buffers to hold the luma and chroma data */
    unsigned char *data;
    unsigned char *buf[3];
    int width;
    int height;

    FrameBuffer();

    FrameBuffer(int _width, int _height);
    ///reset pointers and free memory
    virtual ~FrameBuffer();

    int SizeY();

    int SizeU();

    int Size();

};

#endif	/* FRAMEBUFFER_H */

