#include "../cubecodec/general.h"
#include "../cubecodec/types.h"
#include "../cubecodec/CompressorHuffman.h"
#include "../cubecodec/MQcoder.h"
#include "../cubecodec/CompressorAC.h"
#include <cassert>
#include <bitset>
//#include <boost/math/distributions/normal.hpp>
//test get bit at
#include <boost/random/variate_generator.hpp>
#include <boost/random.hpp>
#include <boost/math/distributions.hpp>
//test get symbol

using namespace MQcoder;

int testACcompress()
{
    //generate arrays
    Coords3D subDims(16,32,4);
    CoeffArray3D array1(boost::extents[subDims.depth][subDims.height][subDims.width]);
    CoeffView3D subcubeView1 =  array1[ boost::indices[range()][range()][range()] ];
    for (int d = 0; d < subDims.depth; d++)
    {
        for (int h = 0; h < subDims.height; h++)
        {
            for (int w = 0; w < subDims.width; w++)
            {
                array1[d][h][w] = 89+h;//(CoeffType)rand()%2;
            }//w
        }//h
    }//d
    
    //Compress the subcubes
    Coords3D location(4,4,4);
    CompressorPtr compressor(new CompressorAC());
    Packet packet1 = compressor->Compress(subcubeView1, location, Ych, 1);
    
    std::cout << "" <<std::endl;
    std::cout << "AC compress test finished" <<std::endl;
    
    return 0;
}

int testBitPlaneStreamWrite()
{
    int byteCount = 4*sizeof(CoeffType);
    ucharPtr data = ucharPtr(new unsigned char [byteCount]);
    memset(data.get(), 0, byteCount);
    CoeffType* num = (CoeffType*)data.get();
    
    //map the MSBit of LSByte as a new stream
    BitPlaneStream bitplane(byteCount, data, 0, sizeof(CoeffType), true );
    bitplane.insertBit(1);
    bitplane.insertBit(0);
    bitplane.insertBit(1);
    bitplane.insertBit(1);
    
    //map LSBit of MSByte as a new stream
    BitPlaneStream bitplane2(byteCount, data, 15 , sizeof(CoeffType), true );
    bitplane2.insertBit(0);
    bitplane2.insertBit(0);
    bitplane2.insertBit(1);
    bitplane2.insertBit(1);
    
    //check if numbers are correct after modifying a bitplane
    assert(num[0] == 0x0080);
    assert(num[1] == 0x0000);
    assert(num[2] == 0x0180);
    assert(num[3] == 0x0180);
    
    
    std::cout << "bitplane  stream write test finished" <<std::endl;
    return 0;
}

int testBitPlaneStreamRead()
{
    short num1[4] = { 1 ,0x0000 ,0xFFFF ,0x0000 };
    unsigned char data1[8] = { 1 ,0 ,0x00 ,0x00 ,0xFF ,0xFF ,0x00 ,0x00 };
    //init a memory
    ucharPtr data2 = ucharPtr(new unsigned char [8]);
    ucharPtr num2 = ucharPtr(new unsigned char [8]);
    memcpy(data2.get(), data1, 8);
    memcpy(num2.get(), num1, 8);
    BitStream bits(8, data2);
    
    std::cout << bits.toString() << std::endl;
    
    //map bitplane to initialized buffer
    
    for(int i=0; i < 16;i++)
    {
        BitPlaneStream bitplane(8, data2, i, 2, false );
        BitPlaneStream bitplaneNum(8, num2, i, 2, false );
        assert(strcmp(bitplane.toString().c_str(), bitplaneNum.toString().c_str()) == 0);
        //std::cout << bitplane.toString() << " : " << bitplaneNum.toString() << std::endl;
    }
            
    //check if the bitstream is correct
            
    std::cout << std::endl << "bitplane  stream read test finished" <<std::endl;
    return 0;
}

int testMQencodeDecode()
{
    int byteCount = 9999;
    
    ucharPtr inData = ucharPtr(new unsigned char[byteCount]);
    memset(inData.get(), 240, byteCount);
    memset(inData.get(), 255, byteCount>>4);
    
    BitStream original(byteCount, inData);
    
    BitStream encoded(original.ByteSize()*2);
    
    MQencoder qmEnc(original, encoded);
    qmEnc.Encode();
    //assert(qmEnc.GetCodedBytes());
    std::bitset<8> bits;
    int number;
    std::cout << "MQ coded: " << qmEnc.GetCodedBytes() <<std::endl;
//    for(int i=0; i < qmEnc.GetCodedBytes(); i++)
//    {
//        bits = encoded.GetSequence().get()[i];
//        number = encoded.GetSequence().get()[i];
//        std::cout << " " << std::setw(2) << std::setfill('0') << std::hex << bits << std::dec; 
//        //assert(output.GetSequence()[i] == coded[i]);
//    }    
    
    BitStream decoded(original.ByteSize());
    
    MQdecoder mqDec(encoded, decoded, original.GetLength() );
    mqDec.Decode();
    //std::cout << std::endl << " decoded bytes count:  " << decoded.ByteSize() << std::endl;
    //std::cout << std::endl << " original bytes count: " << original.ByteSize() << std::endl;
    
    assert(original.ByteSize() == byteCount);
    assert(original.ByteSize() == decoded.ByteSize());
    
    for(int i=0; i < original.ByteSize(); i++)
    {
        //assert(decoded.GetSequence().get()[i] == data[i]);
        //number = decoded.GetSequence().get()[i];
        //std::cout << " " << std::setw(2) << std::setfill('0') << std::hex << number << std::dec; 
    }
    std::cout << std::endl << "MQ code-decode test finished" <<std::endl;
    return 0;
}

