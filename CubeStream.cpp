/* 
 * File:   CubeStream.cpp
 * Author: korzec
 * 
 * Created on August 14, 2011, 1:09 AM
 */

#include "CubeStream.h"

CubeStream::CubeStream() : inputFile(NULL), outputFile(NULL)
{
}

CubeStream::CubeStream(std::istream* stream) : inputFile(NULL), outputFile(NULL)
{
    Init(stream);
}

CubeStream::CubeStream(std::ostream* stream) : inputFile(NULL), outputFile(NULL)
{
    Init(stream);
}

bool CubeStream::Init(std::istream* stream)
{
    if (outputFile || inputFile)
        return false;
    if(!stream)
        return false;
    inputFile = stream;
    return !inputFile->fail();
}

bool CubeStream::Init(std::ostream* stream)
{
    if (outputFile || inputFile)
        return false;
    if(!stream)
        return false;
    outputFile = stream;
    return !outputFile->fail();
}

bool CubeStream::WriteSequenceHeader(const Parameters& parameters, const VideoParams& videoParams)
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

bool CubeStream::ReadSequenceHeader(Parameters& parameters, VideoParams& videoParams)
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

bool CubeStream::WriteCubeHeader(const int& cubeNumber)
{
    if(!outputFile)
        return false;
    outputFile->write
            ((char*) &cubeNumber, sizeof (cubeNumber));
    return ! outputFile->fail();
}

bool CubeStream::WritePacket(const Packet& packet)
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

bool CubeStream::ReadCubeHeader(int& cubeNumber)
{   
    if(!inputFile)
        return false;
    inputFile->read
            ((char*) &cubeNumber, sizeof (cubeNumber));
    return ! inputFile->fail();
}

Packet CubeStream::ReadPacket()
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

bool CubeStream::Finish()
{
    bool state;
    if (outputFile)
    {
        outputFile->flush();
        state = outputFile->good();
    }
    else if (inputFile)
    {
        inputFile->sync();
        state = inputFile->good();
    }
    else
        state = true;
    inputFile = NULL;
    outputFile = NULL;
    return state;
}

CubeStream::~CubeStream()
{
    Finish();
}
