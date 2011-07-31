/* 
 * File:   SubcubeIndex.cpp
 * Author: korzec
 * 
 * Created on July 31, 2011, 7:25 PM
 */

#include "SubcubeIndex.h"

Subcube SubcubeIndex::GetSubcube(Coords3D index)
{
    return list[index.depth][index.height][index.width];
}

void SubcubeIndex::Init(CoeffView3D& cube, Coords3D size)
{
    //Coords3D size(32,32,4);
    Coords3D dims(cube.shape()[2]/size.width, 
                  cube.shape()[1]/size.height, 
                  cube.shape()[0]/size.depth);
    
    list.resize(extents[dims.depth][dims.height][dims.width]);
    
    //loop over all subcubes and initialize them
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                Coords3D index(w,h,d);
                list[d][h][w].Init(cube, index, size);
            }
        }
    }
}

SubcubeIndex::SubcubeIndex(CoeffView3D& cube, Coords3D size)
{
    Init(cube,size);
}

SubcubeIndex::SubcubeIndex()
{
}
