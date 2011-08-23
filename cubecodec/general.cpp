#include "general.h"
#include <stdlib.h>
#include <stdio.h>
#include <bitset>
#include <cassert>
#include <float.h>
#include <vector>
#include "Picture.h"
#include "types.h"

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

///find number of occurencies of CoeffType symbols and put into a map

typedef std::map<CoeffType, int> CoeffMap;
//typedef boost::shared_ptr<CoeffMap> CoeffMapPtr;

CoeffMap getSymbolStatistics(CoeffView3D& array)
{
    CoeffMap map;
    
    Coords3D dims(array.shape());
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                CoeffType key = array[d][h][w];

                map[key]++;
                
            }//w
        }//h
    }//d
    return map;
}


//output a statistics map to csv file
bool writeMap(CoeffMap map, std::string fileName)
{
    std::ofstream file(fileName.c_str());
    if(file.fail())
        return false;
    
    file << "hex, decimal, count, binary" <<std::endl;
    CoeffMap::iterator iterator = map.begin();
    for(;iterator != map.end(); iterator++)
    {
        std::bitset<sizeof(CoeffType)*8> bin = iterator->first;

        file << std::hex << iterator->first <<", "
                << std::dec << iterator->first <<", "
                << iterator->second <<", " 
                << bin << std::endl;
    }
    file.close();
    return true;
}

double MSE(const ValueArray2Dref& array1, const ValueArray2Dref& array2)
{
    assert(array1.shape()[0] == array2.shape()[0]);
    assert(array1.shape()[1] == array2.shape()[1]);
    
    Coords3D dims(array1.shape()[1], array1.shape()[0], 1);
    
    double sum = 0;
    double current;
    //loop all values        
    for (int h = 0; h < dims.height; h++)
    {
        for (int w = 0; w < dims.width; w++)
        {
             current = (array1)[h][w] - (array2)[h][w];
             sum += current*current;
        }//w
    }//h
    //return mean
    return sum/dims.Volume();
}

double PSNR(double mse)
{
    if (mse > 0)
        return 10 * log10((255 * 255) / mse);
    else
        return DBL_MAX;  
}

std::vector<double> PSNR(Picture original, Picture reconstructed)
{
    assert(original.height() == reconstructed.height());
    assert(original.width() == reconstructed.width());
    //compute mse
    double mse = -1;
    std::vector<double> results;
    double mseAll = 0;
    for( int i = 0; i < NOFCHANNELS ; i++)
    {
        mse = MSE(original.Array((Channel)i), reconstructed.Array((Channel)i));
        results.push_back(PSNR(mse));
        mseAll+= mse;
    }
    results.push_back (PSNR ( mseAll / NOFCHANNELS ));
    return results;
}

