/* 
 * File:   CubeIO.h
 * Author: korzec
 *
 * Created on August 12, 2011, 7:38 PM
 */

#ifndef CUBEIO_H
#define	CUBEIO_H

#include "types.h"
#include "Packet.h"
#include <string>
#include <iostream>
#include <fstream>

/// Reads and writes data encoded with cube codec
class CubeIO
{
public:
    CubeIO();
    CubeIO(std::string fileName, bool isWrite);
    bool Init(std::string fileName, bool isWrite);
    
    bool WriteSequenceHeader(CodingParams);
    bool WriteCubeHeader(int cubeNumber);
    bool WritePacket(Packet);
    
    CodingParams ReadSequenceHeader();
    int ReadCubeHeader();
    Packet ReadPacket();
private:
    std::ifstream* inputFile;
    std::ofstream* outputFile;      
};

#endif	/* CUBEIO_H */

