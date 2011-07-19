/*
 * cube_codec.h
 *
 *  Created on: Jul 8, 2011
 *      Author: korzec
 */

#ifndef CUBE_CODEC_H_
#define CUBE_CODEC_H_


#include "boost/multi_array.hpp"
#include <boost/smart_ptr.hpp>
//#include <blitz/array.h>

#include <exception>
#include <iostream>

//using namespace blitz;
using namespace boost;

typedef float CoeffType;
typedef unsigned char ValueType;
typedef int PictureNumber;
typedef int CubeNumber;

class Coords3D
{
public:
    int width;
    int height;
    int depth;
    Coords3D() : width(0), height(0), depth(0)
    {
        
    }
    Coords3D(int width, int height, int depth)
    {
         this->width = width;
         this->height = height;
         this->depth = depth;
    }
};

class CubeCoords
{
public:
    Coords3D lower;
    Coords3D higher;
};

enum EncoderState
{
    PICAVAIL, NEEDBUFFER, FINISHED, INVALID
};

class CodingParams
{
public:
    int width;
    int height;

    int cubeDepth;

    int start_pos;
    int end_pos;
    bool verbose;
    bool nolocal;
    int fields_factor;

    CodingParams() : width(0), height(0), cubeDepth(4),
    start_pos(0), end_pos(-1), verbose(false), nolocal(false), fields_factor(1)
    {
    }
};

class FrameBuffer
{
public:
    /*! buffers to hold the luma and chroma data */
    unsigned char *data;
    unsigned char *buf[3];
    int width;
    int height;
    int refCount;

    FrameBuffer() : data(NULL), width(0), height(0), refCount(0)
    {
        buf[0] = NULL;
        buf[1] = NULL;
        buf[2] = NULL;
    }

    FrameBuffer(int _width, int _height) : data(NULL), width(0), height(0), refCount(0)
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

    virtual ~FrameBuffer()
    {
        buf[0] = NULL;
        buf[1] = NULL;
        buf[2] = NULL;
        delete [] data;
        data = NULL;
    }

    int SizeY()
    {
        return width*height;
    }

    int SizeU()
    {
        return width * height / 4;
    }

    int Size()
    {
        return width * height * 3 / 2;
    }

};

typedef boost::multi_array_ref<ValueType, 2 > ValueArray2Dref;
typedef boost::multi_array<CoeffType, 3 > CoeffArray3D;

//typedef boost::multi_array_ref<CoeffType, 3 > CoeffArray3Dref;
//typedef boost::shared_ptr<CoeffArray3Dref> CoeffArray3DrefPtr;


typedef boost::shared_ptr<FrameBuffer> FrameBufferPtr;
typedef boost::shared_ptr<ValueArray2Dref> ValueArray2DrefPtr;
typedef boost::shared_ptr<CoeffArray3D> CoeffArray3DPtr;

class Picture
{
public:
    ValueArray2DrefPtr arrayY;
    //ValueArray2D U;
    //ValueArray2D V;
    FrameBufferPtr frame;
    int pictureNumber;
    int width()
    {
        if (!frame)
            return 0;
        return frame->width;
    }

    int height()
    {
        if (!frame)
            return 0;
        return frame->height;
    }

    ValueArray2Dref& Y()
    {
        return *arrayY;
    }

    Picture() 
    {
        frame = FrameBufferPtr();
        //arrayY = ValueArray2DrefPtr
        //        (new ValueArray2Dref(NULL, boost::extents[0][0]));
    }

    Picture(FrameBuffer* _frame)
    {
        frame = FrameBufferPtr(_frame);
        ///dereferencing external pointer maybe produce problems with bad usage
        if (!frame || !(frame->data))
            return;
        arrayY = ValueArray2DrefPtr(new ValueArray2Dref
                (frame->buf[0], boost::extents[frame->height][frame->width]));
    }

    Picture(int width, int height)
    {
        frame = FrameBufferPtr(new FrameBuffer(width, height));
        arrayY = ValueArray2DrefPtr(new ValueArray2Dref
                (frame->buf[0], boost::extents[frame->height][frame->width]));
    }
};

typedef std::vector<Picture> PictureVector;

#include "other.h"

#endif /* CUBE_CODEC_H_ */