/* 
 * File:   CoeffCube.cpp
 * Author: korzec
 * 
 * Created on July 17, 2011, 9:17 PM
 */

#include "CoeffCube.h"

CoeffCube::CoeffCube()
{
}

CoeffCube::CoeffCube(int width, int height, int depth)
{
    arrayY = CoeffArray3DPtr(new CoeffArray3D(boost::extents[depth][height][width]));
    //arrayY = new CoeffArray3D(boost::extents[depth][height][width]);
    //boost::array<CoeffArray3D::index, 3> dims = {{depth, height, width}};
    //arrayY.resize(boost::extents[depth][height][width]);
}

CoeffArray3D & CoeffCube::Y()
{
    return *arrayY;
}

bool CoeffCube::LoadGOP(PictureVector& gop)
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

Coords3D CoeffCube::Dimensionality()
{
    Coords3D dims;
    dims.depth = Y().shape()[0];
    dims.height = Y().shape()[1];
    dims.width = Y().shape()[2]; 
    return dims;
}

bool CoeffCube::ForwardTransform()
{
    return transform.Forward(Y());
}

bool CoeffCube::ReverseTransform()
{
    return transform.Reverse(Y());
}