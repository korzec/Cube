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

/// copy a slice from one 2d array to another 2 array
template <class T, class U>
bool copyArray()
{
    ///if the gop size matches the cube depth
    if (gop.size() == (size_t) Dimensionality().depth)
    {
        Coords3D dims = Dimensionality();
        ///copy the gop to the cube
        for (int d = 0; d < dims.depth; d++)
        {
            //get pointer to the pic 
            Picture* pic = &gop[d];
            for (int h = 0; h < dims.height; h++)
            {
                //get pointer to a row in the picture
                ValueType* picRow = &pic->Y()[h][0];
                //get pointer to a row in one slice
                CoeffType* sliceRow = &Y()[d][h][0];

                //copy a row from pic to cube
                for (int w = 0; w < dims.width; w++)
                {
                    sliceRow[w] = CoeffType(picRow[w]);
                }
            }
        }
        return true;
    }
    return false;
}

#endif	/* GENERAL_H */