int testMQdecoder()
{
    unsigned char data[32] = { 0x00 ,0x02 ,0x00 ,0x51 ,0x00 ,0x00 ,0x00 ,0xC0,
                               0x03 ,0x52 ,0x87 ,0x2A ,0xAA ,0xAA ,0xAA ,0xAA,
                               0x82 ,0xC0 ,0x20 ,0x00 ,0xFC ,0xD7 ,0x9E ,0xF6,
                               0xBF ,0x7F ,0xED ,0x90 ,0x4F ,0x46 ,0xA3 ,0xBF };
    
    unsigned char coded[60] = { 0x84, 0xc7, 0x3b, 0xfc, 0xe1, 0xa1, 0x43, 0x04,  
                                0x02, 0x20, 0x00, 0x00, 0x41, 0x0d, 0xbb, 0x86, 
                                0xf4, 0x31, 0x7f, 0xff, 0x88, 0xff, 0x37, 0x47, 
                                0x1a, 0xdb, 0x6a, 0xdf, 0xff, 0xac,  
                                0x84, 0xc7, 0x3b, 0xfc, 0xe1, 0xa1, 0x43, 0x04,  
                                0x02, 0x20, 0x00, 0x00, 0x41, 0x0d, 0xbb, 0x86, 
                                0xf4, 0x31, 0x7f, 0xff, 0x88, 0xff, 0x37, 0x47, 
                                0x1a, 0xdb, 0x6a, 0xdf, 0xff, 0xac,  };
    ucharPtr inData = ucharPtr(new unsigned char[30]);
    memcpy(inData.get(), coded, 60);
    BitStream input(60, inData);
    
    BitStream output(32);
    BitStream output2(32);
    
    MQdecoder mqDec(input, output, 32*8);
    mqDec.Decode();
    mqDec.Continue(output2,32*8);
    //show result
//    std::cout << "qm decoder:" << std::endl;
//    std::bitset<8> bits;
//    int number;
    for(int i=0; i < 32; i++)
    {
//        bits = output.GetSequence().get()[i];
//        number = output.GetSequence().get()[i];
//        std::cout << " " << std::setw(2) << std::setfill('0') << std::hex << number << std::dec; 
        assert(output.GetSequence().get()[i] == data[i]);
        assert(output2.GetSequence().get()[i] == data[i]);
    }
    
    std::cout << "qm decoder test finished" << std::endl;
    return 0;
}

int testReference()
{
    unsigned int C;
    unsigned short& Clow = (*((unsigned short*)(&C)));
    unsigned short& Chigh = (*((unsigned short*)(&C)+1));
    std::bitset<sizeof(unsigned short)*8> low;
    std::bitset<sizeof(unsigned short)*8> high;
    std::bitset<sizeof(unsigned int)*8> full;
    
    C = 0x000088AA;
    full = C;
    low = Clow;
    high = Chigh;
    
    std::cout << "C: " << C << " : " << full << std::endl;
    std::cout << "Clow: " << Clow << " : " << low << std::endl;
    std::cout << "Chigh: " << Chigh << " : " << high << std::endl;

    return 0;
}

