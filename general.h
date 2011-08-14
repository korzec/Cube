/* 
 * File:   general.h
 * Author: korzec
 * 
 * General purpose functions
 *
 * Created on July 28, 2011, 11:00 PM
 */

#ifndef GENERAL_H
#define	GENERAL_H

#include "types.h"
#include "Subcube.h"
#include <string>
#include <iostream>
#include <fstream>



/// copy a Picture to slice in CoeffCube
bool copyArrayFromValueToCoeff(ValueArray2Dref& from, CoeffView2D& to)
{
    assert(from.dimensionality == to.dimensionality);
    int width = to.shape()[1];
    int height = to.shape()[0];
    //get pointer to the pic 
    for (int h = 0; h < height; h++)
    {
        //get pointer to a row in the picture
        ValueType* picRow = &from[h][0];
        //get pointer to a row in one slice
        CoeffType* sliceRow = &to[h][0];

        //copy a row from pic to cube
        for (int w = 0; w < width; w++)
        {
            sliceRow[w] = CoeffType(picRow[w]);
        }
    }

    return true;
}
/// copy a slice from CoeffCube to a Picture
bool copyArrayFromCoeffToValue(CoeffView2D& from, ValueArray2Dref& to)
{
    assert(from.dimensionality == to.dimensionality);
    int width = to.shape()[1];
    int height = to.shape()[0];
    //get pointer to the pic 
    for (int h = 0; h < height; h++)
    {
        //get pointer to a row in the picture
        ValueType* picRow = &to[h][0];
        //get pointer to a row in one slice
        CoeffType* sliceRow = &from[h][0];

        //copy a row from pic to cube
        for (int w = 0; w < width; w++)
        {
            picRow[w] = ValueType(sliceRow[w]);
        }
    }

    return true;
}

///saves CoeffArray3D to a file for analysis
bool dumpCube(CoeffArray3D& cube, std::string fileName)
{
    std::ofstream* output = new std::ofstream(fileName.c_str(), std::ios::out | std::ios::binary);
    if (!output || !output->good())
    {
        std::cerr << "output problem" << std::endl;
        return false;
    }

    Coords3D dims(cube.shape()[2], cube.shape()[1], cube.shape()[0]);

    //*output << "w, h, d, Y" <<std::endl;

    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            //for (int w = 0; w < dims.width; w++)
            {
                /// zero the band
                CoeffType* coeff = &cube[d][h][0];
                //if(*coeff < 10)
                output->write((char*) (coeff), sizeof (CoeffType) * dims.width);
            }
        }
    }
    output->close();
    return true;
}
/// writes weights of each value in CoeffCube to a file for analysis
bool dumpSubcubes(SubcubeArray3D& subcubes, FloatArray3D& weights, std::string fileName)
{
    std::ofstream* output = new std::ofstream(fileName.c_str(), std::ios::out | std::ios::binary);
    if (!output || !output->good())
    {
        std::cerr << "output problem" << std::endl;
        return false;
    }
    ///whole cube
    CoeffView3D* cube = &(*subcubes.data()).GetParentView();
    ///size of whole cube
    Coords3D dims(cube->shape());
    //size of subcubes
    Coords3D subSize = (*subcubes.data()).GetSize();

    Coords3D index;
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                ///compute current subcube index
                index.Set(w / subSize.width -0.5,
                          h / subSize.height -0.5,
                          d / subSize.depth -0.5);

                //CoeffType* coeff = &(*cube)[d][h][w];
                float* weight = &weights[index.depth][index.height][index.width];
                // output->write((char*)(coeff), sizeof(CoeffType));
                output->write((char*) (weight), sizeof (float));
            }//w
        }//h
    }//d
    output->close();
    return true;
}

#endif	/* GENERAL_H */