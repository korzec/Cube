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
#include <string>
#include "CodecParams.h"

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
    bool test;
    bool stats;
    float skipRatio;
    bool nofile;
    bool dumpCubes;
    bool analysis2;
    std::string output;
    std::string input;

    Parameters() : 
    start_pos(0), end_pos(INT_MAX), verbose(false), nolocal(true), 
    analysis(false), decode(false), test(false), stats(false), skipRatio(0), 
    nofile(false), dumpCubes(false), analysis2(false)
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
                       << " notest " << test << std::endl;
        return stream.str();
    }
};

#endif	/* PARAMETERS_H */

