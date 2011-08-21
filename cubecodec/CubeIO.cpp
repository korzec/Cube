/* 
 * File:   CubeIO.cpp
 * Author: korzec
 * 
 * Created on August 12, 2011, 7:38 PM
 */

#include "CubeIO.h"

CubeIO::CubeIO()
{
}

CubeIO::CubeIO(std::string fileName, bool isWrite)
{
    Init(fileName, isWrite);
}

bool CubeIO::Init(std::string fileName, bool isWrite)
{
    if (outputFile || inputFile)
        return false;
    if (isWrite)
    {
        outputFile = new std::ofstream(fileName.c_str(), std::ios::out | std::ios::binary);
        return !outputFile->fail();
    }
    else
    {
        inputFile = new std::ifstream(fileName.c_str(), std::ios::in | std::ios::binary);
        return !inputFile->fail();
    }
}

bool CubeIO::Finish()
{
    bool state;
    if (outputFile)
    {
        ((std::ofstream*)outputFile)->close();
        state = ! outputFile->fail();
    }
    else if (inputFile)
    {
        ((std::ifstream*)inputFile)->close();
        state = ! inputFile->fail();
    }
    else
        state = true;
    inputFile = NULL;
    outputFile = NULL;
    return state;
}

CubeIO::~CubeIO()
{
    Finish();
    
}
