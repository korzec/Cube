/* 
 * File:   CompressorAC.cpp
 * Author: korzec
 * 
 * Created on August 21, 2011, 7:50 AM
 */

#include "CompressorAC.h"
#include "BitStream.h"
#include "MQcoder.h"
#include <cassert>
#include <boost/lambda/lambda.hpp>

CompressorAC::CompressorAC()
{
}

Packet CompressorAC::Compress(CoeffView3D& subcube, Coords3D& location, Channel channel, int cubeNumber)
{

    CoeffArray3D array(subcube);
    Coords3D dims(array.shape());
    
    //TODO: implement arithemtics coding
    //initialize storage for coded data
    unsigned int fullSize = dims.Volume()*sizeof(CoeffType);
    //extra space allocated if atithmetic coding expands data instead of compacting
    ucharPtr compressedData = ucharPtr(new unsigned char [fullSize*2]);
    BitStream compressedPlanes(fullSize*2, compressedData);

    //initialize to zeros needed by the stream mapping unsafeness
    memset(compressedData.get(), 0, fullSize*2);
    
    //map CoeffArray3D to ucharPtr, with empty deallocator
    ucharPtr data = ucharPtr((unsigned char*)array.data(), boost::lambda::_1);
    //map all bitplanes 
    std::vector<BitPlaneStream> bitPlanes;
    for(unsigned int i=0; i<8*sizeof(CoeffType); i++)
        bitPlanes.push_back( BitPlaneStream(fullSize, data, i, sizeof(CoeffType), false) );
    
    //compress all bitplanes
    MQcoder::MQencoder mqEncoder(bitPlanes[0], compressedPlanes );
    mqEncoder.Encode();
    for(unsigned int i=1; i<8*sizeof(CoeffType); i++)
    {
        mqEncoder.Continue(bitPlanes[i]);
//        std::cout << "i: " << i << " : " <<bitPlanes[i].toString() << std::endl;
    }
    int bytesWritten = compressedPlanes.ByteSize();
    //output packet
    
    Packet packet;
    packet.header.cubeNumer = cubeNumber;
    packet.header.channel = channel;
    packet.compressedData = compressedData;
    packet.header.compressedSize = bytesWritten;
    packet.header.fullSize = fullSize; //redundant
    packet.header.location = location;
    return packet;
}

CoeffArray3DPtr CompressorAC::Decompress(Packet& packet, Coords3D& subcubeSize)
{
    assert(packet.compressedData.use_count() > 0);
    assert(packet.header.compressedSize > 0);
    
    unsigned int fullSize = subcubeSize.Volume()*sizeof(CoeffType);
    assert(fullSize == packet.header.fullSize);
    
    CoeffArray3DPtr array = CoeffArray3DPtr(new CoeffArray3D(
                                                             boost::extents[subcubeSize.depth][subcubeSize.height][subcubeSize.width]));

    //map CoeffArray3D to ucharPtr, with empty deallocator
    ucharPtr data = ucharPtr((unsigned char*)array->data(), boost::lambda::_1);
    //zero the buffer required by BitStream unsafeness
    memset(data.get(), 0, fullSize);
    
    //map all bitplanes 
    std::vector<BitPlaneStream> bitPlanes;
    for(unsigned int i=0; i<8*sizeof(CoeffType); i++)
        bitPlanes.push_back( BitPlaneStream(fullSize, data, i, sizeof(CoeffType), true) );
    
    BitStream compressedPlanes(packet.header.compressedSize, packet.compressedData);
    
    int singlePlaneBitSize = fullSize/2;
    
    //decompress all bitplanes
    MQcoder::MQdecoder mqDecoder(compressedPlanes, bitPlanes[0] , singlePlaneBitSize );
    mqDecoder.Decode();
    for(unsigned int i=1; i<8*sizeof(CoeffType); i++)
    {
        mqDecoder.Continue(bitPlanes[i], singlePlaneBitSize);
    }
    
    
    //check if decompressed size matches the subcube size
    return array;
}

BitPlaneStream::BitPlaneStream( unsigned int maxLength, ucharPtr data,
                               int planeIndex, int planeBytes, bool newBuffer )
: BitStream(maxLength, data), bitPlaneIndex(planeIndex), bitPlaneBytes(planeBytes)
{
    //modify length
    if(newBuffer)
        length = 0;
    else
        length = maxLength / planeBytes; 
}
void BitPlaneStream::insertBit(unsigned char newBit)
{
    if (!newBit) //assuming the buffer was initialized to 0
    {
        length++;
        return;
    }
    bits[length * bitPlaneBytes + (bitPlaneIndex>>3)] |= (1 << (7 - bitPlaneIndex % 8));
    //move to next position
    length++;  
}
unsigned char BitPlaneStream::GetBitAt(unsigned long int atBit)
{
    if (length > atBit)
    //{
        //find current byte
        //unsigned int byte = ;
        //assert(byte < maxCharLength);
        //int position = ;
        return (bits[atBit * bitPlaneBytes + (bitPlaneIndex>>3)] 
                >> (7 - bitPlaneIndex % 8)) & 1;
    //}
    return 2;
}
    