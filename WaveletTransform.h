/* 
 * File:   WaveletTransform.h
 * Author: korzec
 *
 * Created on July 18, 2011, 8:44 PM
 */

#ifndef WAVELETTRANSFORM_H
#define	WAVELETTRANSFORM_H

#include "types.h"

class WaveletTransform
{
public:
    WaveletTransform();
    WaveletTransform(const WaveletTransform& orig);
    virtual ~WaveletTransform();
    
    
    bool Forward(CoeffArray3D&);    
    
    bool Reverse(CoeffArray3D&);
    
private:
    
    //trasform a single slice;
    bool ForwardSlice(CoeffArray3D& cube, int slice);

    bool Split(CoeffArray3D&);
    
    bool Synth(CoeffArray3D&);
    
    bool Deinterleave(CoeffArray3D&);
    
    bool Interleave(CoeffArray3D&);
    
    bool deinterleave1d(CoeffArray3D&);
};

#endif	/* WAVELETTRANSFORM_H */

