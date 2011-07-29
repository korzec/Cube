/* 
 * File:   general.h
 * Author: korzec
 * 
 * General purpose functions
 *
 * Created on July 28, 2011, 11:00 PM
 */

#ifndef GENERAL_H
#define	GENERAL_H

#include "types.h"


/// copy a slice from one 2d array to another 2 array
//template <class T, class U>
bool copyArrayFromValueToCoeff(ValueArray2Dref& from ,CoeffView2D& to)
{
    assert( from.dimensionality == to.dimensionality );
    int width = to.shape()[1];
    int height = to.shape()[0];
    //get pointer to the pic 
    for (int h = 0; h < height; h++)
    {
        //get pointer to a row in the picture
        ValueType* picRow = &from[h][0];
        //get pointer to a row in one slice
        CoeffType* sliceRow = &to[h][0];

        //copy a row from pic to cube
        for (int w = 0; w < width; w++)
        {
            sliceRow[w] = CoeffType(picRow[w]);
        }
    }
    
    return false;
}

bool copyArrayFromCoeffToValue(CoeffView2D& from ,ValueArray2Dref& to)
{
    assert( from.dimensionality == to.dimensionality );
    int width = to.shape()[1];
    int height = to.shape()[0];
    //get pointer to the pic 
    for (int h = 0; h < height; h++)
    {
        //get pointer to a row in the picture
        ValueType* picRow = &to[h][0];
        //get pointer to a row in one slice
        CoeffType* sliceRow = &from[h][0];

        //copy a row from pic to cube
        for (int w = 0; w < width; w++)
        {
            picRow[w] = ValueType(sliceRow[w]);
        }
    }
    
    return false;
}

#endif	/* GENERAL_H */

