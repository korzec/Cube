#include "../cubecodec/general.h"
#include "../cubecodec/types.h"
#include "../cubecodec/CompressorHuffman.h"
#include <cassert>
#include <bitset>

int testInsertBit()
{
    Codeword  word;
    word.insertBit(1);
    word.insertBit(0);
    word.insertBit(1);
    assert(word.GetLength() == 3);
    std::bitset<8> bits = word.GetSequence().get()[0];
    std::cout << bits << std::endl;
    std::cout << word.toString() << std::endl;
    assert(word.GetSequence().get()[0] == 160);
    
    //test if cloning works properly for codewords
    assert(word.Clone().GetLength() == 3);
    assert(word.Clone().GetSequence().get()[0] == 160);

    Codeword super;
    std::cout << super.toString() << std::endl;
    super.insertBit(1);
    std::cout << super.toString() << std::endl;
    super.insertBit(0);
    std::cout << super.toString() << std::endl;
    super.insertBit(1);
    std::cout << super.toString() << std::endl;
    super.insertBit(0);
    std::cout << super.toString() << std::endl;
    super.insertBit(1);
    std::cout << super.toString() << std::endl;
    super.insertBit(0);
    std::cout << super.toString() << std::endl;
    super.insertBit(1);
    std::cout << super.toString() << std::endl;
    super.insertBit(0);
    assert(super.GetSequence().get()[0] == 170 );
    std::cout << super.toString() << std::endl;
    
    super.insertBit(1);
    std::cout << super.toString() << std::endl;
    super.insertBit(0);
    std::cout << super.toString() << std::endl;
    super.insertBit(1);
    std::cout << super.toString() << std::endl;
    super.insertBit(0);
    std::cout << super.toString() << std::endl;
    super.insertBit(1);
    std::cout << super.toString() << std::endl;
    super.insertBit(0);
    std::cout << super.toString() << std::endl;
    super.insertBit(1);
    std::cout << super.toString() << std::endl;
    super.insertBit(0);
    assert(super.GetSequence().get()[1] == 170 );
    assert(super.GetSequence().get()[0] == 170 );
    std::cout << super.toString() << std::endl;
    
    return 0;
}

int testHuffCompression()
{
    //create compressor
    CompressorHuffman compressor;
    //create example data to compress
    Coords3D dims(128,256,16);
    CoeffArray3D array(boost::extents[dims.depth][dims.height][dims.width]);
    CoeffView3D view = array[ boost::indices[range()][range()][range()] ];
    
    //test with initialisation
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                /// d = x_2n+1 - x_2n
                view[d][h][w] = (CoeffType((random())%255)) << 2;
            }
        }
    }
    
     Coords3D superDims;
    
    //compress the data 
    Packet packet = compressor.Compress(view, superDims, Ych, 666);
    //check sizes
    std::cout << "compressed size: " << packet.header.compressedSize <<std::endl;
    //decompress data
    CoeffArray3DPtr data = compressor.Decompress(packet, dims );
    //verify data
    Coords3D newDims(data->shape());
    assert(dims.depth == newDims.depth );
    assert(dims.height == newDims.height );
    assert(dims.width == newDims.width );
    
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                assert(view[d][h][w] == (*data)[d][h][w]);
            }
        }
    }
    
    
    return 0;
}

int testHuffTree()
{
    
    CompressorHuffman compressor;
    Codeword word = compressor.GetCodeword(0);
    assert(word.GetLength() > 0);
    assert(word.GetSequence().use_count() > 0);
    std::cout << word.toString();
    CoeffPair symbolPair = compressor.GetSymbol(0);
    
    //print all symbols
    CodewordMap* dict = &compressor.GetDictionary();
    
    //check if dictionary is a 1:1 mapping
    std::map<std::string, CoeffType> map;
    CodewordMap::iterator it = compressor.GetDictionary().begin();
    for (; it != compressor.GetDictionary().end(); it++)
    {
        map.insert(std::pair<std::string, CoeffType>(it->second.toString(), it->first));
    }
    assert(dict->size() == map.size());
    std::map<std::string, CoeffType>::iterator iter = map.begin();
//    for (; iter != map.end(); iter++)
//    {
//        std::cout << iter->second << "\t, " << iter->first << std::endl;
//    }
    
    
    it = compressor.GetDictionary().begin();
    for (; it != compressor.GetDictionary().end(); it++)
    {
        std::bitset<sizeof(CoeffType)*8> bin = it->first;
        std::cout << it->first << "\t, " << bin << ", "
                  << it->second.GetLength() << "\t,"
                  << it->second.toString()
                  << std::endl;
    }
    
    
    
    
    return 0;
}

int testStatistics()
{
    //generate array
    Coords3D dims(16,32,4);
    CoeffArray3D array(boost::extents[dims.depth][dims.height][dims.width]);
    CoeffView3D view = array[ boost::indices[range()][range()][range()] ];
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
    testInsertBit();
    testHuffTree();
    testStatistics();
    return 0;
}
