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
    CubeCoords coords;
    CoeffCube cube;
public:
    Subcube();
    Subcube(const Subcube& orig);
    virtual ~Subcube();
private:

};

#endif	/* SUBCUBE_H */

