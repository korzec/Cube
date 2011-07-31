/* 
 * File:   Subcube.h
 * Author: korzec
 *
 * Created on July 17, 2011, 9:30 PM
 */

#ifndef SUBCUBE_H
#define	SUBCUBE_H

#include "types.h"
#include "CoeffCube.h"

class Subcube {
    Coords3D index;
    CoeffView3DPtr array;
public:
    Subcube();
    Subcube(CoeffView3D& cube, Coords3D& index, Coords3D& size);
    void Init(CoeffView3D& cube, Coords3D& index, Coords3D& size);
    Coords3D GetIndex();
    CoeffView3D& GetView();
    Coords3D GetSize();

};

#endif	/* SUBCUBE_H */