int testMQencoder()
{
    //init input data and allocate output buffer;
    
    unsigned char data[64] = { 0x00 ,0x02 ,0x00 ,0x51 ,0x00 ,0x00 ,0x00 ,0xC0,
                               0x03 ,0x52 ,0x87 ,0x2A ,0xAA ,0xAA ,0xAA ,0xAA,
                               0x82 ,0xC0 ,0x20 ,0x00 ,0xFC ,0xD7 ,0x9E ,0xF6,
                               0xBF ,0x7F ,0xED ,0x90 ,0x4F ,0x46 ,0xA3 ,0xBF,
                               0x00 ,0x02 ,0x00 ,0x51 ,0x00 ,0x00 ,0x00 ,0xC0,
                               0x03 ,0x52 ,0x87 ,0x2A ,0xAA ,0xAA ,0xAA ,0xAA,
                               0x82 ,0xC0 ,0x20 ,0x00 ,0xFC ,0xD7 ,0x9E ,0xF6,
                               0xBF ,0x7F ,0xED ,0x90 ,0x4F ,0x46 ,0xA3 ,0xBF, };
    
    unsigned char coded[30] = { 0x84, 0xc7, 0x3b, 0xfc, 0xe1, 0xa1, 0x43, 0x04,  
                                0x02, 0x20, 0x00, 0x00, 0x41, 0x0d, 0xbb, 0x86, 
                                0xf4, 0x31, 0x7f, 0xff, 0x88, 0xff, 0x37, 0x47, 
                                0x1a, 0xdb, 0x6a, 0xdf, 0xff, 0xac,  };
    
    ucharPtr inData = ucharPtr(new unsigned char[32]);
    memcpy(inData.get(), data, 32);
    BitStream input(32, inData);
    
    ucharPtr inData2 = ucharPtr(new unsigned char[32]);
    memcpy(inData2.get(), data, 32);
    BitStream input2(32, inData2);
    
    BitStream output(64);
    
    MQencoder qmEnc(input, output);
    qmEnc.Encode();
    assert(qmEnc.GetCodedBytes() == 30);
    assert(output.GetLength() == 30*8);
    for(int i=0; i < qmEnc.GetCodedBytes(); i++)
    {
        assert(output.GetSequence()[i] == coded[i]);
    }
    
    qmEnc.Continue(input2);
    assert(qmEnc.GetCodedBytes() == 60);
    assert(output.GetLength() == 60*8);
    for(int i=30; i < qmEnc.GetCodedBytes(); i++)
    {
        assert(output.GetSequence()[i] == coded[i-30]);
    }
    
    std::cout << "qm decoder test finished" << std::endl;
//    std::cout<< " coded bytes count: " << qmEnc.GetCodedBytes() <<std::endl;
    return 0;
}

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
    //std::cout << super.toString() << std::endl;
    super.insertBit(1);
    //std::cout << super.toString() << std::endl;
    super.insertBit(0);
    //std::cout << super.toString() << std::endl;
    super.insertBit(1);
    //std::cout << super.toString() << std::endl;
    super.insertBit(0);
    //std::cout << super.toString() << std::endl;
    super.insertBit(1);
    //std::cout << super.toString() << std::endl;
    super.insertBit(0);
    //std::cout << super.toString() << std::endl;
    super.insertBit(1);
    //std::cout << super.toString() << std::endl;
    super.insertBit(0);
    assert(super.GetSequence().get()[0] == 170 );
    //std::cout << super.toString() << std::endl;
    
    super.insertBit(1);
    //std::cout << super.toString() << std::endl;
    super.insertBit(0);
    //std::cout << super.toString() << std::endl;
    super.insertBit(1);
    
    assert(strcmp(super.toString().c_str(), "10101010101") == 0);
    
    //std::cout << super.toString() << std::endl;
    super.insertBit(0);
    //std::cout << super.toString() << std::endl;
    super.insertBit(1);
    //std::cout << super.toString() << std::endl;
    super.insertBit(0);
    //std::cout << super.toString() << std::endl;
    super.insertBit(1);
    //std::cout << super.toString() << std::endl;
    super.insertBit(0);
    assert(super.GetSequence().get()[1] == 170 );
    assert(super.GetSequence().get()[0] == 170 );
    //std::cout << super.toString() << std::endl;
    
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
    
    //generate  normal distributed numbers
    boost::mt19937 gen;
    boost::normal_distribution<> gauss(0,64);
    boost::math::laplace_distribution<> laplace(0,64);
    boost::variate_generator<boost::mt19937&, boost::normal_distribution<> > coeffsGauss(gen, gauss);
    //boost::variate_generator<boost::mt19937&, boost::math::laplace_distribution<> > coeffsLaplace(gen, laplace);
    
    //test with initialisation
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                /// d = x_2n+1 - x_2n
                //view[d][h][w] = (CoeffType((random())%255)) << 2;
                view[d][h][w] = ((CoeffType(coeffsGauss()) % 256 ) << 2 );
                //view[d][h][w] = 255;
            }
        }
    }
    
    Coords3D superDims;
    
    //compress the data 
    Packet packet = compressor.Compress(view, superDims, Ych, 666);
    //check sizes
    std::cout << "compressed size: " << packet.header.compressedSize <<std::endl;
    std::cout << "full size: " << packet.header.fullSize <<std::endl;
    //decompress data
    CoeffArray3DPtr data = compressor.Decompress(packet, dims);
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
    
    
//    it = compressor.GetDictionary().begin();
//    for (; it != compressor.GetDictionary().end(); it++)
//    {
//        std::bitset<sizeof(CoeffType)*8> bin = it->first;
//        std::cout << it->first << "\t, " << bin << ", "
//                  << it->second.GetLength() << "\t,"
//                  << it->second.toString()
//                  << std::endl;
//    }
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
    testMQdecoder();
    
    testACcompress();
    testBitPlaneStreamWrite();
    testBitPlaneStreamRead();
    testMQencodeDecode();
    
    testReference();
    testMQencoder();
    testHuffCompression();
    testInsertBit();
    testHuffTree();
    testStatistics();
    return 0;
}
