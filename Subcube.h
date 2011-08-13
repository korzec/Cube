/* 
 * File:   Subcube.h
 * Author: korzec
 *
 * Created on July 17, 2011, 9:30 PM
 */

#ifndef SUBCUBE_H
#define	SUBCUBE_H

#include "types.h"

///a small cube located in a CoeffCube data
class Subcube {
    CoeffView3D* cube;
    Coords3D location;
    Coords3D size;
    CoeffView3DPtr array;
public:
    Subcube();
    Subcube(CoeffView3D& cube, Coords3D& index, Coords3D& size);
    void Init(CoeffView3D& cube, Coords3D& index, Coords3D& size);
    Coords3D GetLocation();
    CoeffView3D& GetView();
    Coords3D GetSize();
    float GetWeight();
    CoeffView3D& GetParentView();
};

#endif	/* SUBCUBE_H */

