/* 
 * File:   CubeIO.h
 * Author: korzec
 *
 * Created on August 12, 2011, 7:38 PM
 */

#ifndef CUBEIO_H
#define	CUBEIO_H

#include "CubeStream.h"

/// Reads and writes data encoded with cube codec
class CubeIO : public CubeStream
{
public:
    CubeIO();
    CubeIO(std::string fileName, bool isWrite);
    virtual bool Init(std::string fileName, bool isWrite);
    virtual ~CubeIO();
    virtual bool Finish();

private: 
};

#endif	/* CUBEIO_H */

