/*
 * File:   PictureTest.h
 * Author: korzec
 *
 * Created on Jul 17, 2011, 7:20:01 PM
 */

#ifndef PICTURETEST_H
#define	PICTURETEST_H

#include <cppunit/extensions/HelperMacros.h>

class PictureTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(PictureTest);

    CPPUNIT_TEST(testPicture);
    CPPUNIT_TEST(testPicture2);
    CPPUNIT_TEST(testPicture3);
    CPPUNIT_TEST(testY);
    CPPUNIT_TEST(testHeight);
    CPPUNIT_TEST(testWidth);

    CPPUNIT_TEST_SUITE_END();

public:
    PictureTest();
    virtual ~PictureTest();
    void setUp();
    void tearDown();

private:
    void testPicture();
    void testPicture2();
    void testPicture3();
    void testY();
    void testHeight();
    void testWidth();

};

#endif	/* PICTURETEST_H */

