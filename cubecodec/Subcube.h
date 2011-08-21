/* 
 * File:   Subcube.h
 * Author: korzec
 *
 * Created on July 17, 2011, 9:30 PM
 */

#ifndef SUBCUBE_H
#define	SUBCUBE_H

#include "arrays.h"
#include "types.h"


class SubcubeInfo
{
public:
    Channel channel;
    Coords3D location;
    Coords3D size;
};

///a small cube located in a CoeffCube data
class Subcube {
    SubcubeInfo info;
    CoeffView3D* cube;
    CoeffView3DPtr array;
public:
    Subcube();
    Subcube(CoeffView3D& cube, Coords3D& index, Coords3D& size, Channel channel);
    void Init(CoeffView3D& cube, Coords3D& index, Coords3D& size, Channel channel);
    Coords3D GetLocation();
    CoeffView3D& GetView();
    Coords3D GetSize();
    float GetWeight();
    CoeffView3D& GetParentView();
    Channel GetChannel();
    bool CopyNewValues(CoeffArray3DPtr);
};

#endif	/* SUBCUBE_H */

