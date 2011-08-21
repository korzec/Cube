/* 
 * File:   CubeStream.h
 * Author: korzec
 *
 * Created on August 14, 2011, 1:09 AM
 */

#ifndef CUBESTREAM_H
#define	CUBESTREAM_H

#include "arrays.h"
#include "cubeHeaders.h"
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
           
    bool WriteSequenceHeader(const CodecParams&, const VideoParams&);
    bool WriteCubeHeader(const int& cubeNumber);
    bool WritePacket(const Packet&);
    
    bool ReadSequenceHeader(CodecParams&, VideoParams&);
    bool ReadCubeHeader(int& cubeNumber);
    Packet ReadPacket();
    
    //checks if the next data belongs to next cube
    bool CheckNextCube();
    
protected:
    CubeStream(const CubeStream& orig);
    std::istream* inputFile;
    std::ostream* outputFile; 

};

#endif	/* CUBESTREAM_H */

