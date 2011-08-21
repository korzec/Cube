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

///holds data of a frame, NOT safe to copy or assign, not for direct use
class FrameBuffer;
typedef boost::shared_ptr<FrameBuffer> FrameBufferPtr;

class FrameBuffer
{
    //TODO: use auto pointers for memory allocations
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

