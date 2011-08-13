/*
 * File:   CompressorTestClass.h
 * Author: korzec
 *
 * Created on Aug 13, 2011, 5:55:10 AM
 */

#ifndef COMPRESSORTESTCLASS_H
#define	COMPRESSORTESTCLASS_H

#include <cppunit/extensions/HelperMacros.h>

class CompressorTestClass : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(CompressorTestClass);

    CPPUNIT_TEST(testCompress);
    CPPUNIT_TEST(testCompressor);
    CPPUNIT_TEST(testDecompress);

    CPPUNIT_TEST_SUITE_END();

public:
    CompressorTestClass();
    virtual ~CompressorTestClass();
    void setUp();
    void tearDown();

private:
    void testCompress();
    void testCompressor();
    void testDecompress();

};

#endif	/* COMPRESSORTESTCLASS_H */

