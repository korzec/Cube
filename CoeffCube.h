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
    int CubeNumber;
    WaveletTransform transform;
public:
    CoeffCube();
    CoeffCube(int width, int height, int depth);
    
    CoeffArray3D& Y();
    
    bool LoadGOP(PictureVector& gop);
    
    bool ForwardTransform();
    bool ReverseTransform();

    /// Load images and pad the data to allow wavelet transform
    void LoadImages(PictureVector pictures);
    /// returns Y array dimensions
    Coords3D Dimensionality();

};

#endif	/* COEFFCUBE_H */

