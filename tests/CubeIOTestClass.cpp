/*
 * File:   CubeIOTestClass.cpp
 * Author: korzec
 *
 * Created on Aug 13, 2011, 9:14:18 PM
 */

#include "CubeIOTestClass.h"
#include "../CubeIO.h"


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
    std::stringstream ss1; ss1 << OUTDIR << "TestCubeIO";
    std::string fileName = ss1.str();
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
        std::stringstream ss1; ss1 << OUTDIR << "TestCubeIO";
        std::string fileName = ss1.str();
        bool isWrite = true;
        CubeIO cubeIO;
        bool result = cubeIO.Init(fileName, isWrite);
        CPPUNIT_ASSERT(result);
    }
    {
        std::stringstream ss1; ss1 << OUTDIR << "TestCubeIO";
        std::string fileName = ss1.str();
        bool isWrite = false;
        CubeIO cubeIO;
        bool result = cubeIO.Init(fileName, isWrite);
        CPPUNIT_ASSERT(result);
    }
}

void CubeIOTestClass::testReadCubeHeader()
{
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
    Parameters p0;
    VideoParams p1;
    CubeIO cubeIO;
    //bool result = cubeIO.ReadSequenceHeader(p0, p1);
}

void CubeIOTestClass::testWriteCubeHeader()
{
    std::cout << std::endl;
    std::stringstream ss1; ss1 << OUTDIR << "TestCubeIO";
    std::string fileName = ss1.str();
    int cubeNumber = 559;
    {
        bool isWrite = true;
        CubeIO cubeIO(fileName, isWrite);
        bool result = cubeIO.WriteCubeHeader(cubeNumber);
        CPPUNIT_ASSERT(result);
    }
    { //read and compare
        bool isWrite = false;
        CubeIO cubeIO(fileName, isWrite);
        int readNumber;
        bool result = cubeIO.ReadCubeHeader(readNumber);
        CPPUNIT_ASSERT(result);
        CPPUNIT_ASSERT_EQUAL(cubeNumber, readNumber);
    }
    //bool result = cubeIO.WriteCubeHeader(cubeNumber);
}

void CubeIOTestClass::testWritePacket()
{
    std::cout << std::endl;
    Packet packet;
    int size = 666;
    Coords3D dims(44,66,8);
    std::stringstream ss1; ss1 << OUTDIR << "TestCubeIO";
    std::string fileName = ss1.str();
    //init packet
    packet.compressedData = ucharPtr(new unsigned char[size]);
    packet.compressedSize = size;
    packet.fullSize = 999;
    packet.location = dims;
    
    //init payload
    for(int i=0; i < packet.compressedSize; i++)
    {   
        packet.compressedData.get()[i] = (char)rand();
    }
    {
        bool isWrite = true;
        CubeIO cubeIO(fileName, isWrite);
        bool result = cubeIO.WritePacket(packet);
        CPPUNIT_ASSERT(result);
    }
    { //read and compare
        bool isWrite = false;
        CubeIO cubeIO(fileName, isWrite);
        Packet newPacket = cubeIO.ReadPacket();
        CPPUNIT_ASSERT_EQUAL(packet.compressedSize, newPacket.compressedSize);
        CPPUNIT_ASSERT_EQUAL(packet.fullSize, newPacket.fullSize);
        CPPUNIT_ASSERT_EQUAL(packet.location.Volume(), newPacket.location.Volume());
        for(int i=0; i < packet.compressedSize; i++)
        {   
            CPPUNIT_ASSERT_EQUAL(packet.compressedData.get()[i],
                                 newPacket.compressedData.get()[i]);
        }
    }
    
    
    
    CubeIO cubeIO;
    //bool result = cubeIO.WritePacket(p0);
}

void CubeIOTestClass::testWriteSequenceHeader()
{
    
    std::cout << std::endl;
    Parameters parameters;
    Coords3D dims(100,20,4);
    Coords3D subDims(20,20,4);
    parameters.codecParams.cubeSize = dims;
    parameters.codecParams.subcubeSize = subDims;
    parameters.codecParams.levels = 2;
    
    VideoParams videoParams;
    videoParams.fpsDenominator = 1;
    videoParams.fpsNumerator = 30;
    videoParams.frameCount = 100;
    
    std::stringstream ss1; ss1 << OUTDIR << "TestCubeIO";
    std::string fileName = ss1.str();
    bool result;
    
    {//case without opening a file
        CubeIO cubeIO;
        bool result = cubeIO.WriteSequenceHeader(parameters, videoParams);
        CPPUNIT_ASSERT(result == false);
    }
    {//case with writing a file
        CubeIO cubeIO;
        result = cubeIO.Init(fileName, true);
        CPPUNIT_ASSERT(result);
        result = cubeIO.WriteSequenceHeader(parameters, videoParams);
        CPPUNIT_ASSERT(result);
    }
    {//case with reading a file
        CubeIO cubeIO;
        cubeIO.Init(fileName, false);
        
        Parameters codingP2;
        VideoParams videoP2;
        
        bool result = cubeIO.ReadSequenceHeader(codingP2, videoP2);
        CPPUNIT_ASSERT(result);
        CPPUNIT_ASSERT_EQUAL(parameters.codecParams.levels, codingP2.codecParams.levels);
        CPPUNIT_ASSERT_EQUAL(parameters.codecParams.subcubeSize.Volume(), codingP2.codecParams.subcubeSize.Volume());
        CPPUNIT_ASSERT_EQUAL(parameters.codecParams.cubeSize.Volume(), codingP2.codecParams.cubeSize.Volume());
        
        //check if parametersAre the same;
        
        //TODO: parameters should be separated from runtime encoder switches etc
    }
}

