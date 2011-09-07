/* 
 * File:   CompressorAC.h
 * Author: korzec
 *
 * Created on August 21, 2011, 7:50 AM
 */

#ifndef COMPRESSORCOPY_H
#define	COMPRESSORCOPY_H

#include "Compressor.h"

class CompressorCopy : public Compressor
{
public:
    CompressorCopy();
    virtual Packet Compress(CoeffView3D& subcube, Coords3D& location, Channel channel, int cubeNumer);
    virtual CoeffArray3DPtr Decompress(Packet& packet, Coords3D& subcubeSize);
private:

};

#endif	/* COMPRESSORCOPY_H */

