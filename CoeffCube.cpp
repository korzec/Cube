/* 
 * File:   CoeffCube.cpp
 * Author: korzec
 * 
 * Created on July 17, 2011, 9:17 PM
 */

#include "CoeffCube.h"
#include "general.h"

CoeffCube::CoeffCube()
{
}

CoeffCube::CoeffCube(int width, int height, int depth)
{
    arrayY = CoeffArray3DPtr(new CoeffArray3D(boost::extents[depth][height][width]));
    arrayU = CoeffArray3DPtr(new CoeffArray3D(boost::extents[depth][height>>1][width>>1]));
    arrayV = CoeffArray3DPtr(new CoeffArray3D(boost::extents[depth][height>>1][width>>1]));
}

CoeffArray3D & CoeffCube::Y()
{
    return *arrayY;
}
CoeffArray3D & CoeffCube::U()
{
    return *arrayU;
}
CoeffArray3D & CoeffCube::V()
{
    return *arrayV;
}

bool CoeffCube::LoadGOP(PictureVector& gop)
{
    ///get a picture and a slice
    
    ///if the gop size matches the cube depth
    if (gop.size() == (size_t) Dimensionality().depth)
    {
        Coords3D dims = Dimensionality();
        ///copy the gop to the cube
        for (int d = 0; d < dims.depth; d++)
        {
            //get pointer to the pic 
            Picture* pic = &gop[d];
           
            CoeffView2D sliceY =  this->Y()[d];
            copyArrayFromValueToCoeff(pic->Y(), sliceY);
            
            CoeffView2D sliceU =  this->U()[d];
            copyArrayFromValueToCoeff(pic->U(), sliceU);
            
            CoeffView2D sliceV =  this->V()[d];
            copyArrayFromValueToCoeff(pic->V(), sliceV);

        }
        return true;
    }
    return false;
}

PictureVectorPtr CoeffCube::GetGOP()
{
    Coords3D dims = Dimensionality();
    PictureVectorPtr gop(new PictureVector());
    if (dims.depth > 0)
    {
        //copy cube data into a gop
        for (int d = 0; d < dims.depth; d++)
        {
            Picture picture(dims.width, dims.height);
              ///copy a slice to the Picture          
            CoeffView2D sliceY =  this->Y()[d];
            copyArrayFromCoeffToValue(sliceY, picture.Y());

            CoeffView2D sliceU =  this->U()[d];
            copyArrayFromCoeffToValue(sliceU, picture.U());
            
            CoeffView2D sliceV =  this->V()[d];
            copyArrayFromCoeffToValue(sliceV, picture.V());
            
            gop->push_back(picture);
        }

    }
    return gop;
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