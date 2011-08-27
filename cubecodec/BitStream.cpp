/* 
 * File:   BitStream.cpp
 * Author: korzec
 * 
 * Created on August 26, 2011, 7:10 PM
 */

#include "BitStream.h"

BitStream::BitStream(unsigned int byteLength) : length(0), maxByteLength(byteLength)
{
    bitSequence.reset(new unsigned char [maxByteLength]);
    bits = bitSequence.get();
    //zero the alocated memory
    memset(bitSequence.get(), 0, maxByteLength);
}

BitStream::BitStream(unsigned int maxLength, ucharPtr data) : length(0), maxByteLength(maxLength)
{
    //set length with byte grain; extra bits should be discarded by decompressor
    length = maxLength * 8;
    //assign the memory
    bitSequence = data;
    bits = bitSequence.get();
}

void BitStream::insertBit(unsigned char newBit)
{
    //newBit = newBit & 1;
    //if there is still space
    //if (length < maxCharLength * 8)
    {
        if (!newBit)
        {
            length++;
            return;
        }
        //find current byte
        //unsigned int byte = length >> 3;
        //assert(byte < maxCharLength);
        //insert new bit at its position
        //int position = 7 - length % 8;
        bitSequence.get()[length >> 3] |= (1 << (7 - length % 8)); //on;y works if 0 is skipped
        //move to next position
        length++;
    }
}

void BitStream::insertBitStream(BitStream stream)
{
    //all bits one by one
    //unsigned char newBit = 0;
    for (int atBit = 0; atBit < stream.GetLength(); atBit++)
        insertBit(stream.GetBitAt(atBit));
    //{
    //make this inline:
        //newBit = ( (bitSequence.get()[atBit >> 3] >> (7 - atBit % 8)) & 1 );
        //if(!newBit)
        //    bitSequence.get()[length >> 3] |= (1 << (7 - length % 8));
        //length++;
        
    //}
}

void BitStream::insertByte(unsigned char newByte)
{
    if(length%8)
    {
        //copy to current byte and move by 8
        bitSequence.get()[length >> 3] = newByte;
        length += 8;
    }
    else
    {    
        //insert bit by bit
        for (int atBit = 0; atBit < 8; atBit++)
            insertBit(newByte << (7 - atBit));
    }
}

BitStream BitStream::Clone()
{
    BitStream word(maxByteLength);
    memcpy(word.bitSequence.get(), bitSequence.get(), maxByteLength);
    word.length = length;
    return word;
}

int BitStream::GetLength()
{
    return length;
}

ucharPtr BitStream::GetSequence()
{
    return bitSequence;
}

unsigned char BitStream::GetBitAt(unsigned long int atBit)
{
    //OPT
    //if not out of range
    if (length > atBit)
    //{
        //find current byte
        //unsigned int byte = ;
        //assert(byte < maxCharLength);
        //int position = ;
        return (bits[atBit >> 3] >> (7 - atBit % 8)) & 1;
    //}
    return 2;
}

int BitStream::ByteSize()
{
    return (length >> 3) + 1;
}

std::string BitStream::toString()
{
    std::stringstream stringStream;

    for (unsigned long int i = 0; i < length; i++)
    {
        //find current byte
        unsigned int byte = i >> 3;
        assert(byte < maxByteLength);
        //output current 
        int position = 7 - i % 8;
        if (bitSequence.get()[byte] & 1 << position)
            stringStream << '1';
        else
            stringStream << '0';
    }
    return stringStream.str();
}
