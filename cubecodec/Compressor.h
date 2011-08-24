/* 
 * File:   Compressor.h
 * Author: korzec
 *
 * Created on August 12, 2011, 8:14 PM
 */

#ifndef COMPRESSOR_H
#define	COMPRESSOR_H

#include "arrays.h"
#include "Packet.h"

class Compressor;

typedef boost::shared_ptr<Compressor> CompressorPtr;

///compresses the Subcube data, abstract 
class Compressor
{
public:
    virtual Packet Compress(CoeffView3D& subcube, Coords3D& location, Channel channel, int cubeNumer) =0;
    virtual CoeffArray3DPtr Decompress(Packet& packet, Coords3D& subcubeSize) =0;
};

#endif	/* COMPRESSOR_H */

