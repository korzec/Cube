/*
 * File:   CompressorHuffmanTestClass.h
 * Author: korzec
 *
 * Created on Aug 22, 2011, 8:13:02 PM
 */

#ifndef COMPRESSORHUFFMANTESTCLASS_H
#define	COMPRESSORHUFFMANTESTCLASS_H

#include <cppunit/extensions/HelperMacros.h>

class CompressorHuffmanTestClass : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(CompressorHuffmanTestClass);

    //CPPUNIT_TEST(testMethod);
    //CPPUNIT_TEST(testFailedMethod);

    CPPUNIT_TEST_SUITE_END();

public:
    CompressorHuffmanTestClass();
    virtual ~CompressorHuffmanTestClass();
    void setUp();
    void tearDown();

private:
    void testGenerateTree();
    void testFailedMethod();
};

#endif	/* COMPRESSORHUFFMANTESTCLASS_H */

