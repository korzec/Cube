/*
 * File:   PictureTest.cpp
 * Author: korzec
 *
 * Created on Jul 17, 2011, 7:20:03 PM
 */

#include "PictureTest.h"
#include "types.h"


CPPUNIT_TEST_SUITE_REGISTRATION(PictureTest);

PictureTest::PictureTest() {
}

PictureTest::~PictureTest() {
}

void PictureTest::setUp() {
}

void PictureTest::tearDown() {
}

void PictureTest::testPicture() {
    Picture picture();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void PictureTest::testPicture2() {
    FrameBuffer* _frame = NULL;
    Picture picture(_frame);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void PictureTest::testPicture3() {
    int width;
    int height;
    Picture picture(width, height);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void PictureTest::testY() {
    Picture picture;
    ValueArray2Dref& result = picture.Y();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void PictureTest::testHeight() {
    Picture picture;
    int result = picture.height();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void PictureTest::testWidth() {
    Picture picture;
    int result = picture.width();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

