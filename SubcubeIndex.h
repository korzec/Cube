/* 
 * File:   SubcubeIndex.h
 * Author: korzec
 *
 * Created on July 31, 2011, 7:25 PM
 */

#ifndef SUBCUBEINDEX_H
#define	SUBCUBEINDEX_H

#include "types.h"
#include "Subcube.h"
bool dumpSubcubes(SubcubeArray3D& subcubes, FloatArray3D& weights, std::string fileName);

///stores an 3D array of Subcube (#SubcubeArray3D)
class SubcubeIndex
{
public:
    SubcubeIndex();
    SubcubeIndex(CoeffView3D& cube, Coords3D size );
    void Init(CoeffView3D& cube, Coords3D subSize );
    Subcube& GetSubcube(Coords3D index);
    void ComputeWeights();
    bool dump(std::string);
private:
    SubcubeArray3D list;
    FloatArray3D weights;
    
};

#endif	/* SUBCUBEINDEX_H */

