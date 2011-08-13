/* 
 * File:   CubeIO.cpp
 * Author: korzec
 * 
 * Created on August 12, 2011, 7:38 PM
 */

#include "CubeIO.h"

CubeIO::CubeIO() : inputFile(NULL), outputFile(NULL)
{
}

CubeIO::CubeIO(std::string fileName, bool isWrite) : inputFile(NULL), outputFile(NULL)
{
    Init(fileName, isWrite);
}

bool CubeIO::Init(std::string fileName, bool isWrite)
{
    if (outputFile)
        outputFile->close();
    if (inputFile)
        inputFile->close();
    inputFile = NULL;
    outputFile = NULL;
    if (isWrite)
    {
        outputFile = new std::ofstream(fileName.c_str(), std::ios::out | std::ios::binary);
        return !outputFile->fail();
    }
    else
    {
        inputFile = new std::ifstream(fileName.c_str(), std::ios::in | std::ios::binary);
        return !inputFile->fail();
    }

}

bool CubeIO::WriteSequenceHeader(const Parameters& parameters, const VideoParams& videoParams)
{
    if(!outputFile)
        return false;
    //write coding Params to a stream , not handling endianess
#define FILEOPERATION outputFile->write
    FILEOPERATION((char*) &parameters.codecParams.cubeSize, sizeof (parameters.codecParams.cubeSize));  //1
    FILEOPERATION((char*) &parameters.codecParams.subcubeSize, sizeof (parameters.codecParams.subcubeSize)); //2
    FILEOPERATION((char*) &parameters.codecParams.levels, sizeof (parameters.codecParams.levels)); //3
    FILEOPERATION((char*) &videoParams.frameCount, sizeof (videoParams.frameCount)); //4
    FILEOPERATION((char*) &videoParams.fpsNumerator, sizeof (videoParams.fpsNumerator)); //5
    FILEOPERATION((char*) &videoParams.fpsDenominator, sizeof (videoParams.fpsDenominator)); //6
#undef FILEOPERATION
    return ! outputFile->fail();
}

bool CubeIO::ReadSequenceHeader(Parameters& parameters, VideoParams& videoParams)
{
    if(!inputFile)
        return false;
#define FILEOPERATION inputFile->read
    FILEOPERATION((char*) &parameters.codecParams.cubeSize, sizeof (parameters.codecParams.cubeSize));  //1
    FILEOPERATION((char*) &parameters.codecParams.subcubeSize, sizeof (parameters.codecParams.subcubeSize)); //2
    FILEOPERATION((char*) &parameters.codecParams.levels, sizeof (parameters.codecParams.levels)); //3
    FILEOPERATION((char*) &videoParams.frameCount, sizeof (videoParams.frameCount)); //4
    FILEOPERATION((char*) &videoParams.fpsNumerator, sizeof (videoParams.fpsNumerator)); //5
    FILEOPERATION((char*) &videoParams.fpsDenominator, sizeof (videoParams.fpsDenominator)); //6
#undef FILEOPERATION
    return ! inputFile->fail();
}

bool CubeIO::WriteCubeHeader(const int& cubeNumber)
{
    if(!outputFile)
        return false;
    outputFile->write
            ((char*) &cubeNumber, sizeof (cubeNumber));
    return ! outputFile->fail();
}

bool CubeIO::WritePacket(const Packet& packet)
{
    if(!outputFile)
        return false;
#define FILEOPERATION outputFile->write
    FILEOPERATION((char*) &packet.location.depth, sizeof (packet.location.depth));
    FILEOPERATION((char*) &packet.location.height, sizeof (packet.location.height));
    FILEOPERATION((char*) &packet.location.width, sizeof (packet.location.width));
    FILEOPERATION((char*) &packet.fullSize, sizeof (packet.fullSize));
    FILEOPERATION((char*) &packet.compressedSize, sizeof (packet.compressedSize));
    FILEOPERATION((char*) packet.compressedData.get(), sizeof(char)*packet.compressedSize);
#undef FILEOPERATION
    return ! outputFile->fail();
}

bool CubeIO::ReadCubeHeader(int& cubeNumber)
{   
    if(!inputFile)
        return false;
    inputFile->read
            ((char*) &cubeNumber, sizeof (cubeNumber));
    return ! inputFile->fail();
}

Packet CubeIO::ReadPacket()
{    
    if(!inputFile)
        return Packet();
    Packet packet;
#define FILEOPERATION inputFile->read
    FILEOPERATION((char*) &packet.location.depth, sizeof (packet.location.depth));
    FILEOPERATION((char*) &packet.location.height, sizeof (packet.location.height));
    FILEOPERATION((char*) &packet.location.width, sizeof (packet.location.width));
    FILEOPERATION((char*) &packet.fullSize, sizeof (packet.fullSize));
    FILEOPERATION((char*) &packet.compressedSize, sizeof (packet.compressedSize));
    packet.compressedData = ucharPtr(new unsigned char[packet.compressedSize] );
    FILEOPERATION((char*) packet.compressedData.get(), sizeof(char)*packet.compressedSize);
#undef FILEOPERATION
    return packet;
}

bool CubeIO::Finish()
{
    bool state;
    if (outputFile)
    {
        outputFile->close();
        state = ! outputFile->fail();
    }
    else if (inputFile)
    {
        inputFile->close();
        state = ! inputFile->fail();
    }
    else
        state = true;
    inputFile = NULL;
    outputFile = NULL;
    return state;
}

CubeIO::~CubeIO()
{
    Finish();
}
