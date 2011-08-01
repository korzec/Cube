/* 
 * File:   SubcubeIndex.cpp
 * Author: korzec
 * 
 * Created on July 31, 2011, 7:25 PM
 */

#include "SubcubeIndex.h"

SubcubeIndex::SubcubeIndex()
{
}

SubcubeIndex::SubcubeIndex(CoeffView3D& cube, Coords3D size)
{
    Init(cube,size);
}

void SubcubeIndex::Init(CoeffView3D& cube, Coords3D subSize)
{
    //Coords3D size(32,32,4);
    Coords3D dims(cube.shape()[2]/subSize.width, 
                  cube.shape()[1]/subSize.height, 
                  cube.shape()[0]/subSize.depth);
    
    list.resize(extents[dims.depth][dims.height][dims.width]);
    weights.resize(extents[dims.depth][dims.height][dims.width]);
    
    //loop over all subcubes and initialize them
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                Coords3D index(w,h,d);
                ((Subcube*)(&list[d][h][w]))->Init(cube, index, subSize);
            }
        }
    }
}

Subcube& SubcubeIndex::GetSubcube(Coords3D index)
{
    return list[index.depth][index.height][index.width];
}

void SubcubeIndex::ComputeWeights()
{
    ///loop over all subcubes and compute their Sum of Squares
    ///save results to weight array;
    assert(list.dimensionality == weights.dimensionality);
    
    Coords3D dims(list.shape());
    
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                Subcube& subcube = list[d][h][w];   
                weights[d][h][w] = subcube.GetWeight();
            }//w
        }//h
    }//d
}

bool SubcubeIndex::dump(std::string fileName)
{
    return dumpSubcubes(list, weights, fileName );
}