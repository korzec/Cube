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
    
    int singlePlaneCodeBufferSize = fullSize*2/16;
    
    std::vector<BitStream> compressedPlaneStreams;
    for(unsigned int i=0; i<8*sizeof(CoeffType); i++)
    {
        //allocate memory for compression of a single plane
        compressedPlaneStreams.push_back ( 
                BitStream (singlePlaneCodeBufferSize, 
                     ucharPtr(new unsigned char [singlePlaneCodeBufferSize]) ) 
        );
        
    }
    BitStream output(fullSize*2, compressedData);
    //initialize to zeros needed by the stream mapping unsafeness
    memset(compressedData.get(), 0, fullSize*2);
    
    //map CoeffArray3D to ucharPtr, with empty deallocator
    ucharPtr data = ucharPtr((unsigned char*)array.data(), boost::lambda::_1);
    
    //map all bitplanes 
    std::vector<BitPlaneStream> bitPlanes;
    for(unsigned int i=0; i<8*sizeof(CoeffType); i++)
        bitPlanes.push_back( BitPlaneStream(fullSize*2, data, i, sizeof(CoeffType), false) );
    //compress all bitplanes
    for(unsigned int i=0; i<8*sizeof(CoeffType); i++)
    {
        MQcoder::MQencoder mqEncoder(bitPlanes[i], compressedPlaneStreams[i] );
        mqEncoder.Encode();
    }
    //concentrate compressed bitplanes into one buffer
    int bytesWritten = 0;
    for(unsigned int i=0; i<8*sizeof(CoeffType); i++)
    {
        //copy compressed bitplane to the collective buffer
        int size = compressedPlaneStreams[i].ByteSize();
        memcpy(compressedData.get()+bytesWritten,
               compressedPlaneStreams[i].GetSequence().get(), size);
        bytesWritten += size;
    }

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
    
    //map all bitplanes 
    std::vector<BitPlaneStream> bitPlanes;
    for(unsigned int i=0; i<8*sizeof(CoeffType); i++)
        bitPlanes.push_back( BitPlaneStream(fullSize, data, i, sizeof(CoeffType), true) );
    
    BitStream compressedPlanes(packet.header.compressedSize, packet.compressedData);
    
    int singlePlaneBitSize = fullSize/2;
    
    //decompress all bitplanes
    MQcoder::MQdecoder mqDecoder(compressedPlanes, bitPlanes[0] , singlePlaneBitSize );
    for(unsigned int i=0; i<8*sizeof(CoeffType); i++)
    {
        bitPlanes[i];
        mqDecoder.Decode();
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
    