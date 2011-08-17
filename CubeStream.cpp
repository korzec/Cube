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

bool CubeStream::WriteSequenceHeader(const CodecParams& codecParams, const VideoParams& videoParams)
{
    if(!outputFile)
        return false;
    //write coding Params to a stream , not handling endianess
#define FILEOPERATION outputFile->write
    FILEOPERATION((char*) &codecParams.cubeSize, sizeof (codecParams.cubeSize));  //1
    FILEOPERATION((char*) &codecParams.subcubeSize, sizeof (codecParams.subcubeSize)); //2
    FILEOPERATION((char*) &codecParams.levels, sizeof (codecParams.levels)); //3
    FILEOPERATION((char*) &videoParams.frameCount, sizeof (videoParams.frameCount)); //4
    FILEOPERATION((char*) &videoParams.fpsNumerator, sizeof (videoParams.fpsNumerator)); //5
    FILEOPERATION((char*) &videoParams.fpsDenominator, sizeof (videoParams.fpsDenominator)); //6
#undef FILEOPERATION
    return ! outputFile->fail();
}

bool CubeStream::ReadSequenceHeader(CodecParams& codecParams, VideoParams& videoParams)
{
    if(!inputFile)
        return false;
#define FILEOPERATION inputFile->read
    FILEOPERATION((char*) &codecParams.cubeSize, sizeof (codecParams.cubeSize));  //1
    FILEOPERATION((char*) &codecParams.subcubeSize, sizeof (codecParams.subcubeSize)); //2
    FILEOPERATION((char*) &codecParams.levels, sizeof (codecParams.levels)); //3
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
    char header = CUBEHEADERCODE;
    outputFile->write
            ((char*) &header, sizeof (header));
    outputFile->write
            ((char*) &cubeNumber, sizeof (cubeNumber));
    return ! outputFile->fail();
}

bool CubeStream::WritePacket(const Packet& packet)
{
    if(!outputFile)
        return false;
    char header = PACKETHEADERCODE;
#define FILEOPERATION outputFile->write
    FILEOPERATION((char*) &header, sizeof (header));
    FILEOPERATION((char*) &packet.channel, sizeof (packet.channel));
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
    char header = 0;
    inputFile->read
            ((char*) &header, sizeof (header));
    inputFile->read
            ((char*) &cubeNumber, sizeof (cubeNumber));
    return ! inputFile->fail();
}

Packet CubeStream::ReadPacket()
{    
    if(!inputFile)
        return Packet();
    Packet packet;
    char header = 0;
#define FILEOPERATION inputFile->read
    FILEOPERATION((char*) &header, sizeof (header));
    FILEOPERATION((char*) &packet.channel, sizeof (packet.channel));
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


bool CubeStream::CheckNextCube()
{
    if(!inputFile)
        return true;
    int peek = inputFile->peek();
    if( peek == CUBEHEADERCODE )
        return true;
    if(peek == PACKETHEADERCODE)
        return false;
    //asume its a next cube when its not a packet
    return true;
}