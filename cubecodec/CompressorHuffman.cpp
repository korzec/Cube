/* 
 * File:   CompressorHuffman.cpp
 * Author: korzec
 * 
 * Created on August 22, 2011, 12:47 AM
 */

#include <float.h>

#include "CompressorHuffman.h"

CompressorHuffman::CompressorHuffman()
{
    tree = GenerateTree();
    BuildDictionary(tree, Codeword());
    ResetWord();
}

HuffNodePtr CompressorHuffman::GenerateTree()
{
    HuffNodeMap queue;
    //generate statistics for the context : asume HHH context
    //generate probability value for all symbols for range {x AND .....1111111111..}
    for (short symbol = -32768;; symbol += 1) // !!!!!!!!
    {
        HuffNodePtr node = HuffNodePtr(new HuffNode());
        node->symbol = symbol;
        if (symbol == 0)
            node->weight = 1;
        else
            node->weight = 1. / fabs(symbol);
        queue.insert(HuffNodePair(node->weight, node));
        if (symbol == 32767)
            break;
    }
    //build huffman tree using the queue
    while (queue.size() > 1)
    {
        HuffNodePtr node = HuffNodePtr(new HuffNode());
        node->symbol = 666;
        //add next node as a left branch and remove from queue
        node->left = queue.begin()->second;
        queue.erase(queue.begin());
        //add next node as right branch and remove from queue
        node->right = queue.begin()->second;
        queue.erase(queue.begin());
        //set new weights to be the sum of children's weights
        node->weight = node->left->weight + node->right->weight;
        //insert node back in the queue
        queue.insert(HuffNodePair(node->weight, node));
    }
    //now we have a full huffman tree for our context 
    HuffNodePtr tree = queue.begin()->second;

    return tree;
    //now build a static map with symbols and their coding values

}

bool CompressorHuffman::BuildDictionary(HuffNodePtr& tree, Codeword word)
{
    //traverse all the tree to find all symbols and store their codewords
    //map symbol to its codeword
    bool ret = true;
    if (tree->left.use_count() > 0)
    {
        Codeword newWord = word.Clone();
        newWord.insertBit(0);
        ret = ret && BuildDictionary(tree->left, newWord);
    }
    if (tree->right.use_count() > 0)
    {
        Codeword newWord = word.Clone();
        newWord.insertBit(1);
        ret = ret && BuildDictionary(tree->right, newWord);
    }
    //if its leaf add the codeword to the dictionary
    if (tree->right.use_count() == 0 && tree->left.use_count() == 0)
    {
        return dictionary.insert(CodewordPair(tree->symbol, word)).second;
    }
    return ret;
}

CodewordMap& CompressorHuffman::GetDictionary()
{
    return dictionary;
}

Packet CompressorHuffman::Compress(CoeffView3D& subcube, Coords3D& location, Channel channel, int cubeNumber)
{ //NOTE: endianess might mix up
    //get pointer to actual data and length of data
    CoeffArray3D array(subcube);
    Coords3D dims(array.shape());
    unsigned int fullSize = dims.Volume() * sizeof (CoeffType);
    CoeffType* cubeData = (CoeffType*) array.data();
    //allocate data for compression : not more than the input?
    BitStream compressedData(fullSize);

    //loop through all values and output codewords to the compression buffer
    int symbolCount = fullSize / sizeof (CoeffType);
    for (int i = 0; i < symbolCount; i++)
    {
        compressedData.insertBitStream(GetCodeword(cubeData[i]));
    }

    int compressedSize = compressedData.ByteSize();
    Packet packet;
    packet.compressedData = compressedData.GetSequence();
    packet.header.cubeNumer = cubeNumber;
    packet.header.channel = channel;
    packet.header.compressedSize = compressedSize;
    packet.header.fullSize = fullSize; //redundant
    packet.header.location = location;

    return packet;
}

CoeffArray3DPtr CompressorHuffman::Decompress(Packet& packet, Coords3D& subcubeSize)
{
    //allocate memory for decompressed subcube array
    assert(packet.compressedData.use_count() > 0);
    assert(packet.header.compressedSize > 0);
    unsigned int fullSize;
    unsigned int compressedSize;
    //int newSize;

    fullSize = subcubeSize.Volume() * sizeof (CoeffType);
    assert(packet.header.fullSize == fullSize); //redundant
    compressedSize = packet.header.compressedSize;

    CoeffArray3DPtr array = CoeffArray3DPtr(new CoeffArray3D(
                                                             boost::extents[subcubeSize.depth][subcubeSize.height][subcubeSize.width]));
    //get array memory pointer
    CoeffType* cubeData = (CoeffType*) array->data();
    //map the compressed data to BitStream
    BitStream compressedData(compressedSize, packet.compressedData);
    //read bit by bit and write coeffs as they get decoded
    //read exact number of symbols needed and discard any trailing bits
    int symbolCount = fullSize / sizeof (CoeffType);
    for (int i = 0, symbols = 0; symbols < symbolCount; i++)
    {
        //TODO: fix endless loop if the input is wrong
        CoeffPair coeffPair = this->GetSymbol(compressedData.GetBitAt(i));
        if (coeffPair.second)
        {
            cubeData[symbols] = coeffPair.first;
            symbols++;
        }
    }
    return array;
}

inline void CompressorHuffman::ResetWord()
{
    currentNode = tree;
}

CoeffPair CompressorHuffman::GetSymbol(unsigned long int& atBit, BitStream stream )
{
    //starting at atBit decode next symbol
    stream.GetBitAt(atBit);
    /*TODO: return value*/return CoeffPair(0, false);
}

CoeffPair CompressorHuffman::GetSymbol(unsigned char bit)
{
    if (bit)
        currentNode = currentNode->right;
    else
        currentNode = currentNode->left;
    if (currentNode->left.get() == NULL && currentNode->right.get() == NULL)
    {
        CoeffPair result(currentNode->symbol, true);
        ResetWord();
        return result;
    }
    return CoeffPair(0, false);
}

Codeword CompressorHuffman::GetCodeword(CoeffType symbol)
{
    return dictionary.at(symbol);
}

//the bitstream members


//codeword
Codeword::Codeword() : BitStream(MAXCODEWORDLENGTH) {}
Codeword Codeword::Clone()
{
    Codeword word; 
    memcpy( word.bitSequence.get(), bitSequence.get(), maxByteLength);
    word.length = length;
    return word;
}