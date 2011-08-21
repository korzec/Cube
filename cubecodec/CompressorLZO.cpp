/* 
 * File:   CompressorLZO.cpp
 * Author: korzec
 * 
 * Created on August 21, 2011, 7:50 AM
 */

#include "CompressorLZO.h"
#include "../minilzo/minilzo.h"
#include <cassert>

CompressorLZO::CompressorLZO()
{
}

Packet CompressorLZO::Compress(CoeffView3D& subcube, Coords3D& location, Channel channel, int cubeNumber)
{
//    assert(subcube.size() > 0);
    assert(lzo_init() == LZO_E_OK);
    if (lzo_init() != LZO_E_OK)
        return Packet(); //if compressor doest work
    
    lzo_uint fullSize;
    lzo_uint compressedSize;
    //lzo_uint new_len;
    
    CoeffArray3D array(subcube);
    Coords3D dims(array.shape());
    fullSize = dims.Volume()*sizeof(CoeffType);
    
    unsigned char* workMemory = new unsigned char [64*1024];

    unsigned char* cubeData = (unsigned char*)array.data();
    size_t bufferSize = fullSize + fullSize/64 + 16 + 3; //lzo can expand input 
    unsigned char* compressedData = new unsigned char [bufferSize];

    int result =  lzo1x_1_compress(cubeData, fullSize, compressedData, &compressedSize, workMemory );
    delete[] workMemory;
    assert(result == LZO_E_OK);

    Packet packet;
    packet.cubeNumer = cubeNumber;
    packet.channel = channel;
    packet.compressedData = ucharPtr(compressedData);
    packet.compressedSize = compressedSize;
    packet.fullSize = fullSize; //redundant
    packet.location = location;
    return packet;
}

CoeffArray3DPtr CompressorLZO::Decompress(Packet& packet, Coords3D& subcubeSize)
{
    assert(lzo_init() == LZO_E_OK);
    assert(packet.compressedData.use_count() > 0);
    assert(packet.compressedSize > 0);
    lzo_uint fullSize;
    lzo_uint compressedSize;
    lzo_uint newSize;
    
    fullSize = subcubeSize.Volume()*sizeof(CoeffType);
    assert((size_t)packet.fullSize == fullSize); //redundant
    compressedSize = packet.compressedSize;
    
    CoeffArray3DPtr array = CoeffArray3DPtr(new CoeffArray3D(
            extents[subcubeSize.depth][subcubeSize.height][subcubeSize.width]));
    
    unsigned char* cubeData = (unsigned char*)array->data();
    unsigned char* compressedData = packet.compressedData.get();
    
    int result = lzo1x_decompress(compressedData,compressedSize,cubeData,&newSize,NULL);
    //check if decompressed size matches the subcube size
    assert(result == LZO_E_OK && newSize == fullSize); 
    return array;
}
    