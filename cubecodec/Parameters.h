/* 
 * File:   Parameters.h
 * Author: korzec
 *
 * Created on August 21, 2011, 8:44 AM
 */

#ifndef PARAMETERS_H
#define	PARAMETERS_H

#include "arrays.h"

class CodecParams
{
public:
    Coords3D cubeSize;
    Coords3D subcubeSize;
    int levels;
    
    CodecParams() : cubeSize(0,0,4), subcubeSize(32,32,4), levels(1)
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

///parameters of encoding
class Parameters
{
public:
    
    CodecParams codecParams;

    int start_pos;
    int end_pos;
    bool verbose;
    bool nolocal;
    bool analysis;
    bool decode;
    bool notest;

    Parameters() : 
    start_pos(0), end_pos(INT_MAX), verbose(false), nolocal(true), 
    analysis(false), decode(false), notest(false)
    {}
};

#endif	/* PARAMETERS_H */

