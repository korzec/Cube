/*
 * File:   CompressorTestClass.cpp
 * Author: korzec
 *
 * Created on Aug 13, 2011, 5:55:10 AM
 */

#include "CompressorTestClass.h"
#include "../Compressor.h"


CPPUNIT_TEST_SUITE_REGISTRATION(CompressorTestClass);

CompressorTestClass::CompressorTestClass()
{
}

CompressorTestClass::~CompressorTestClass()
{
}

void CompressorTestClass::setUp()
{
}

void CompressorTestClass::tearDown()
{
}

void CompressorTestClass::testCompress()
{
    Coords3D dims(16,32,4);
    CoeffArray3D array(extents[dims.depth][dims.height][dims.width]);
    CoeffView3D subcubeView =  array[ indices[range()][range()][range()] ];
    
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                array[d][h][w] = (CoeffType)d*h*w;
            }//w
        }//h
    }//d
    
    Coords3D location(4,4,4);
    Compressor compressor;
    Packet packet = compressor.Compress(subcubeView, location);
    if (true /*check result*/)
    {
        CPPUNIT_ASSERT(packet.compressedData.use_count() > 0);
        CPPUNIT_ASSERT(packet.location.depth == location.depth);
        CPPUNIT_ASSERT(packet.location.height == location.height);
        CPPUNIT_ASSERT(packet.location.width == location.width);
        CPPUNIT_ASSERT(packet.fullSize == Coords3D(array.shape()).Volume()*sizeof(CoeffType));
        std::cout << std::endl;
        std::cout << "array size " << Coords3D(array.shape()).Volume() << std::endl;
        std::cout << "fullSize " << packet.fullSize << std::endl;
        std::cout << "compressed size " << packet.compressedSize << std::endl;
        //LZO can expand input
        //CPPUNIT_ASSERT(packet.compressedSize <= packet.fullSize);
    }
}

void CompressorTestClass::testCompressor()
{
    Compressor compressor();
    if (true /*check result*/)
    {
        //CPPUNIT_ASSERT(false);
    }
}

void CompressorTestClass::testDecompress()
{    
    Coords3D dims(16,32,4);
    CoeffArray3D array(extents[dims.depth][dims.height][dims.width]);
    CoeffView3D subcubeView =  array[ indices[range()][range()][range()] ];
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                array[d][h][w] = (CoeffType)rand();
            }//w
        }//h
    }//d
    
    Coords3D location(4,4,4);
    Compressor compressor;
    Packet packet = compressor.Compress(subcubeView, location);
    
    CoeffArray3DPtr newArray = compressor.Decompress(packet, dims);
    
    if (true /*check result*/)
    {
        CPPUNIT_ASSERT(dims.Volume() == Coords3D(newArray->shape()).Volume());
        for (int d = 0; d < dims.depth; d++)
        {
            for (int h = 0; h < dims.height; h++)
            {
                for (int w = 0; w < dims.width; w++)
                {
                    CPPUNIT_ASSERT(array[d][h][w] == (*newArray)[d][h][w]);
                }//w
            }//h
        }//d
    }
}

