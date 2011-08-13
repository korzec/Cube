/* 
 * File:   CubeIO.cpp
 * Author: korzec
 * 
 * Created on August 12, 2011, 7:38 PM
 */

#include "CubeIO.h"

CubeIO::CubeIO() : inputFile(NULL), outputFile(NULL) {}

CubeIO::CubeIO(std::string fileName, bool isWrite) : inputFile(NULL), outputFile(NULL)
{
    Init(fileName, isWrite);
}
bool CubeIO::Init(std::string fileName, bool isWrite)
{
    if(outputFile)
        outputFile->close();
    if(inputFile)
        inputFile->close();
    inputFile = NULL;
    outputFile = NULL;
    if(isWrite)
    {
        outputFile = new std::ofstream(fileName.c_str(), std::ios::out | std::ios::binary);
        return ! outputFile->fail();
    }
    else
    {
        inputFile = new std::ifstream(fileName.c_str(), std::ios::in | std::ios::binary);
        return ! inputFile->fail();
    }
    
}

bool CubeIO::WriteSequenceHeader(CodingParams)
{
    //write coding Params to a stream
}
bool CubeIO::WriteCubeHeader(int cubeNumber)
{
    
}
bool CubeIO::WritePacket(Packet)
{
    
}

CodingParams CubeIO::ReadSequenceHeader()
{
    
}
int CubeIO::ReadCubeHeader()
{
    
}
Packet CubeIO::ReadPacket()
{
    
}