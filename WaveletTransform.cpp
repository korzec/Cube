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

bool WaveletTransform::ForwardSlice(CoeffArray3D& cube, int slice)
{
    return false;
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
    assert(cube.size() != 0);
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
                /// s = x_2n + d/2
                cube[d][h][w-1] += cube[d][h][w]/2;
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
                /// s = x_2n + d/2
                cube[d][h-1][w] += cube[d][h][w]/2;
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
                /// s = x_2n + d/2
                cube[d-1][h][w] += cube[d][h][w]/2;
            }
        }
    }

    return true;
}

bool WaveletTransform::Synth(CoeffArray3D& cube)
{
    assert(cube.size() != 0);
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
                /// xe = s - d/2
                cube[d][h][w-1] -= cube[d][h][w]/2;
                /// xo = d + xe
                cube[d][h][w] += cube[d][h][w-1];
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
                /// xe = s - d/2
                cube[d][h-1][w] -= cube[d][h][w]/2;
                /// xo = d + xe
                cube[d][h][w] += cube[d][h-1][w];
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
                /// xe = s - d/2
                cube[d-1][h][w] -= cube[d][h][w]/2;
                /// xo = d + xe
                cube[d][h][w] += cube[d-1][h][w];
            }
        }
    }

    return true;
}

//bool WaveletTransform::deinterleave1d(CoeffArray3D& cube , int dimension)
//{
//    Coords3D dims(cube.shape()[2], cube.shape()[1], cube.shape()[0]);   
//    
//    CoeffArray3D temp_cube(boost::extents[dims.depth][dims.height][dims.width]);
//    memcpy(temp_cube.data(), cube.data(), cube.size() );
//    
//    return 0;
//}

bool WaveletTransform::Deinterleave(CoeffArray3D& cube)
{
    Coords3D dims(cube.shape()[2], cube.shape()[1], cube.shape()[0]);
    
    //check if all dimensions are even numbers
    if(dims.depth%2 || dims.height%2 || dims.width%2)
        return false;
    //if a dimension is odd set the modulo operator for loop iterator;
    //the first interleave will repeat but complexity almost doesnt change
    
    ///copy the values to temp
    CoeffArray3D temp_cube(cube); 
    
    //return true;
    
#define INTERLEAVEMODE cube[d][h][w] = temp_cube[D][H][W];
//#define INTERLEAVEMODE cube[d%dims.depth][h][w] = temp_cube[D][H][W];
//#define SPECIAL if(d == dims.depth  )
    ///reorder in depth FIRST HALF
    for (int d = 0, D=0 ; d < dims.depth/2; d++, D+=2)
    {
        ///reorder in height FIRST HALF
        for (int h = 0, H=0 ; h < dims.height/2; h++, H+=2)
        {
            //reorder in width FIRST HALF
            for (int w = 0, W=0 ; w < dims.width/2; w++, W+=2)
            {
                INTERLEAVEMODE
            }
            //reorder in width SECOND HALF
            for (int w = dims.width/2, W=1 ; w < dims.width; w++, W+=2)
            {
                INTERLEAVEMODE
            }
        }
        ///reorder in height SECOND HALF
        for (int h = dims.height/2, H=1 ; h < dims.height; h++, H+=2)
        {
            //reorder in width FIRST HALF
            for (int w = 0, W=0 ; w < dims.width/2; w++, W+=2)
            {
                INTERLEAVEMODE
            }
            //reorder in width SECOND HALF
            for (int w = dims.width/2, W=1 ; w < dims.width; w++, W+=2)
            {
                INTERLEAVEMODE
            }
        }
    }
    ///reorder in depth SECOND HALF
    for (int d = dims.depth/2, D=1 ; d < dims.depth; d++, D+=2)
    {
        ///reorder in height FIRST HALF
        for (int h = 0, H=0 ; h < dims.height/2; h++, H+=2)
        {
            //reorder in width FIRST HALF
            for (int w = 0, W=0 ; w < dims.width/2; w++, W+=2)
            {
                INTERLEAVEMODE
            }
            //reorder in width SECOND HALF
            for (int w = dims.width/2, W=1 ; w < dims.width; w++, W+=2)
            {
                INTERLEAVEMODE
            }
        }
        ///reorder in height SECOND HALF
        for (int h = dims.height/2, H=1 ; h < dims.height; h++, H+=2)
        {
            //reorder in width FIRST HALF
            for (int w = 0, W=0 ; w < dims.width/2; w++, W+=2)
            {
                INTERLEAVEMODE
            }
            //reorder in width SECOND HALF
            for (int w = dims.width/2, W=1 ; w < dims.width; w++, W+=2)
            {
                INTERLEAVEMODE
            }
        }
    }
#undef INTERLEAVEMODE
    
    return true;
}

bool WaveletTransform::Interleave(CoeffArray3D& cube)
{
     Coords3D dims(cube.shape()[2], cube.shape()[1], cube.shape()[0]);
    
    //check if all dimensions are even numbers
    if(dims.depth%2 || dims.height%2 || dims.width%2)
        return false;
    //if a dimension is odd set the modulo operator for loop iterator;
    //the first interleave will repeat but complexity almost doesnt change
    
    ///copy the values to temp
    CoeffArray3D temp_cube(cube); 
    
    //return true;
    
#define INTERLEAVEMODE cube[D][H][W] = temp_cube[d][h][w];
    
    ///reorder in depth FIRST HALF
    for (int d = 0, D=0 ; d < dims.depth/2; d++, D+=2)
    {
        ///reorder in height FIRST HALF
        for (int h = 0, H=0 ; h < dims.height/2; h++, H+=2)
        {
            //reorder in width FIRST HALF
            for (int w = 0, W=0 ; w < dims.width/2; w++, W+=2)
            {
                INTERLEAVEMODE
            }
            //reorder in width SECOND HALF
            for (int w = dims.width/2, W=1 ; w < dims.width; w++, W+=2)
            {
                INTERLEAVEMODE
            }
        }
        ///reorder in height SECOND HALF
        for (int h = dims.height/2, H=1 ; h < dims.height; h++, H+=2)
        {
            //reorder in width FIRST HALF
            for (int w = 0, W=0 ; w < dims.width/2; w++, W+=2)
            {
                INTERLEAVEMODE
            }
            //reorder in width SECOND HALF
            for (int w = dims.width/2, W=1 ; w < dims.width; w++, W+=2)
            {
                INTERLEAVEMODE
            }
        }
    }
    ///reorder in depth SECOND HALF
    for (int d = dims.depth/2, D=1 ; d < dims.depth; d++, D+=2)
    {
        ///reorder in height FIRST HALF
        for (int h = 0, H=0 ; h < dims.height/2; h++, H+=2)
        {
            //reorder in width FIRST HALF
            for (int w = 0, W=0 ; w < dims.width/2; w++, W+=2)
            {
                INTERLEAVEMODE
            }
            //reorder in width SECOND HALF
            for (int w = dims.width/2, W=1 ; w < dims.width; w++, W+=2)
            {
                INTERLEAVEMODE
            }
        }
        ///reorder in height SECOND HALF
        for (int h = dims.height/2, H=1 ; h < dims.height; h++, H+=2)
        {
            //reorder in width FIRST HALF
            for (int w = 0, W=0 ; w < dims.width/2; w++, W+=2)
            {
                INTERLEAVEMODE
            }
            //reorder in width SECOND HALF
            for (int w = dims.width/2, W=1 ; w < dims.width; w++, W+=2)
            {
                INTERLEAVEMODE
            }
        }
    }
#undef INTERLEAVEMODE
    
    return true;
}

