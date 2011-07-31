/* 
 * File:   Subcube.cpp
 * Author: korzec
 * 
 * Created on July 17, 2011, 9:30 PM
 */

#include "Subcube.h"

Subcube::Subcube(CoeffView3D& cube, Coords3D& index, Coords3D& size)
{
    Init(cube, index, size);
}

Subcube::Subcube() {
}

void Subcube::Init(CoeffView3D& cube, Coords3D& index, Coords3D& size)
{
    this->index = index;
    array = CoeffView3DPtr(new CoeffView3D(
            cube [ indices
            [range(index.depth*size.depth, (index.depth+1)*size.depth)]
            [range(index.height*size.height, (index.height+1)*size.height)]
            [range(index.width*size.width, (index.width+1)*size.width)]
            ]));
}

Coords3D Subcube::GetIndex()
{
    return index;
}

CoeffView3D& Subcube::GetView()
{
    return *array;
}

Coords3D Subcube::GetSize()
{
    Coords3D dims(array->shape());
    return dims;
}