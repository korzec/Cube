/* 
 * File:   CubeStream.h
 * Author: korzec
 *
 * Created on August 14, 2011, 1:09 AM
 */

#ifndef CUBESTREAM_H
#define	CUBESTREAM_H

#include "types.h"
#include "Packet.h"
#include <string>
#include <iostream>
#include <fstream>

class CubeStream
{
public:
    CubeStream();
    CubeStream(std::istream* stream);
    CubeStream(std::ostream* stream);
    virtual bool Init(std::istream* stream);
    virtual bool Init(std::ostream* stream);
    virtual ~CubeStream();
    virtual bool Finish();
           
    bool WriteSequenceHeader(const Parameters&, const VideoParams&);
    bool WriteCubeHeader(const int& cubeNumber);
    bool WritePacket(const Packet&);
    
    bool ReadSequenceHeader(Parameters&, VideoParams&);
    bool ReadCubeHeader(int& cubeNumber);
    Packet ReadPacket();
    
protected:
    CubeStream(const CubeStream& orig);
    std::istream* inputFile;
    std::ostream* outputFile; 

};

#endif	/* CUBESTREAM_H */

