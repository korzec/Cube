/* 
 * File:   CompressorLZO.h
 * Author: korzec
 *
 * Created on August 21, 2011, 7:50 AM
 */

#ifndef COMPRESSORLZO_H
#define	COMPRESSORLZO_H

#include "Compressor.h"

class CompressorLZO : public Compressor
{
public:
    CompressorLZO();
    virtual Packet Compress(CoeffView3D& subcube, Coords3D& location, Channel channel, int cubeNumer);
    virtual CoeffArray3DPtr Decompress(Packet& packet, Coords3D& subcubeSize);
private:

};

#endif	/* COMPRESSORLZO_H */

