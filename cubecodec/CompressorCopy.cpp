/* 
 * File:   CompressorAC.cpp
 * Author: korzec
 * 
 * Created on August 21, 2011, 7:50 AM
 */

#include "CompressorCopy.h"
//#include <iostream>
#include <cassert>

CompressorCopy::CompressorCopy()
{
}

Packet CompressorCopy::Compress(CoeffView3D& subcube, Coords3D& location, Channel channel, int cubeNumber)
{

    CoeffArray3D array(subcube);
    Coords3D dims(array.shape());
    
    //initialize storage for coded data
    unsigned int fullSize = dims.Volume()*sizeof(CoeffType);
    //allocate memory for data
    ucharPtr compressedData = ucharPtr(new unsigned char [fullSize]);
    
    //copy data into compressedData
    memcpy(compressedData.get(), array.data(), fullSize);
    
    Packet packet;
    packet.header.channel = channel;
    packet.compressedData = compressedData;
    packet.header.compressedSize = fullSize;
    packet.header.location = location;
    return packet;
}

CoeffArray3DPtr CompressorCopy::Decompress(Packet& packet, Coords3D& subcubeSize)
{
    unsigned int fullSize = subcubeSize.Volume()*sizeof(CoeffType);
    
    CoeffArray3DPtr array = CoeffArray3DPtr(new CoeffArray3D(
                                                             boost::extents[subcubeSize.depth][subcubeSize.height][subcubeSize.width]));
    assert(fullSize == packet.header.compressedSize );
    memcpy(array.get()->data(), packet.compressedData.get(), packet.header.compressedSize);   
    
    return array;
}

    