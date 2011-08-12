/* 
 * File:   Packet.h
 * Author: korzec
 *
 * Created on August 12, 2011, 7:40 PM
 */

#ifndef PACKET_H
#define	PACKET_H

#include "types.h"
#include "Subcube.h"
#include "Compressor.h"

///Stores compressed Subcube data
class Packet
{
public:
    Packet(Compressor compressor);
private:
    Compressor compressor;
    ucharPtr CompressedData;
    CoeffArray3DPtr SubcubeData;
    int compressedSize;
    
};

#endif	/* PACKET_H */

