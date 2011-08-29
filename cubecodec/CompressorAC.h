/* 
 * File:   CompressorAC.h
 * Author: korzec
 *
 * Created on August 21, 2011, 7:50 AM
 */

#ifndef COMPRESSORAC_H
#define	COMPRESSORAC_H

#include "Compressor.h"
#include "BitStream.h"

///maps a bitplane in a byte buffer to a bitstream
class BitPlaneStream : public BitStream
{
    int bitPlaneIndex;
    int bitPlaneBytes;
public:
    BitPlaneStream( unsigned int maxLength, ucharPtr data, int planeIndex,
                   int planeBytes, bool newBuffer);
    virtual void insertBit(unsigned char newBit);
    virtual unsigned char GetBitAt(unsigned long int atBit);
    
};

class CompressorAC : public Compressor
{
public:
    CompressorAC();
    virtual Packet Compress(CoeffView3D& subcube, Coords3D& location, Channel channel, int cubeNumer);
    virtual CoeffArray3DPtr Decompress(Packet& packet, Coords3D& subcubeSize);
private:

};

#endif	/* COMPRESSORAC_H */

