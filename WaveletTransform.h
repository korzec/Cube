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
    
    bool Forward(CoeffView3D&);    
    bool Reverse(CoeffView3D&);
    
private:
    
    //trasform a single slice;
    bool ForwardSlice(CoeffView3D& cube, int slice);

    bool Split(CoeffView3D&);
    
    bool Synth(CoeffView3D&);
    
    bool Deinterleave(CoeffView3D&);
    
    bool Interleave(CoeffView3D&);
    
    bool deinterleave1d(CoeffView3D&);
};

#endif	/* WAVELETTRANSFORM_H */

