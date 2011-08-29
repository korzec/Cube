/*
 * File:   CompressorHuffmanTestClass.cpp
 * Author: korzec
 *
 * Created on Aug 22, 2011, 8:13:03 PM
 */

#include "CompressorHuffmanTestClass.h"
#include "../cubecodec/CompressorHuffman.h"


CPPUNIT_TEST_SUITE_REGISTRATION(CompressorHuffmanTestClass);

CompressorHuffmanTestClass::CompressorHuffmanTestClass()
{
}

CompressorHuffmanTestClass::~CompressorHuffmanTestClass()
{
}

void CompressorHuffmanTestClass::setUp()
{
}

void CompressorHuffmanTestClass::tearDown()
{
}

void CompressorHuffmanTestClass::testGenerateTree()
{
    CompressorHuffman compressor;
    CoeffPair symbolPair = compressor.GetSymbol(0);
    CPPUNIT_ASSERT(true);
}

void CompressorHuffmanTestClass::testFailedMethod()
{
    //CPPUNIT_ASSERT(false);
}

