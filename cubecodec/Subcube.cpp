/* 
 * File:   Subcube.cpp
 * Author: korzec
 * 
 * Created on July 17, 2011, 9:30 PM
 */

#include "Subcube.h"
#include <cassert>

Subcube::Subcube() : cube(NULL)
{
}

Subcube::Subcube(CoeffView3D& cube, Coords3D& index, Coords3D& size, Channel channel) : cube(NULL)
{
    Init(cube, index, size, channel);
}


void Subcube::Init(CoeffView3D& cube, Coords3D& index, Coords3D& size, Channel ch)
{
    this->cube = &cube;
    info.location = index;
    info.size = size;
    info.channel = ch;
    array.reset(new CoeffView3D(
            cube [ boost::indices
            [range(index.depth*size.depth, (index.depth+1)*size.depth)]
            [range(index.height*size.height, (index.height+1)*size.height)]
            [range(index.width*size.width, (index.width+1)*size.width)]
            ]));
}

Coords3D Subcube::GetLocation()
{
    return info.location;
}

CoeffView3D& Subcube::GetView()
{
    return *array;
}

Coords3D Subcube::GetSize()
{
    //Coords3D dims(array->shape());
    return info.size;
}

float Subcube::GetWeight()
{
    CoeffView3D array = GetView();
    Coords3D dims(array.shape());
    float sum = 0;
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                sum += (array)[d][h][w]*(array)[d][h][w];
            }//w
        }//h
    }//d
    return sum;
}

CoeffView3D& Subcube::GetParentView()
{
    return *cube;
}

Channel Subcube::GetChannel()
{
    return info.channel;
}
bool Subcube::CopyNewValues(CoeffArray3DPtr newArrayPtr)
{   
    //TODO: use memcpy
    
    assert(newArrayPtr->shape()[0] == array->shape()[0]);
    assert(newArrayPtr->shape()[1] == array->shape()[1]);
    assert(newArrayPtr->shape()[2] == array->shape()[2]);
    
    Coords3D dims(array->shape());
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                (*array)[d][h][w] = (*newArrayPtr)[d][h][w];
            }//w
        }//h
    }//d
    return true;
}