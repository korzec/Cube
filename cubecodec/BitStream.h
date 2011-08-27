/* 
 * File:   BitStream.h
 * Author: korzec
 *
 * Created on August 26, 2011, 7:10 PM
 */

#ifndef BITSTREAM_H
#define	BITSTREAM_H

#include "arrays.h"
#include <cassert>
class BitStream
{
protected:
    unsigned long int length;
    unsigned int maxByteLength;
    ucharPtr bitSequence;
    unsigned char* bits;
public:
    BitStream(unsigned int maxLength);
    BitStream( unsigned int maxLength, ucharPtr data);
    void insertBit(unsigned char newBit);
    void insertBitStream(BitStream stream);
    void insertByte(unsigned char newByte);
    BitStream Clone();
    int GetLength();
    ucharPtr GetSequence();
    unsigned char GetBitAt(unsigned long int atBit);
    int ByteSize();
    std::string toString();
};

#endif	/* BITSTREAM_H */

