/* 
 * File:   Compressor.h
 * Author: korzec
 *
 * Created on August 12, 2011, 8:14 PM
 */

#ifndef COMPRESSOR_H
#define	COMPRESSOR_H

#include "types.h"
///compresses the Subcube data, can be subclassed to change the compression algorithm
class Compressor
{
public:
    Compressor(); 
    virtual ucharPtr Compress(CoeffArray3DPtr subcube, int& compressedSize);
    virtual CoeffArray3DPtr Decompress(ucharPtr compressedData, int compressedSize);
    
private:

};

#endif	/* COMPRESSOR_H */

