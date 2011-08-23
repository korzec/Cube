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
    BuildDictionary(tree, Codeword() );
    ResetWord();
}

HuffNodePtr CompressorHuffman::GenerateTree()
{
    HuffNodeMap queue;
    //generate statistics for the context : asume HHH context
    //generate probability value for all symbols for range {x AND .....1111111111..}
    for(short symbol = -1024; symbol < 1024; symbol+=4)
    {
        HuffNodePtr node = HuffNodePtr(new HuffNode());
        node->symbol = symbol;
        if(symbol == 0)
            node->weight = FLT_MAX;
        else
            node->weight = 1./fabs(symbol);
        queue.insert(HuffNodePair(node->weight,node));
    }
    //build huffman tree using the queue
    while(queue.size() > 1)
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
        queue.insert(HuffNodePair(node->weight, node) );
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
    if(tree->left.use_count() > 0)
    {
        Codeword newWord = word.Clone();
        newWord.insertBit(0);
        ret = ret && BuildDictionary(tree->left, newWord);
    }
    if(tree->right.use_count() > 0)
    {
        Codeword newWord = word.Clone();
        newWord.insertBit(1);
        ret = ret && BuildDictionary(tree->right, newWord);
    }
    //if its leaf add the codeword to the dictionary
    if(tree->right.use_count() == 0 && tree->left.use_count() == 0)
    {
        return dictionary.insert(CodewordPair(tree->symbol, word)).second;
    }
    return ret;
}

CodewordMap& CompressorHuffman::GetDictionary()
{
    return dictionary;
}

Packet CompressorHuffman::Compress(CoeffView3D& subcube, Coords3D& location, Channel channel, int cubeNumer)
{
    //get pointer to actual data and length of data
    CoeffArray3D array(subcube);
    Coords3D dims(array.shape());
    unsigned int fullSize = dims.Volume()*sizeof(CoeffType);
    CoeffType* cubeData = (CoeffType*)array.data();
    //allocate data for compression : not more than the input?
    BitStream compressedData(fullSize);
    
    Codeword word = GetCodeword(cubeData[0]);
    
    //BitStream.insertBitStream();
    //read
    
    //DANGER: endianess might mix up
    
    //compress the symbols and track the size of output
    return Packet();
}
CoeffArray3DPtr CompressorHuffman::Decompress(Packet& packet, Coords3D& subcubeSize)
{
    return CoeffArray3DPtr();
}

void CompressorHuffman::ResetWord()
{
    currentNode = tree;
}

CoeffPair CompressorHuffman::GetSymbol(unsigned char bit)
{
    if(bit)
        currentNode = currentNode->right;
    else
        currentNode = currentNode->left;
    if(currentNode->left.get() == NULL && currentNode->right.get() == NULL)
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