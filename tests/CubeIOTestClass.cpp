/*
 * File:   CubeIOTestClass.cpp
 * Author: korzec
 *
 * Created on Aug 13, 2011, 9:14:18 PM
 */

#include "CubeIOTestClass.h"
#include <CubeIO.h>


CPPUNIT_TEST_SUITE_REGISTRATION(CubeIOTestClass);

CubeIOTestClass::CubeIOTestClass()
{
}

CubeIOTestClass::~CubeIOTestClass()
{
}

void CubeIOTestClass::setUp()
{
}

void CubeIOTestClass::tearDown()
{
}

void CubeIOTestClass::testCubeIO()
{
    std::cout << std::endl;
    CubeIO cubeIO();
}
void CubeIOTestClass::testCubeIO2()
{
    std::cout << std::endl;
    std::string fileName = "supertest1";
    bool isWrite = true;
    CubeIO cubeIO(fileName, isWrite);
}

void CubeIOTestClass::testFinish()
{
    std::cout << std::endl;
    CubeIO cubeIO;
    bool result = cubeIO.Finish();
    CPPUNIT_ASSERT(result);
}

void CubeIOTestClass::testInit()
{
    std::cout << std::endl;
    {
        std::string fileName = "TestFile333";
        bool isWrite = true;
        CubeIO cubeIO;
        bool result = cubeIO.Init(fileName, isWrite);
        CPPUNIT_ASSERT(result);
    }
    {
        std::string fileName = "TestFile333";
        bool isWrite = false;
        CubeIO cubeIO;
        bool result = cubeIO.Init(fileName, isWrite);
        CPPUNIT_ASSERT(result);
    }
}

void CubeIOTestClass::testReadCubeHeader()
{
    int cubeNumber;
    CubeIO cubeIO;
    //bool result = cubeIO.ReadCubeHeader(cubeNumber);
}

void CubeIOTestClass::testReadPacket()
{
    CubeIO cubeIO;
    //Packet result = cubeIO.ReadPacket();
}

void CubeIOTestClass::testReadSequenceHeader()
{
    CodingParams p0;
    VideoParams p1;
    CubeIO cubeIO;
    //bool result = cubeIO.ReadSequenceHeader(p0, p1);
}

void CubeIOTestClass::testWriteCubeHeader()
{
    int cubeNumber;
    CubeIO cubeIO;
    //bool result = cubeIO.WriteCubeHeader(cubeNumber);
}

void CubeIOTestClass::testWritePacket()
{
    Packet p0;
    CubeIO cubeIO;
    //bool result = cubeIO.WritePacket(p0);
}

void CubeIOTestClass::testWriteSequenceHeader()
{
    
    std::cout << std::endl;
    CodingParams codingParams;
    Coords3D dims(100,20,4);
    Coords3D subDims(20,20,4);
    codingParams.cubeSize = dims;
    codingParams.subcubeSize = subDims;
    codingParams.levels = 2;
    
    VideoParams videoParams;
    videoParams.fpsDenominator = 1;
    videoParams.fpsNumerator = 30;
    videoParams.frameCount = 100;
    
    std::string fileName = "TestFile444";
    bool result;
    
    {//case without opening a file
        CubeIO cubeIO;
        bool result = cubeIO.WriteSequenceHeader(codingParams, videoParams);
        CPPUNIT_ASSERT(result == false);
    }
    {//case with writing a file
        CubeIO cubeIO;
        result = cubeIO.Init(fileName, true);
        CPPUNIT_ASSERT(result);
        result = cubeIO.WriteSequenceHeader(codingParams, videoParams);
        CPPUNIT_ASSERT(result);
    }
    {//case with reading a file
        CubeIO cubeIO;
        cubeIO.Init(fileName, false);
        
        CodingParams codingP2;
        VideoParams videoP2;
        
        bool result = cubeIO.ReadSequenceHeader(codingP2, videoP2);
        CPPUNIT_ASSERT(result);
        CPPUNIT_ASSERT_EQUAL(codingParams.levels, codingP2.levels);
        CPPUNIT_ASSERT_EQUAL(codingParams.subcubeSize.Volume(), codingP2.subcubeSize.Volume());
        CPPUNIT_ASSERT_EQUAL(codingParams.cubeSize.Volume(), codingP2.cubeSize.Volume());
        
        //check if codingParamsAre the same;
        
        //TODO: codingParams should be separated from runtime encoder switches etc
    }
}

