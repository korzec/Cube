/* 
 * File:   CoeffCube.cpp
 * Author: korzec
 * 
 * Created on July 17, 2011, 9:17 PM
 */

#include "CoeffCube.h"
#include "general.h"
#include "CubeTransform.h"
#include "SubcubeIndex.h"
#include <omp.h>

CoeffCube::CoeffCube() : available(false), cubeNumber(-1), nextIndex(-1)
{
}

CoeffCube::CoeffCube(Coords3D size, int levels, Coords3D subSize) :
        available(false), cubeNumber(-1), nextIndex(-1)
{
    Init(size, levels, subSize);
}

void CoeffCube::Init(Coords3D size, int levels, Coords3D subSize)
{
    arrays[Ych] = CoeffArray3DPtr(new CoeffArray3D
            (boost::extents[size.depth][size.height][size.width]));
    arrays[Uch] = CoeffArray3DPtr(new CoeffArray3D
            (boost::extents[size.depth][size.height>>1][size.width>>1]));
    arrays[Vch] = CoeffArray3DPtr(new CoeffArray3D
            (boost::extents[size.depth][size.height>>1][size.width>>1]));
    
    subbands[Ych].Init(Array(Ych), levels);
    subbands[Uch].Init(Array(Uch), levels);
    subbands[Vch].Init(Array(Vch), levels);
    
    cubes[Ych].Init(subbands[Ych].GetSubband(0, LLL), subSize );
    cubes[Uch].Init(subbands[Uch].GetSubband(0, LLL), subSize );
    cubes[Vch].Init(subbands[Vch].GetSubband(0, LLL), subSize );
}

CoeffArray3D & CoeffCube::Array(Channel ch)
{
    return *arrays[ch];
}

bool CoeffCube::LoadNextPicture(Picture& picture)
{
    if(!available)
        return false;
    assert(nextIndex < Dimensionality().depth);
    assert(nextIndex >= 0);
    ///destination slice
    CoeffView2D sliceY =  this->Array(Ych)[nextIndex];
    copyArrayFromValueToCoeff(picture.Array(Ych), sliceY);
    
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
           
            CoeffView2D sliceY =  this->Array(Ych)[d];
            copyArrayFromValueToCoeff(pic->Array(Ych), sliceY);
            
            CoeffView2D sliceU =  this->Array(Uch)[d];
            copyArrayFromValueToCoeff(pic->Array(Uch), sliceU);
            
            CoeffView2D sliceV =  this->Array(Vch)[d];
            copyArrayFromValueToCoeff(pic->Array(Vch), sliceV);

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
            CoeffView2D sliceY =  this->Array(Ych)[d];
            copyArrayFromCoeffToValue(sliceY, picture.Array(Ych));

            CoeffView2D sliceU =  this->Array(Uch)[d];
            copyArrayFromCoeffToValue(sliceU, picture.Array(Uch));
            
            CoeffView2D sliceV =  this->Array(Vch)[d];
            copyArrayFromCoeffToValue(sliceV, picture.Array(Vch));
            
            gop->push_back(picture);
        }

    }
    return gop;
}

Coords3D CoeffCube::Dimensionality()
{
    Coords3D dims(Array(Ych).shape());
    //dims.depth = Y().shape()[0];
    //dims.height = Y().shape()[1];
    //dims.width = Y().shape()[2];
    return dims;
}

Coords3D CoeffCube::ChromaDimensionality()
{
    Coords3D dims(Array(Uch).shape());
    //dims.depth = U().shape()[0];
    //dims.height = U().shape()[1];
    //dims.width = U().shape()[2];
    return dims;
}

bool CoeffCube::SmoothTime()
{
    bool ret = true;
    ret = CubeTransform::SmoothTemporal(subbands[Ych].GetSubband(0, LLL))
        && CubeTransform::SmoothTemporal(subbands[Uch].GetSubband(0, LLL))
        && CubeTransform::SmoothTemporal(subbands[Vch].GetSubband(0, LLL));
    return ret;
}

int CoeffCube::GetLevel()
{
    return subbands[Ych].GetLevel();
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
                state = state && transform.Forward(subbands[Ych].GetSubband(i-1, LLL));
            #pragma omp section
                {
                state = state && transform.Forward(subbands[Uch].GetSubband(i-1, LLL));     
                state = state && transform.Forward(subbands[Vch].GetSubband(i-1, LLL));
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
            state = state && transform.Reverse(subbands[Ych].GetSubband(i - 1, LLL));
        #pragma omp section
            {
            state = state && transform.Reverse(subbands[Uch].GetSubband(i - 1, LLL));
            state = state && transform.Reverse(subbands[Vch].GetSubband(i - 1, LLL));
            }
        }
    }
    return state;
}

bool CoeffCube::dumpCoeffs(std::string fileName)
{
    return dumpCube(Array(Ych), fileName);   
}

bool CoeffCube::dumpWeights(std::string fileName)
{
    cubes[Ych].ComputeWeights();
    return cubes[Ych].dump(fileName);
}