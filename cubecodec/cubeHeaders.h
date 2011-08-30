/* 
 * File:   cubeHeaders.h
 * Author: korzec
 *
 * Created on August 21, 2011, 8:53 AM
 */

#ifndef CUBEHEADERS_H
#define	CUBEHEADERS_H

#include "CodecParams.h"
#include "types.h"

#define CUBEHEADERCODE 0x0C
#define PACKETHEADERCODE 0x0B
#define SEQUENCEHEADERCODE 0x31304243//"CB01" in LE


class SequenceHeader
{
public:
    unsigned int headerCode;
    CodecParams codecParams;
    VideoParams videoParams;
};

class CubeHeader
{
public:
    unsigned char headerCode;
    int cubeNumber;
};

class PacketHeader
{
public:
    unsigned char headerCode;
    int cubeNumer;
    Coords3D location;
    Channel channel;
    unsigned int fullSize;
    unsigned int compressedSize;
    
};



#endif	/* CUBEHEADERS_H */

