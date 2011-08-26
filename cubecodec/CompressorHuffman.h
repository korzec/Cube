/* 
 * File:   CompressorHuffman.h
 * Author: korzec
 *
 * Created on August 22, 2011, 12:47 AM
 */

#ifndef COMPRESSORHUFFMAN_H
#define	COMPRESSORHUFFMAN_H

#include "Compressor.h"
#include "BitStream.h"
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

class Codeword : public BitStream
{
public:
    Codeword();
    Codeword Clone();
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
    
    CoeffPair GetSymbol(unsigned long int& atBit, BitStream stream );
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

