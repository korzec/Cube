/* 
 * File:   WaveletTransform.cpp
 * Author: korzec
 * 
 * Created on July 18, 2011, 8:44 PM
 */

#include "WaveletTransform.h"

WaveletTransform::WaveletTransform()
{
}

WaveletTransform::WaveletTransform(const WaveletTransform& orig)
{
}

WaveletTransform::~WaveletTransform()
{
}

bool WaveletTransform::Forward(CoeffArray3D& cube)
{
    if(Split(cube) && Deinterleave(cube))
        return true;
    else
        return false;
}

bool WaveletTransform::Reverse(CoeffArray3D& cube)
{
    if(Interleave(cube) && Synth(cube))
        return true;
    else
        return false;
}

bool WaveletTransform::Split(CoeffArray3D& cube)
{
    if(cube.size() == 0)
        return false;
    
    Coords3D dims(cube.shape()[2], cube.shape()[1], cube.shape()[0]);
    
    ///do filtering in width
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 1; w < dims.width; w+=2)
            {
                /// d = x_2n+1 - x_2n
                cube[d][h][w] -= cube[d][h][w-1];
                /// s = x_2n + d
                cube[d][h][w-1] += cube[d][h][w];
            }
        }
    }
    
    ///do filtering in height
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 1; h < dims.height; h+=2)
        {
            for (int w = 0; w < dims.width; w++)
            {
                /// d = x_2n+1 - x_2n
                cube[d][h][w] -= cube[d][h-1][w];
                /// s = x_2n + d
                cube[d][h-1][w] += cube[d][h][w];
            }
        }
    }
    ///do filtering in depth
    for (int d = 1; d < dims.depth; d+=2)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                /// d = x_2n+1 - x_2n
                cube[d][h][w] -= cube[d-1][h][w];
                /// s = x_2n + d
                cube[d-1][h][w] += cube[d][h][w];
            }
        }
    }

    return true;
}

bool WaveletTransform::Synth(CoeffArray3D& cube)
{
    return true;
}

bool WaveletTransform::Deinterleave(CoeffArray3D& cube)
{
    Coords3D dims(cube.shape()[2], cube.shape()[1], cube.shape()[0]);
    
    CoeffArray3D temp_cube(boost::extents[dims.depth][dims.height][dims.width]);
    
    ///copy the values to temp
    memcpy(temp_cube.data(), cube.data(), cube.size() );
    
    ///reorder in width
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 1; w < dims.width; w+=2)
            {
                /// d = x_2n+1 - x_2n
                //cube[d][h][w] -= cube[d][h][w-1];
                /// s = x_2n + d
                //                              cube[d][h][w-1] += cube[d][h][w];
            }
        }
    }
    
    return true;
}

bool WaveletTransform::Interleave(CoeffArray3D& cube)
{
    return true;
}