/* 
 * File:   SubcubeIndex.cpp
 * Author: korzec
 * 
 * Created on July 31, 2011, 7:25 PM
 */

#include "SubcubeIndex.h"
#include <cassert>

bool dumpSubcubes(SubcubeArray3D& subcubes, FloatArray3D& weights, std::string fileName);

SubcubeIndex::SubcubeIndex()
{
}

SubcubeIndex::SubcubeIndex(CoeffView3D& cube, Coords3D size, Channel channel)
{
    Init(cube,size, channel);
}

void SubcubeIndex::Init(CoeffView3D& cube, Coords3D subSize, Channel channel)
{
    assert(cube.shape()[2] % subSize.width == 0);
    assert(cube.shape()[1] % subSize.height == 0);
    assert(cube.shape()[0] % subSize.depth == 0);
    //Coords3D size(32,32,4);
    Coords3D dims(cube.shape()[2]/subSize.width, 
                  cube.shape()[1]/subSize.height, 
                  cube.shape()[0]/subSize.depth);
    
    list.resize(boost::extents[dims.depth][dims.height][dims.width]);
    weights.resize(boost::extents[dims.depth][dims.height][dims.width]);
    
    //loop over all subcubes and initialize them
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                Coords3D index(w,h,d);
                ((Subcube*)(&list[d][h][w]))->Init(cube, index, subSize, channel);
            }
        }
    }
}

Subcube& SubcubeIndex::GetSubcube(Coords3D& index)
{
    return list[index.depth][index.height][index.width];
}

void SubcubeIndex::ComputeWeights()
{
    ///loop over all subcubes and compute their Sum of Squares
    ///save results to weight array;
    ///also save a sorted maping of weights to subcubes
    assert(list.dimensionality == weights.dimensionality);
    //remove old weights mapping
    weightsMap.clear();
    Coords3D dims(list.shape());
    float weight;
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                Subcube& subcube = list[d][h][w];
                weight = subcube.GetWeight();
                weights[d][h][w] = weight;
                //items are sorted on insertion
                weightsMap.insert(WeightPair(weight, &subcube));
            }//w
        }//h
    }//d
}

bool SubcubeIndex::dump(std::string fileName)
{
    return dumpSubcubes(list, weights, fileName );
}

Coords3D SubcubeIndex::GetIndexDims()
{
    return Coords3D(weights.shape());
}


WeightsMap& SubcubeIndex::GetWeightsMap()
{
    return weightsMap;
}