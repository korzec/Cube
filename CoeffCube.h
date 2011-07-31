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
#include "WaveletTransform.h"
#include "SubbandList.h"

/// performs a 3d transform on a GOP
class CoeffCube {
private:
    CoeffArray3DPtr arrayY;
    CoeffArray3DPtr arrayU;
    CoeffArray3DPtr arrayV;
    WaveletTransform transform;
    
    SubbandList subbandsY;
    SubbandList subbandsU;
    SubbandList subbandsV;
    
    /// available to receive next picture
    bool available;
    int cubeNumber;
    ///the index of slice pointing to next available space (where next picture will be copied)
    int nextIndex;
public:
    CoeffCube();
    CoeffCube(int width, int height, int depth, int levels);
    
    CoeffArray3D& Y();
    CoeffArray3D& U();
    CoeffArray3D& V();
    
    int GetLevel();
    
    bool LoadNextPicture(Picture&);
    bool MakeAvailable();
    
    /// Load images and pad the data to allow wavelet transform
    bool LoadGOP(PictureVector& gop);
    
    PictureVectorPtr GetGOP();
    
    bool ForwardTransform();
    bool ReverseTransform();
    
    bool SmoothTime();

    /// returns Y array dimensions
    Coords3D Dimensionality();
    
    Coords3D ChromaDimensionality();

    bool dump(std::string);
};

#endif	/* COEFFCUBE_H */

