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

/// performs a 3d transform on a GOP
class CoeffCube {
private:
    CoeffArray3D* arrayY;
    int CubeNumber;
public:
    CoeffCube();
    CoeffCube(int width, int height, int depth);
    
    CoeffCube(const CoeffCube& orig);
    virtual ~CoeffCube();

    CoeffArray3D& Y();
    
    bool LoadGOP(PictureVector& gop);
    
    void Forward();
    void Backward();

    /// Load images and pad the data to allow wavelet transform
    void LoadImages(PictureVector pictures);
    /// returns Y array dimensions
    Coords3D Dimensionality();
    
    void Split();
    void Synth();
    void Interleave();
    void DeInterleave();

};

#endif	/* COEFFCUBE_H */

