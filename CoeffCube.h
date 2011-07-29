/* 
 * File:   CoeffCube.h
 * Author: korzec
 *
 * Created on July 17, 2011, 9:17 PM
 */

#ifndef COEFFCUBE_H
#define	COEFFCUBE_H

#include "types.h"
#include <vector>
#include <boost/multi_array.hpp>
#include "WaveletTransform.h"

/// performs a 3d transform on a GOP
class CoeffCube {
private:
    CoeffArray3DPtr arrayY;
    CoeffArray3DPtr arrayU;
    CoeffArray3DPtr arrayV;
    WaveletTransform transform;
    /// available to receive next picture
    bool available;
    ///the index of slice pointing to next available space (where next picture will be copied)
    int nextIndex;
public:
    CoeffCube();
    CoeffCube(int width, int height, int depth);
    
    CoeffArray3D& Y();
    CoeffArray3D& U();
    CoeffArray3D& V();
    
    bool LoadNextPicture(Picture&);
    bool MakeAvailable();
    
    /// Load images and pad the data to allow wavelet transform
    bool LoadGOP(PictureVector& gop);
    
    PictureVectorPtr GetGOP();
    
    bool ForwardTransform();
    bool ReverseTransform();

    /// returns Y array dimensions
    Coords3D Dimensionality();
    
    Coords3D ChromaDimensionality();

};

#endif	/* COEFFCUBE_H */

