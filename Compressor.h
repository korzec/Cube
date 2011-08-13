/* 
 * File:   Compressor.h
 * Author: korzec
 *
 * Created on August 12, 2011, 8:14 PM
 */

#ifndef COMPRESSOR_H
#define	COMPRESSOR_H

#include "types.h"
#include "Packet.h"
///compresses the Subcube data, can be subclassed to change the compression algorithm
class Compressor
{
public:
    Compressor(); 
    virtual Packet Compress(CoeffView3D& subcube, Coords3D& lcoation);
    virtual CoeffArray3DPtr Decompress(Packet packet);
    
private:

};

#endif	/* COMPRESSOR_H */

