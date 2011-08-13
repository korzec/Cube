/*
 * cube_codec.h
 *
 *  Created on: Jul 8, 2011
 *      Author: korzec
 */

#ifndef CUBE_CODEC_H_
#define CUBE_CODEC_H_

#define OUTDIR "out/"

#ifndef DEBUG
#define BOOST_DISABLE_ASSERTS 
#endif
#include "boost/multi_array.hpp"
#include <boost/smart_ptr.hpp>

#include <exception>
#include <iostream>
#include <cassert>

//using namespace blitz;
using namespace boost;

typedef float CoeffType;
typedef unsigned char ValueType;
typedef int PictureNumber;
typedef int CubeNumber;

///orientation labels for the 3d subbands
enum Orientation
{
    ///order: width, height, depth
    LLL = 0,
    HLL = 1,
    LHL = 2,
    HHL = 3,
    LLH = 4,
    HLH = 5,
    LHH = 6,
    HHH = 7,
};

enum Channel
{
    Ych = 0,
    Uch = 1,
    Vch = 2,
};

///coordinates in 3d (euclidean x,y,z)
class Coords3D
{
public:
    int width;
    int height;
    int depth;
    Coords3D() : width(-1), height(-1), depth(-1)
    {
        
    }
    Coords3D(int width, int height, int depth)
    {
         this->width = width;
         this->height = height;
         this->depth = depth;
    }
    
    Coords3D(const boost::multi_array_types::size_type* dimensionality)
    {
         this->width = dimensionality[2];
         this->height = dimensionality[1];
         this->depth = dimensionality[0];
    }
    Coords3D& Set(int width, int height, int depth)
    {
         this->width = width;
         this->height = height;
         this->depth = depth;
         return *this;
    }
    int Volume()
    {
        return width*height*depth;
    }
};

///posible states of the encoder after encoding iteration
enum EncoderState
{
    PICTURE_AVAILABLE, NEED_BUFFER, END_OF_SEQUENCE, INVALID,
    OUTPUT_AVAILABLE
};

///parameters of encoding
class CodingParams
{
public:
    Coords3D cubeSize;
    Coords3D subcubeSize;

    int start_pos;
    int end_pos;
    bool verbose;
    bool nolocal;
    bool analysis;
    int levels;

    CodingParams() : cubeSize(0,0,4), subcubeSize(32,32,4),
    start_pos(0), end_pos(INT_MAX), verbose(false), nolocal(true), 
    analysis(false), levels(1)
    {
    }
};

class VideoParams
{
public:
    int fpsNumerator;
    int fpsDenominator;
    int frameCount;

    VideoParams() : fpsNumerator(30), fpsDenominator(1), frameCount(0)
    {
    }
};

///holds data of a frame, NOT safe to copy or assign, not for direct use
//TODO: use auto pointers for memory allocations
class FrameBuffer
{
public:
    /*! buffers to hold the luma and chroma data */
    unsigned char *data;
    unsigned char *buf[3];
    int width;
    int height;

    FrameBuffer() : data(NULL), width(0), height(0)
    {
        buf[0] = NULL;
        buf[1] = NULL;
        buf[2] = NULL;
    }

    FrameBuffer(int _width, int _height) : data(NULL), width(0), height(0)
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
        if(data)        
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
typedef boost::detail::multi_array::sub_array<CoeffType, 2> CoeffView2D;

typedef CoeffArray3D::array_view<3>::type CoeffView3D;
typedef boost::shared_ptr<CoeffView3D> CoeffView3DPtr;

typedef boost::shared_ptr<FrameBuffer> FrameBufferPtr;
typedef boost::shared_ptr<ValueArray2Dref> ValueArray2DrefPtr;
typedef boost::shared_ptr<CoeffArray3D> CoeffArray3DPtr;

typedef boost::multi_array_types::index_range range;

typedef boost::shared_array<unsigned char> ucharPtr;

#endif /* CUBE_CODEC_H_ */
