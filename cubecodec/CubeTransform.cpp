/* 
 * File:   CubeTransform.cpp
 * Author: korzec
 * 
 * Created on July 31, 2011, 10:56 PM
 */

#include "CubeTransform.h"
#include <cassert>

bool CubeTransform::SmoothTemporal(CoeffView3D& cube)
{
    //zero the tempotal H
    assert(cube.size() != 0);
    if(cube.size() == 0)
        return false;
   
    
    Coords3D dims(cube.shape()[2], cube.shape()[1], cube.shape()[0]);
    
    ///zero the the H temporal band (**H), except the level-1 LLH;
    for (int d = dims.depth/2; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                ///dint
                if(w<dims.width/2 && h<dims.height/2)
                    continue;
                /// zero the band
                CoeffType* coeff = &cube[d][h][w];
                //if(*coeff < 10)
                    *coeff = 0;
            }
        }
    }
    return true;
}