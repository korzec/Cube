/* 
 * File:   CompressorHuffman.h
 * Author: korzec
 *
 * Created on August 22, 2011, 12:47 AM
 */

#ifndef COMPRESSORHUFFMAN_H
#define	COMPRESSORHUFFMAN_H

#include "Compressor.h"
#include <map>
#include <cassert>

class HuffNode;
typedef boost::shared_ptr<HuffNode> HuffNodePtr;

class HuffNode
{
public:
    CoeffType symbol;
    float weight;
    HuffNodePtr left, right;
};

#define MAXCODEWORDLENGTH 80

class BitStream
{
protected:
    int length;
    int maxCharLength;
    ucharPtr bitSequence;
    bool flushed;
public:
    BitStream(int maxLength) : length(0), maxCharLength(maxLength), flushed(false)
    {
        bitSequence.reset(new unsigned char [maxCharLength] );
        //zero the alocated memory
        memset(bitSequence.get(), 0, maxCharLength);
    }
    void insertBit(unsigned char newBit)
    {
        //TODO:if flushed abort or Unflush
        newBit = newBit & 1;
          
        //if there is still space
        if( length < maxCharLength*8 && !flushed)
        {
            //find current byte
            int byte = length>>3;
            assert(byte < maxCharLength);
            //insert new bit shifting the previous ones to the left
            bitSequence.get()[byte] = (bitSequence.get()[byte]<<1) | newBit;          
            //move to next position
            length++;
        }  
    }
    void insertBitStream(BitStream stream)
    {
        //all bits one by one
        for(int i = 0; i< stream.GetLength(); i++)
            insertBit(stream.GetBitAt(i));
    }
    BitStream Clone()
    {
        BitStream word(maxCharLength); 
        memcpy( word.bitSequence.get(), bitSequence.get(), maxCharLength);
        word.length = length;
        return word;
    }
    int GetLength() { return length; }
    ucharPtr GetSequence() { return bitSequence; }
    
    unsigned char extractBit()
    {
        //if there is still bits left
        if(length > 0)
        {
            //find current byte
            int byte = length>>3;
            assert(byte < maxCharLength);
            //get current bit value
            unsigned char result = bitSequence.get()[byte] & 1;
            //shift to the right to drop lsb
            bitSequence.get()[byte]>>=1;
            //decrease length
            length--;
            return result;
        }
        else
            return 2;
    }
    
    unsigned char GetBitAt(int atBit)
    {
        //if not out of range
        if(length < atBit)
        {
            //find current byte
            int byte = atBit>>3;
            assert(byte < maxCharLength);
            int position = 7-atBit%8;
            return (bitSequence.get()[byte]>>position) & 1;
        }  
        return 2;
    }
    
    void FlushBits()
    {
        if(flushed)
            return;
        //move the rest of bits to the left 
        int trail = length%8;
        if(trail)
        {
            //shift last char to left 8-trail positions
            bitSequence.get()[length>>3] <<= (8-trail);
        }
        flushed = true;
    }
    void UnflushBits()
    { 
        if(!flushed)
            return;
        int trail = length%8;
        if(trail)
        {
            //shift bits back to the right
            bitSequence.get()[length>>3] >>= (8-trail);
        }
        flushed = false;
    }
    
    std::string toString()
    {
        std::stringstream stringStream;
        
        //treat the last few bits special
        int trail = length%8;
        
        for(int i=0; i<length-trail; i++)
        {
            //find current byte
            int byte = i>>3;
            assert(byte < maxCharLength);
            //output current 
            int position = 7-i%8;
            if(bitSequence.get()[byte] & 1<<position )
                stringStream << '1';
            else
                stringStream << '0';
        }  
        //UnflushBits();
        for(int i=length-trail; i<length; i++)
        {
            //find current byte
            int byte = i>>3;
            assert(byte < maxCharLength);
            //output current 
            int position = trail-1-i%8;
            if(bitSequence.get()[byte] & 1<<position )
                stringStream << '1';
            else
                stringStream << '0';
        }
        //FlushBits();
        return stringStream.str();
    }
};

class Codeword : public BitStream
{
public:
    Codeword() : BitStream(MAXCODEWORDLENGTH) {}
    Codeword Clone()
    {
        Codeword word; 
        memcpy( word.bitSequence.get(), bitSequence.get(), maxCharLength);
        word.length = length;
        return word;
    }
};

typedef std::multimap<float, HuffNodePtr> HuffNodeMap;
typedef std::pair<float, HuffNodePtr> HuffNodePair;

typedef std::map<CoeffType, Codeword> CodewordMap;
typedef std::pair<CoeffType, Codeword> CodewordPair;

typedef std::pair<CoeffType, bool> CoeffPair;

class CompressorHuffman : public Compressor
{
public:
    CompressorHuffman();
    virtual Packet Compress(CoeffView3D& subcube, Coords3D& location, Channel channel, int cubeNumer);
    virtual CoeffArray3DPtr Decompress(Packet& packet, Coords3D& subcubeSize);
    ///return the dictionary build off the tree
    CodewordMap& GetDictionary();
    ///return a codeword for a symbol;
    Codeword GetCodeword(CoeffType);
    ///returns symbol if bool is true
    ///and bool value determining if the actual symbol was reached, false if not 
    CoeffPair GetSymbol(unsigned char bit);
    ///discard the codeword currently being decoded
    void ResetWord();
private:
    HuffNodePtr GenerateTree();
    bool BuildDictionary(HuffNodePtr& tree, Codeword word);
    CodewordMap dictionary;
    HuffNodePtr tree;
    HuffNodePtr currentNode;
};

#endif	/* COMPRESSORHUFFMAN_H */

