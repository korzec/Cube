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
#include <cstring>
#include <cassert>

CoeffCube::CoeffCube() : available(false), cubeNumber(-1), nextIndex(-1)
{
}

CoeffCube::CoeffCube(Coords3D size, int levels, Coords3D subSize) :
        available(false), cubeNumber(-1), nextIndex(-1)
{
    Init(size, levels, subSize);
}

bool CoeffCube::Init(Coords3D size, int levels, Coords3D subSize)
{
    arrays[Ych] = CoeffArray3DPtr(new CoeffArray3D
            (boost::extents[size.depth][size.height][size.width]));
    arrays[Uch] = CoeffArray3DPtr(new CoeffArray3D
            (boost::extents[size.depth][size.height>>1][size.width>>1]));
    arrays[Vch] = CoeffArray3DPtr(new CoeffArray3D
            (boost::extents[size.depth][size.height>>1][size.width>>1]));
    
    subbands[Ych].Init(Array(Ych), levels);
    subbands[Uch].Init(Array(Uch), levels-1);
    subbands[Vch].Init(Array(Vch), levels-1);
    
    subcubeIndex[Ych].Init(subbands[Ych].GetSubband(0, LLL), subSize, Ych );
    subcubeIndex[Uch].Init(subbands[Uch].GetSubband(0, LLL), subSize, Uch );
    subcubeIndex[Vch].Init(subbands[Vch].GetSubband(0, LLL), subSize, Vch );
    return true;
}


int CoeffCube::GetLevel()
{
    return subbands[Ych].GetLevel();
}


CoeffArray3D & CoeffCube::Array(Channel channel)
{
    return *arrays[channel];
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

bool CoeffCube::ForwardTransform()
{
    ///if fully loaded and ready to transofrm
    if(!available && nextIndex == Dimensionality().depth)
    {
        bool state = true;
        for(int i=0; i < GetLevel(); i++ )
        {
            
            #pragma omp parallel sections reduction(&& : state)
            {   
            #pragma omp section
                state = state && transform.Forward(subbands[Ych].GetSubband(i, LLL));
            #pragma omp section
                {
                    if(i != GetLevel()-1)
                    {
                        //the color channels have one level less
                        //skip the last level for colors 
                    state = state && transform.Forward(subbands[Uch].GetSubband(i, LLL));     
                    state = state && transform.Forward(subbands[Vch].GetSubband(i, LLL));
                    }
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
    for (int i = GetLevel()-1; i >= 0 ; i--)
    {

        #pragma omp parallel sections reduction(&& : state)
        {
        #pragma omp section
            state = state && transform.Reverse(subbands[Ych].GetSubband(i, LLL));
        #pragma omp section
            {
                if(i != GetLevel()-1)
                {
                    //the color channels have one level less
                    //skip the last level for colors
                state = state && transform.Reverse(subbands[Uch].GetSubband(i, LLL));
                state = state && transform.Reverse(subbands[Vch].GetSubband(i, LLL));
                }
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
    subcubeIndex[Ych].ComputeWeights();
    return subcubeIndex[Ych].dump(fileName);
}


SubcubeIndex* CoeffCube::GetSubcubeIndex(Channel channel)
{
    return &subcubeIndex[channel];
}

int& CoeffCube::GetCubeNumber()
{
    return cubeNumber;
}

bool CoeffCube::ZeroAll()
{
    //clear all arrays
    for(int i=0; i < NOFCHANNELS ; i++)
    {
        char* data = (char*) ( arrays[0]->data() );
        //size of data in the array
        int length = Coords3D(arrays[0]->shape()).Volume()*sizeof(CoeffType);
        memset(data, 0, length);
    }
    return true;
}

SubbandList* CoeffCube::GetSubbandList()
{
    return subbands;
}