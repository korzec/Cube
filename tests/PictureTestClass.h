/*
 * File:   PictureTestClass.h
 * Author: korzec
 *
 * Created on Aug 14, 2011, 11:59:03 AM
 */

#ifndef PICTURETESTCLASS_H
#define	PICTURETESTCLASS_H

#include <cppunit/extensions/HelperMacros.h>

class PictureTestClass : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(PictureTestClass);

    CPPUNIT_TEST(testMethod);
    CPPUNIT_TEST(testFailedMethod);

    CPPUNIT_TEST_SUITE_END();

public:
    PictureTestClass();
    virtual ~PictureTestClass();
    void setUp();
    void tearDown();

private:
    void testMethod();
    void testFailedMethod();
};

#endif	/* PICTURETESTCLASS_H */

