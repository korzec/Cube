/* 
 * File:   Parameters.h
 * Author: korzec
 *
 * Created on August 21, 2011, 8:44 AM
 */

#ifndef PARAMETERS_H
#define	PARAMETERS_H

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
    float skipRatio;

    Parameters() : 
    start_pos(0), end_pos(INT_MAX), verbose(false), nolocal(true), 
    analysis(false), decode(false), notest(false), skipRatio(0)
    {}   
    std::string toString(bool localConfig = false)
    {
        std::stringstream stream;
        stream << " width " << codecParams.cubeSize.width << std::endl
            << " height " << codecParams.cubeSize.height << std::endl
            << " depth " << codecParams.cubeSize.depth << std::endl
            << " levels " << codecParams.levels << std::endl
            << " compression " << codecParams.compression << std::endl
            << " sub_w " << codecParams.subcubeSize.width << std::endl
            << " sub_h " << codecParams.subcubeSize.height << std::endl
            << " sub_d " << codecParams.subcubeSize.depth << std::endl;
        if(localConfig)
                stream << " skipRatio " << skipRatio << std::endl
                       << " notest " << notest << std::endl;
        return stream.str();
    }
};

#endif	/* PARAMETERS_H */

