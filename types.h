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

typedef int CoeffType;
typedef unsigned char ValueType;
typedef int PictureNumber;
typedef int CubeNumber;

class Coords3D
{
public:
    int width;
    int height;
    int depth;
};

class CubeCoords
{
public:
    int width;
    int height;
    int depth;
    int wPos;
    int hPos;
    int dPos;
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

    CodingParams() : start_pos(0), end_pos(-1), verbose(false)
    , nolocal(false), fields_factor(1)
    , cubeDepth(4)
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

    FrameBuffer(int _width, int _height)
    {
        FrameBuffer();
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

    ~FrameBuffer()
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
typedef boost::multi_array<ValueType, 2 > ValueArray2D;

typedef boost::multi_array<ValueType, 3 > ValueArray3D;

typedef boost::multi_array<CoeffType, 3 > CoeffArray3D;

class PictureCount
{
public:
    ValueArray2Dref* arrayY;
    //ValueArray2D U;
    //ValueArray2D V;
    //boost::shared_ptr<FrameBuffer> frame;
    FrameBuffer* frame;
    int pictureNumber;

    int width()
    {
        if (!frame)
            return 0;

        return frame->width;
        //return Y().shape()[0];
    }

    int height()
    {
        if (!frame)
            return 0;
        return frame->height;
        //return Y().shape()[1];
    }

    ValueArray2Dref& Y()
    {
        return *arrayY;
    }

    PictureCount& operator=(const PictureCount &rhs)
    {
        // Check for self-assignment!
        if (this == &rhs) // Same object?
            return *this; // Yes, so skip assignment, and just return *this.

        pictureNumber = rhs.pictureNumber;
        if (frame)
            frame->refCount--;
        frame = rhs.frame;
        if (frame)
            frame->refCount++;
        arrayY = rhs.arrayY;

        return *this;
    }

    PictureCount(const PictureCount& orig)
    {
        pictureNumber = orig.pictureNumber;
        arrayY = orig.arrayY;
        frame = orig.frame;
        frame->refCount++;
    }

    PictureCount() : frame(NULL)
    {
        //Y(NULL, boost::extents[0][0]);
        arrayY = new ValueArray2Dref(NULL, boost::extents[0][0]);
    }

    PictureCount(FrameBuffer* _frame)
    {
        //frame = boost::shared_ptr<FrameBuffer > (_frame);

        frame = _frame;
        ///dereferencing external pointer maybe produce problems with bad usage
        if (!frame || !(frame->data))
            return;
        arrayY = new ValueArray2Dref(frame->buf[0],
                                     boost::extents[frame->height][frame->width]);
        frame->refCount++;
    }

    PictureCount(int width, int height)
    {
        frame = new FrameBuffer(width, height);
        arrayY = new ValueArray2Dref(frame->buf[0],
                                     boost::extents[frame->height][frame->width]);
        frame->refCount++;
    }

    ~PictureCount()
    {
        //delate data if its the only owner
        if (frame)
        {

            frame->refCount--;
            if (frame->refCount == 0)
            {
                //deleting external memory
                delete frame;
                delete arrayY;
            }

        }
        else //delete mapping if thers no data;
            delete arrayY;


    }
};

typedef boost::shared_ptr<FrameBuffer> FrameBufferPtr;
typedef boost::shared_ptr<ValueArray2Dref> ValueArray2DrefPtr;

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
        //return Y().shape()[0];
    }

    int height()
    {
        if (!frame)
            return 0;
        return frame->height;
        //return Y().shape()[1];
    }

    ValueArray2Dref& Y()
    {
        return *arrayY;
    }

//    PictureAuto& operator=(const Picture &rhs)
//    {
//        // Check for self-assignment!
//        if (this == &rhs) // Same object?
//            return *this; // Yes, so skip assignment, and just return *this.
//
//        pictureNumber = rhs.pictureNumber;
//        if (frame)
//            frame->refCount--;
//        frame = rhs.frame;
//        if (frame)
//            frame->refCount++;
//        arrayY = rhs.arrayY;
//
//        return *this;
//    }
//    PictureAuto(const Picture& orig)
//    {
//        pictureNumber = orig.pictureNumber;
//        arrayY = orig.arrayY;
//        frame = orig.frame;
//        frame->refCount++;
//    }

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

//    ~PictureAuto()
//    {
//        //delate data if its the only owner
//        if (frame)
//        {
//
//            frame->refCount--;
//            if (frame->refCount == 0)
//            {
//                //deleting external memory
//                delete frame;
//                delete arrayY;
//            }
//
//        }
//        else //delete mapping if thers no data;
//            delete arrayY;
//    }
};

typedef std::vector<Picture> PictureVector;



#endif /* CUBE_CODEC_H_ */
