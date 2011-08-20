/* 
 * File:   Decoder.cpp
 * Author: korzec
 * 
 * Created on August 19, 2011, 7:48 PM
 */

#include "Decoder.h"

Decoder::Decoder() : pictureOutputBuffer(0), pictureNumber(0), cubeNumber(0)
{
}

BufferState Decoder::Decode()
{
   //check if we have the packets read
    if (allPackets.size() > 0)
    {
        if (DecompressAll() && coeffCube.ReverseTransform())
        { 
            PictureVectorPtr outputGOP = coeffCube.GetGOP();
            bool ret = pictureOutputBuffer.AddGOP(*outputGOP);
            
            if (ret == false)
            {
                std::cerr << "buffer full, couldn't output pictures";
                return INVALID;
            }
            //remove old packets
            allPackets.clear();
            return PICTURE_AVAILABLE;
        }
        else //transform or decompression failed
            return INVALID;
    }
    else //if not enough buffer
    {
        return NEED_BUFFER;
    }
}

Parameters Decoder::GetParams() const
{
    return params;
}

PictureVectorPtr Decoder::GetDecodedGOP()
{
    PictureVectorPtr gop(new PictureVector);
    pictureOutputBuffer.GetGOP(params.codecParams.cubeSize.depth, *gop);
    return gop;
}

//Picture Encoder::GetNextDecodedPicture()
//{
//    pictureOutputBuffer;
//}

bool Decoder::DeleteOldOutputGOP()
{
    return pictureOutputBuffer.RemoveOldGOP(params.codecParams.cubeSize.depth);
}

bool Decoder::DecompressAll()
{
    //zero all values in all cube arrays
    coeffCube.ZeroAll();
    
    //for all packets in list decompress and copy to location
    PacketMap::reverse_iterator iterator = allPackets.rbegin();
    Subcube *subcube = NULL;
    CoeffArray3DPtr newArrayPtr;
    for (; iterator != allPackets.rend(); iterator++)
    {
        // get subcube to copy the data
        subcube = &coeffCube.GetSubcubeIndex(iterator->second.channel)
                ->GetSubcube(iterator->second.location);
        
        newArrayPtr = compressor.Decompress(iterator->second, params.codecParams.subcubeSize);
        subcube->CopyNewValues(newArrayPtr);
    }
    return true;
}


bool Decoder::ReadSequenceHeader(std::istream* stream)
{
    CubeStream cubeStream(stream);
    VideoParams vparams;
    bool ret = cubeStream.ReadSequenceHeader(params.codecParams, vparams);
    if( !ret )
        return false;
    //Init cube and budders with read parameters
    return Init();
}

bool Decoder::ReadCube(std::istream* stream)
{
    //open file for read
    CubeStream cubeStream(stream);
    bool ret = cubeStream.ReadCubeHeader(coeffCube.GetCubeNumber());
    if(!ret)
        return false;
    //read in all packets
    //read packets until next cube header
    Packet packet;
    allPackets.clear();
    for(int counter=0 ; cubeStream.CheckNextCube() == false; counter-- )
    {
        packet = cubeStream.ReadPacket();
        allPackets.insert(PacketPair((float)counter, packet ));
    }
    return true;
}

bool Decoder::Init()
{   
    bool ret = coeffCube.Init(params.codecParams.cubeSize, 
                          params.codecParams.levels,
                          params.codecParams.subcubeSize);
    if(!ret)
        return false;
    pictureOutputBuffer = PictureBuffer(params.codecParams.cubeSize.depth);
    //check if subcubeSize divides by cube size
    if( params.codecParams.cubeSize.width % params.codecParams.subcubeSize.width != 0 ||
        params.codecParams.cubeSize.height % params.codecParams.subcubeSize.height != 0 ||
        params.codecParams.cubeSize.depth % params.codecParams.subcubeSize.depth != 0)
        return false;
    return true;
}