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
    //int headerCode = SEQUENCEHEADERCODE;
    
    SequenceHeader header;
    header.headerCode   = SEQUENCEHEADERCODE;
    header.codecParams = codecParams;
    header.videoParams = videoParams;
    
    outputFile->write((char*)&header, sizeof(header));
    
    return ! outputFile->fail();
}

bool CubeStream::ReadSequenceHeader(CodecParams& codecParams, VideoParams& videoParams)
{
    if(!inputFile)
        return false;
    
    SequenceHeader header;
    
    inputFile->read((char*)&header, sizeof(header));
    if(header.headerCode != SEQUENCEHEADERCODE)
        return false;
    
    codecParams = header.codecParams;
    videoParams = header.videoParams;
    
    return ! inputFile->fail();
}

bool CubeStream::WriteCubeHeader(const int& cubeNumber)
{
    if(!outputFile)
        return false;
    CubeHeader header;
    header.headerCode = CUBEHEADERCODE;
    header.cubeNumber = cubeNumber;
    outputFile->write((char*) &header, sizeof (header));
    return ! outputFile->fail();
}

bool CubeStream::ReadCubeHeader(int& cubeNumber)
{   
    if(!inputFile)
        return false;
    CubeHeader header;
    inputFile->read ((char*) &header, sizeof (header));
    if(header.headerCode != CUBEHEADERCODE)
        return false;
    cubeNumber = header.cubeNumber;
    return ! inputFile->fail();
}

bool CubeStream::WritePacket(const Packet& packet)
{
    if(!outputFile)
        return false;
    
    PacketHeader header;
    header = packet.header;
    header.headerCode = PACKETHEADERCODE;
    
    outputFile->write((char*)&header, sizeof(header));
    outputFile->write((char*)packet.compressedData.get(), packet.header.compressedSize);
    
    return ! outputFile->fail();
}

Packet CubeStream::ReadPacket()
{    
    if(!inputFile)
        return Packet();
    
    PacketHeader header;
    
    inputFile->read((char*)&header, sizeof(header));
    if(header.headerCode != PACKETHEADERCODE)
        return Packet();
    
    Packet packet;
    packet.header = header;
    
    packet.compressedData = ucharPtr(new unsigned char[packet.header.compressedSize] );
    inputFile->read((char*) packet.compressedData.get(), packet.header.compressedSize);
    if(inputFile->fail())
        return Packet();
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