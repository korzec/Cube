/*
 * File:   CubeIOTestClass.h
 * Author: korzec
 *
 * Created on Aug 13, 2011, 9:14:17 PM
 */

#ifndef CUBEIOTESTCLASS_H
#define	CUBEIOTESTCLASS_H

#include <cppunit/extensions/HelperMacros.h>

class CubeIOTestClass : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(CubeIOTestClass);

    CPPUNIT_TEST(testCubeIO);
    CPPUNIT_TEST(testCubeIO2);
    CPPUNIT_TEST(testFinish);
    CPPUNIT_TEST(testInit);
    CPPUNIT_TEST(testReadCubeHeader);
    CPPUNIT_TEST(testReadPacket);
    CPPUNIT_TEST(testReadSequenceHeader);
    CPPUNIT_TEST(testWriteCubeHeader);
    CPPUNIT_TEST(testWritePacket);
    CPPUNIT_TEST(testWriteSequenceHeader);

    CPPUNIT_TEST_SUITE_END();

public:
    CubeIOTestClass();
    virtual ~CubeIOTestClass();
    void setUp();
    void tearDown();

private:
    void testCubeIO();
    void testCubeIO2();
    void testFinish();
    void testInit();
    void testReadCubeHeader();
    void testReadPacket();
    void testReadSequenceHeader();
    void testWriteCubeHeader();
    void testWritePacket();
    void testWriteSequenceHeader();

};

#endif	/* CUBEIOTESTCLASS_H */

