/* 
 * File:   CoeffCube.cpp
 * Author: korzec
 * 
 * Created on July 17, 2011, 9:17 PM
 */

#include "CoeffCube.h"
#include "general.h"
#include "CubeTransform.h"
#include <omp.h>

CoeffCube::CoeffCube() : available(false), cubeNumber(-1), nextIndex(-1)
{
}

CoeffCube::CoeffCube(int width, int height, int depth, int levels) :
        available(false), cubeNumber(-1), nextIndex(-1)
{
    arrayY = CoeffArray3DPtr(new CoeffArray3D(boost::extents[depth][height][width]));
    arrayU = CoeffArray3DPtr(new CoeffArray3D(boost::extents[depth][height>>1][width>>1]));
    arrayV = CoeffArray3DPtr(new CoeffArray3D(boost::extents[depth][height>>1][width>>1]));
    
    subbandsY.Init(Y(), levels);
    subbandsU.Init(U(), levels);
    subbandsV.Init(V(), levels);
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

bool CoeffCube::LoadNextPicture(Picture& picture)
{
    if(!available)
        return false;
    assert(nextIndex < Dimensionality().depth);
    assert(nextIndex >= 0);
    ///destination slice
    CoeffView2D sliceY =  this->Y()[nextIndex];
    copyArrayFromValueToCoeff(picture.Y(), sliceY);
    
    nextIndex++;
    if(nextIndex == Dimensionality().depth)
    {
        available = false;
    }
    return true;
}

bool CoeffCube::MakeAvailable()
{
    available = true;
    nextIndex = 0;
    
    return true;
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
        //set availability
        available = false;
        nextIndex = Dimensionality().depth;
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

Coords3D CoeffCube::ChromaDimensionality()
{
    Coords3D dims;
    dims.depth = U().shape()[0];
    dims.height = U().shape()[1];
    dims.width = U().shape()[2];
    return dims;
}

bool CoeffCube::SmoothTime()
{
    return CubeTransform::SmoothTemporal(subbandsY.GetSubband(0, LLL));
    return CubeTransform::SmoothTemporal(subbandsU.GetSubband(0, LLL));
    return CubeTransform::SmoothTemporal(subbandsV.GetSubband(0, LLL));
    //return transform.SmoothTemporal(V());
}

int CoeffCube::GetLevel()
{
    return subbandsY.GetLevel();
}

bool CoeffCube::ForwardTransform()
{
    ///if fully loaded and ready to transofrm
    if(!available && nextIndex == Dimensionality().depth)
    {
        bool state = true;
        for(int i=1; i <= GetLevel(); i++ )
        {
            
            #pragma omp parallel sections reduction(&& : state)
            {   
            #pragma omp section
                state = state && transform.Forward(subbandsY.GetSubband(i-1, LLL));
            #pragma omp section
                {
                state = state && transform.Forward(subbandsU.GetSubband(i-1, LLL));     
                state = state && transform.Forward(subbandsV.GetSubband(i-1, LLL));
                }
            }
        }
        return state;
    }
    else
        return false;
}

bool CoeffCube::ReverseTransform()
{
    bool state = true;
    for (int i = GetLevel(); i >= 1 ; i--)
    {

        #pragma omp parallel sections reduction(&& : state)
        {
        #pragma omp section
            state = state && transform.Reverse(subbandsY.GetSubband(i - 1, LLL));
        #pragma omp section
            {
            state = state && transform.Reverse(subbandsU.GetSubband(i - 1, LLL));
            state = state && transform.Reverse(subbandsV.GetSubband(i - 1, LLL));
            }
        }
    }
    return state;
}

bool CoeffCube::dump(std::string fileName)
{
    return dumpCube(Y(), fileName);
}