/* 
 * File:   CodecParams.h
 * Author: korzec
 *
 * Created on August 30, 2011, 1:13 AM
 */

#ifndef CODECPARAMS_H
#define	CODECPARAMS_H

#include "arrays.h"
#include "types.h"

class CodecParams
{
public:
    Coords3D cubeSize;
    Coords3D subcubeSize;
    int levels;
    CompressionType compression;
    
    CodecParams() : cubeSize(0,0,4), subcubeSize(32,32,4), levels(1), compression(HuffmanCoder)
    {}

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


#endif	/* CODECPARAMS_H */

