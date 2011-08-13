/* 
 * File:   Compressor.cpp
 * Author: korzec
 * 
 * Created on August 12, 2011, 8:14 PM
 */

#include "Compressor.h"
#include "minilzo/minilzo.h"
#include <cassert>

Compressor::Compressor()
{
}

Packet Compressor::Compress(CoeffView3D& subcube, Coords3D& location)
{
    assert(lzo_init() == LZO_E_OK);
    if (lzo_init() != LZO_E_OK)
        return Packet(); //if compressor doest work
    
    lzo_uint fullSize;
    lzo_uint compressedSize;
    //lzo_uint new_len;
    
    CoeffArray3D array(subcube);
    fullSize = array.size();
    
    unsigned char* wrkmem = new unsigned char [64*1024];

    unsigned char* cubeData = (unsigned char*)array.data();
    unsigned char* compressedData = new unsigned char [fullSize];

    int result =  lzo1x_1_compress(cubeData, fullSize, compressedData, &compressedSize, wrkmem );
    assert(result == LZO_E_OK);

    Packet packet;
    packet.CompressedData = ucharPtr(compressedData);
    packet.compressedSize = compressedSize;
    packet.fullSize = fullSize;
    packet.location = location;
    return packet;
}

CoeffArray3DPtr Compressor::Decompress(Packet packet, Coords3D& subcubeSize)
{
    lzo_uint fullSize;
    lzo_uint compressedSize;
    lzo_uint newSize;
    
    fullSize = subcubeSize.width*subcubeSize.height*subcubeSize.height;
    compressedSize = packet.compressedSize;
    
    CoeffArray3DPtr array = CoeffArray3DPtr(new CoeffArray3D(
            extents[subcubeSize.depth][subcubeSize.height][subcubeSize.width]));
    
    unsigned char* cubeData = (unsigned char*)array->data();
    unsigned char* compressedData = packet.CompressedData.get();
    
    int result = lzo1x_decompress(compressedData,compressedSize,cubeData,&newSize,NULL);
    //check if decompressed size matches the subcube size
    assert(result == LZO_E_OK && newSize == fullSize); 
    return array;
}
    