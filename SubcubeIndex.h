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

typedef boost::multi_array<Subcube, 3> SubcubeArray3D;

class SubcubeIndex
{
public:
    SubcubeIndex();
    SubcubeIndex(CoeffView3D& cube, Coords3D size );
    void Init(CoeffView3D& cube, Coords3D size );
    Subcube GetSubcube(Coords3D index);
private:
    SubcubeArray3D list;
};

#endif	/* SUBCUBEINDEX_H */

