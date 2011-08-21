#include "../cubecodec/general.h"
#include "../cubecodec/types.h"

int testStatistics()
{
    //generate array
    Coords3D dims(16,32,4);
    CoeffArray3D array(extents[dims.depth][dims.height][dims.width]);
    CoeffView3D view = array[ indices[range()][range()][range()] ];
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                view[d][h][w] = (CoeffType)rand()%256;
            }//w
        }//h
    }//d
    //get map
    CoeffMap map = getSymbolStatistics(view);
    //wrtire map
    writeMap(map, "out/test_map");
    return 0;
}

int testEncoderCompressDecompress()
{
                    //coeffCube.SmoothTime();
                
                //testing: compress and decompress cube to validate
                //compressed data
                //CompressAll();
//                
//                std::ofstream* file = new std::ofstream("file", std::ios::out | std::ios::binary);
//                OutputCube(file);
//                file->close();
//                std::ifstream* infile = new std::ifstream("file", std::ios::in | std::ios::binary);
//                ReadCube(infile);
//                
//                
//                DecompressAll();
                // get statistics for the cube
return 0;                
}

int runTests2()
{
    testStatistics();
    return 0;
}
