/* 
 * File:   CubeTransform.h
 * Author: korzec
 *
 * Created on July 31, 2011, 10:56 PM
 */

#ifndef CUBETRANSFORM_H
#define	CUBETRANSFORM_H

#include "arrays.h"

/// Transform cube to modify value of the cube used to enhance compression
class CubeTransform
{
public:
    /// zero the H band in temporal axis
    static bool SmoothTemporal(CoeffView3D&);
};

#endif	/* CUBETRANSFORM_H */

