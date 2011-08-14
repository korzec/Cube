

#include "PictureIO.h"
#include "types.h"
#include "Picture.h"
#include "Encoder.h"
#include "PictureBuffer.h"
#include "WaveletTransform.h"
#include "Subcube.h"
#include "Compressor.h"
#include "CubeIO.h"
//#include "SubcubeIndex.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cassert>

using namespace std;

int testCompressWriteReadDecompress()
{       
    //generate arrays
    Coords3D subDims(16,32,4);
    CoeffArray3D array1(extents[subDims.depth][subDims.height][subDims.width]);
    CoeffArray3D array2(extents[subDims.depth][subDims.height][subDims.width]);
    CoeffView3D subcubeView1 =  array1[ indices[range()][range()][range()] ];
    CoeffView3D subcubeView2 =  array2[ indices[range()][range()][range()] ];
    for (int d = 0; d < subDims.depth; d++)
    {
        for (int h = 0; h < subDims.height; h++)
        {
            for (int w = 0; w < subDims.width; w++)
            {
                array1[d][h][w] = (CoeffType)rand();
                array2[d][h][w] = (CoeffType)rand();
            }//w
        }//h
    }//d
    
    //Compress the subcubes
    Coords3D location(4,4,4);
    Compressor compressor;
    Packet packet1 = compressor.Compress(subcubeView1, location);
    Packet packet2 = compressor.Compress(subcubeView2, location);
    
    Parameters parameters;
    Coords3D fullDims(100,20,4);
    parameters.codecParams.cubeSize = fullDims;
    parameters.codecParams.subcubeSize = subDims;
    parameters.codecParams.levels = 2;
    
    VideoParams videoParams;
    videoParams.fpsDenominator = 1;
    videoParams.fpsNumerator = 30;
    videoParams.frameCount = 100;
    //now save to file
    std::stringstream ss1; ss1 << OUTDIR << "testCompressWriteReadDecompress";
    std::string fileName = ss1.str();
    
    CubeIO cubeIO;
    bool result = cubeIO.Init(fileName, true);
    assert(result);
    {//write  seq heder   
        result = cubeIO.WriteSequenceHeader(parameters, videoParams);
        assert(result);
    }
    
    //save cube number
    int cubeNumber = 559;
    {
        bool result = cubeIO.WriteCubeHeader(cubeNumber);
        assert(result);
    }
    
    //save packets
    {
        bool result = cubeIO.WritePacket(packet1);
        assert(result);
        result = cubeIO.WritePacket(packet2);
        assert(result);
    }
    
    cubeIO.Finish();
    assert(cubeIO.Init(fileName, false));
    
    //check Seq header
    {//case with reading a file
        Parameters codingP2;
        VideoParams videoP2;
        
        bool result = cubeIO.ReadSequenceHeader(codingP2, videoP2);
        assert(result);
        std::cout << "old " << parameters.codecParams.levels << " new " << codingP2.codecParams.levels << std::endl;
        assert(parameters.codecParams.levels == codingP2.codecParams.levels);
        assert(parameters.codecParams.subcubeSize.Volume() == codingP2.codecParams.subcubeSize.Volume());
        assert(parameters.codecParams.cubeSize.Volume() == codingP2.codecParams.cubeSize.Volume());
        
        //check if parametersAre the same;
        
        //TODO: parameters should be separated from runtime encoder switches etc
    }
    
    
    
    //check cube header
    { //read and compare
        int readNumber;
        bool result = cubeIO.ReadCubeHeader(readNumber);
        assert(result);
        std::cout << "old " << cubeNumber << " new " << readNumber << std::endl;
        assert(cubeNumber == readNumber);
    }
    
    
    Packet newPacket1;
    Packet newPacket2;
    
    { //read  packets
        newPacket1 = cubeIO.ReadPacket();
        newPacket2 = cubeIO.ReadPacket();
        assert(packet1.compressedSize == newPacket1.compressedSize);
        assert(packet1.fullSize == newPacket1.fullSize);
        assert(packet1.location.Volume() == newPacket1.location.Volume());
        for (int i = 0; i < packet1.compressedSize; i++)
        {
            assert(packet1.compressedData.get()[i] ==
                                 newPacket1.compressedData.get()[i]);
            assert(packet2.compressedData.get()[i] ==
                                 newPacket2.compressedData.get()[i]);
        }
    }
    
    

    
    //decompress now
    CoeffArray3DPtr newArray1 = compressor.Decompress(newPacket1, subDims);
    CoeffArray3DPtr newArray2 = compressor.Decompress(newPacket2, subDims);
    
    if (true /*check result*/)
    {
        assert(subDims.Volume() == Coords3D(newArray1->shape()).Volume());
        for (int d = 0; d < subDims.depth; d++)
        {
            for (int h = 0; h < subDims.height; h++)
            {
                for (int w = 0; w < subDims.width; w++)
                {
                    assert(array1[d][h][w] == (*newArray1)[d][h][w]);
                    assert(array2[d][h][w] == (*newArray2)[d][h][w]);
                }//w
            }//h
        }//d
    }
    
    return 0;
}

int testDumpSubcubes()
{
    Coords3D dims(128,256,16);
    CoeffArray3D array(boost::extents[dims.depth][dims.height][dims.width]);
    CoeffView3D view = array[ indices[range()][range()][range()] ];
    Coords3D size(32,32,4);
    
    SubcubeIndex subcubes;
    subcubes.Init(view, size);
    
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                /// d = x_2n+1 - x_2n
                view[d][h][w] = CoeffType((d+h+w)%255);
            }
        }
    } 
    
    subcubes.ComputeWeights();
    
    std::stringstream ss1;
    ss1 << OUTDIR << "test_" << "cube.raw";
    subcubes.dump(ss1.str());
    std::cout<<"wrote test cube"<<std::endl;
    return 0;
}

int testSubcubeIndex()
{
    Coords3D dims(128,256,16);
    CoeffArray3D array(boost::extents[dims.depth][dims.height][dims.width]);
    CoeffView3D view = array[ indices
                        [range(0,dims.depth)]
                        [range(0,dims.height)]
                        [range(0,dims.width)] ];
    Coords3D size(32,32,4);
    Coords3D index(0,0,0);
    
    SubcubeIndex subcubes;
    subcubes.Init(view, size);
    
    assert(subcubes.GetSubcube(index).GetLocation().depth == index.depth);
    
    //test with initialisation
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                /// d = x_2n+1 - x_2n
                view[d][h][w] = CoeffType((d+h+w)%255);
            }
        }
    } 
    
    Subcube subcube = subcubes.GetSubcube(index);
    
    dims = subcube.GetSize();
    
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                /// d = x_2n+1 - x_2n
                assert( view[d][h][w] == subcube.GetView()[d][h][w] );
            }
        }
    } 
        
    
    index.Set(1,1,1);
    subcube = subcubes.GetSubcube(index);
    dims = subcube.GetSize();
    
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                /// d = x_2n+1 - x_2n
                assert( view[d+dims.depth][h+dims.height][w+dims.width]
                        == subcube.GetView()[d][h][w] );
            }
        }
    } 
    
    return 0;
}

int testSubcube()
{
    Coords3D dims(128,256,16);
    CoeffArray3D array(boost::extents[dims.depth][dims.height][dims.width]);
    CoeffView3D view = array[ indices
                        [range(0,dims.depth)]
                        [range(0,dims.height)]
                        [range(0,dims.width)] ];
    Coords3D size(32,32,4);
    Coords3D index(0,0,0);
    
    Subcube subcube;
    subcube.Init(view, index, size);
    
    assert(subcube.GetLocation().depth == index.depth);
    
    return 0;
}

int testView()
{
    Coords3D dims(32,32,4);
    CoeffArray3D array(boost::extents[dims.depth][dims.height][dims.width]);
    CoeffView3D view = array[ indices
                        [range(0,dims.depth)]
                        [range(0,dims.height)]
                        [range(0,dims.width)] ];
    assert(array.size() == view.size());
    return 0;
}

int testSubbandList()
{
    int width = 32;
    int height = 16;
    int depth = 4;
    CoeffArray3DPtr arrayY = CoeffArray3DPtr(new CoeffArray3D(boost::extents[depth][height][width]));
//    CoeffArray3DPtr arrayU = CoeffArray3DPtr(new CoeffArray3D(boost::extents[depth][height>>1][width>>1]));
//    CoeffArray3DPtr arrayV = CoeffArray3DPtr(new CoeffArray3D(boost::extents[depth][height>>1][width>>1]));
    
    Coords3D dims(arrayY->shape());
    
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                /// d = x_2n+1 - x_2n
                (*arrayY)[d][h][w] = CoeffType((d+h+w)%255);
            }
        }
    }   
    
    SubbandList subbandsY;
    int level = 2;
    subbandsY.Init(*arrayY, level);
    
    assert(subbandsY.GetLevel() == level);
    
    CoeffView3D y = subbandsY.GetSubband(0, LLL);
//    size_t ysize = y.size();
//    size_t arraysize = arrayY->size();
    assert(y.size() == arrayY->size());
    
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                /// d = x_2n+1 - x_2n
                assert( (*arrayY)[d][h][w] == CoeffType((d+h+w)%255) );
                assert( (*arrayY)[d][h][w] == y[d][h][w] );
            }
        }
    }   
    
    CoeffView3D sub1 = subbandsY.GetSubband(1,LLL);   
    
    dims = Coords3D(sub1.shape());
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                /// d = x_2n+1 - x_2n
                assert( (*arrayY)[d][h][w] == CoeffType((d+h+w)%255) );
                assert( (*arrayY)[d][h][w] == sub1[d][h][w] );
            }
        }
    }   
    
//    subbandsU.Init(U(), levels);
//    subbandsV.Init(V(), levels);
    return 0;
}

int testPictureReadWrite() {
    string input = "src7.yuv";
    std::ifstream inputPicture(input.c_str(), std::ios::in | std::ios::binary);
    if (!inputPicture) {
        std::cerr << std::endl <<
                "Can't open input data file: " << input << std::endl;
        return EXIT_FAILURE;
    } else
        std::cout << "opened file " << input << std::endl;

    //std::cout << "w " <<  << "h " << encoder.params.height << std::endl;
    Picture picture = PictureIO::ReadPicture(inputPicture, 720, 576);

    assert(picture.width() == 720);
    assert(picture.height() == 576);
    
    /// open the decoded output file
    std::ofstream *outputPicture = NULL;

    std::string outputPictureName = input + ".test.yuv";
    outputPicture = new std::ofstream(outputPictureName.c_str(), std::ios::out | std::ios::binary);

    Picture outPicture(720, 576);
    outPicture = picture;

    for (int i = 0; i < picture.height(); i++)
        for (int j = 0; j < picture.width(); j++)
            //for (int i = 0; i < fb->width*fb->height; i++)
        {
            assert(picture.Array(Ych)[i][j] == outPicture.Array(Ych)[i][j]);
        }
    for (int i = 0; i < picture.chromaHeight(); i++)
        for (int j = 0; j < picture.chromaWidth(); j++)
            //for (int i = 0; i < fb->width*fb->height; i++)
        {
            assert(picture.Array(Uch)[i][j] == outPicture.Array(Uch)[i][j]);
            assert(picture.Array(Vch)[i][j] == outPicture.Array(Vch)[i][j]);
        }

    PictureIO::WritePicture(*outputPicture, outPicture);
    outputPicture->close();
    delete outputPicture;
    
    std::cout << "tests completed" << std::endl;

    return 0;
}

int testEncode()
{
    Encoder encoder;
    Parameters params;
    params.codecParams.cubeSize.width = 16;
    params.codecParams.cubeSize.height = 20;
    params.codecParams.cubeSize.depth = 4;
    encoder.SetParams(params);
    
    Picture picture(params.codecParams.cubeSize.width, params.codecParams.cubeSize.height);
    
    assert(encoder.GetParams().codecParams.cubeSize.depth == 4);
    encoder.LoadNextPicture(picture);
    encoder.LoadNextPicture(picture);
    encoder.LoadNextPicture(picture);
    encoder.LoadNextPicture(picture);
    EncoderState state = encoder.Encode();
    assert(state == PICTURE_AVAILABLE);
    if (state == PICTURE_AVAILABLE)
        std::cout << "Picture available " << state << std::endl;
    
    return 0;    
}

int testDeinterleave()
{
    Coords3D dims(10,2,2);
    CoeffArray3D arrayWdata(boost::extents[dims.depth][dims.height][dims.width]);
    CoeffView3D arrayW = arrayWdata[ indices[range()][range()][range()]];

    ///set values;
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                arrayW[d][h][w] = (d+h+w)%255;          
            }
        }
    }
    
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                std::cout << arrayW[d][h][w] <<" ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    
    WaveletTransform transform;
    transform.Forward(arrayW);
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                std::cout << arrayW[d][h][w] <<" ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    transform.Reverse(arrayW);
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                std::cout << arrayW[d][h][w] <<" ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    
    return 0;
    
}

int testSplit()
{
    int len = 10;
    CoeffArray3D arrayWdata(boost::extents[1][1][len]);
    CoeffArray3D arrayHdata(boost::extents[1][len][1]);
    CoeffArray3D arrayDdata(boost::extents[len][1][1]);

    CoeffView3D arrayW = arrayWdata[ indices[range()][range()][range()] ];
    CoeffView3D arrayH = arrayHdata[ indices[range()][range()][range()] ];
    CoeffView3D arrayD = arrayDdata[ indices[range()][range()][range()] ];
    
    Coords3D dims(len,1,1);
    ///set values;
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                arrayW[d][h][w] = (d+h+w)%255;
                arrayH[d][w][h] = (d+h+w)%255;
                arrayD[w][h][d] = (d+h+w)%255;           
            }
        }
    }
    
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                assert(arrayW[d][h][w] == arrayH[d][w][h]);
                assert(arrayH[d][w][h] == arrayD[w][h][d]);  
                std::cout << arrayW[d][h][w] << " " << arrayH[d][w][h]
                        <<" " << arrayD[w][h][d] << std::endl;
            }
        }
    }
    
    WaveletTransform transform;
    transform.Forward(arrayW);
    transform.Forward(arrayH);
    transform.Forward(arrayD);
    
    /// compare if results are the same for each direction
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                assert(arrayW[d][h][w] == arrayH[d][w][h]);
                assert(arrayH[d][w][h] == arrayD[w][h][d]);           
                std::cout << arrayW[d][h][w] << " " << arrayH[d][w][h]
                        <<" " << arrayD[w][h][d] << std::endl;
            }
        }
    }
    
    return 0;
}

int testGetGOP()
{
    PictureBuffer buffer(4);
    boost::shared_ptr<Picture> p = boost::shared_ptr<Picture> (new Picture(4,4));
    buffer.Add(*p);
    p.reset( new Picture(4,4) );
    buffer.Add(*p);
    
    PictureVector gop;
    bool ret = buffer.GetGOP(4,gop);
    assert(ret == false);
    assert(gop.size() == 0);
    
    p.reset( new Picture(4,4) );
    buffer.Add(*p);
    p.reset( new Picture(4,4) );
    buffer.Add(*p);
    p.reset( new Picture(4,4) );
    buffer.Add(*p);
    p.reset( new Picture(4,4) );
    buffer.Add(*p);

    ret = buffer.GetGOP(4, gop);
    assert(ret == true);
    assert(gop.size() == 4);
    return 0;
}

int testVectorPicture()
{
    PictureVector* v;
    v = new PictureVector;
    Picture pic(4,4);
    
    v->assign(2,pic);
    
    delete v;
    return 0;
}

int testLoadGOP()
{
    //create cube
    Coords3D size(16,8,4);
    Coords3D subSize(4,4,4);
    CoeffCube cube(size,1,subSize);
    Coords3D dims = cube.Dimensionality();
    //crate gop
    PictureVector gop;
    //Picture pic(dims.width, dims.height);
    //gop.assign(dims.depth, pic);
    
    //generate 4 different pictures
    gop.push_back(Picture(dims.width,dims.height));
    gop.push_back(Picture(dims.width,dims.height));
    gop.push_back(Picture(dims.width,dims.height));
    gop.push_back(Picture(dims.width,dims.height));
    
    //init gop values;
    for (int d = 0; d < dims.depth; d++)
    {
        Picture pic = gop[d];
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
//                int x = gop[d].Y().shape()[0];
//                int y = gop[d].Y().shape()[1];
//                int z = gop.size();
                gop[d].Array(Ych)[h][w] = (d+h+w)%255;
            }
        }
    }
    //run LoadGOP();
    cube.LoadGOP(gop);
    CoeffType coeff = cube.Array(Ych)[0][0][0];
    ValueType value = gop[0].Array(Ych)[0][0];
    assert(coeff == value);
    assert(cube.Array(Ych)[0][0][0] == gop[0].Array(Ych)[0][0]);
    
    //validate values;
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                assert(cube.Array(Ych)[d][h][w] == CoeffType ((d+h+w)%255));
            }
        }
    }
    
    
    
    
    std::cout << "loadGOP tested" <<std::endl;
    return 0;
}

int testOutput() {
    int w = 16;
    int h = 16;
    Picture picture(w, h);


    //output test:

    for (int i = 0; i < picture.height(); i++)
        for (int j = 0; j < picture.width(); j++) {
            picture.Array(Ych)[i][j] = 'z';
            if (j == w - 1)
                picture.Array(Ych)[i][j] = '\n';
        }

    // open the decoded ouput file
    std::ofstream *OutputFile = NULL;

    std::string outputPictureName = "outputTest.txt";
    OutputFile = new std::ofstream(outputPictureName.c_str(),
            std::ios::out | std::ios::binary);

    std::cout << "result: " << PictureIO::WritePicture(*OutputFile, picture) << std::endl;
    OutputFile->close();
    return 0;
}

int testTypesConctructors() {
    Picture p1;
    Picture p2(16, 16);

    FrameBuffer f1();
    FrameBuffer f2(16, 16);

    //FrameBuffer* f = (FrameBuffer*)55555;
    //assert(f->buf[0] = (unsigned char*)8);
    //f->buf[0] = (unsigned char*)8;

    ///impossible to catch bad pointer exception
    //	FrameBuffer* f = (FrameBuffer*)55555;
    //	try{
    //	Picture* p = new Picture(f);
    //	delete p;
    std::cout << "types tested" << std::endl;
    //	{
    //	Picture p3(f);
    //	}
    //	} catch(...) {
    //		std::cerr << "OMG";
    //	}
    return 0;
}

int testFrameBufferIO() {
    string input = "/dev/zero";
    std::ifstream inputPicture(input.c_str(), std::ios::in | std::ios::binary);
    if (!inputPicture) {
        std::cerr << std::endl <<
                "Can't open input data file: " << input << std::endl;
        return EXIT_FAILURE;
    } else
        std::cout << "opened file " << input << std::endl;

    //std::cout << "w " <<  << "h " << encoder.params.height << std::endl;
    FrameBuffer* fb = PictureIO::ReadPictureData(inputPicture, 16, 16);

    std::cout << "Xw " << fb->width << "h " << fb->height << std::endl;
    assert(fb->data == fb->buf[0]);
    assert(fb->width == 16);
    assert(fb->height == 16);

    if (fb)
        std::cout << "frame read" << std::endl;

    //for(int i=0; i <fb.height; i++)
    //  for (int j = 0; j < fb->width; j++)
    for (int i = 0; i < fb->width * fb->height; i++) {
        //std::cout << int(fb->buf[0][i]);
        assert(fb->buf[0][i] == 0);
    }

    std::cout << "tests completed" << std::endl;

    return 0;
}

int testPictureIO() {
    string input = "/dev/zero";
    std::ifstream inputPicture(input.c_str(), std::ios::in | std::ios::binary);
    if (!inputPicture) {
        std::cerr << std::endl <<
                "Can't open input data file: " << input << std::endl;
        return EXIT_FAILURE;
    } else
        std::cout << "opened file " << input << std::endl;

    //std::cout << "w " <<  << "h " << encoder.params.height << std::endl;
    Picture picture = PictureIO::ReadPicture(inputPicture, 16, 16);

    assert(picture.width() == 16);
    assert(picture.height() == 16);

    for (int i = 0; i < picture.height(); i++)
        for (int j = 0; j < picture.width(); j++)
            //for (int i = 0; i < fb->width*fb->height; i++)
        {
            assert(picture.Array(Ych)[i][j] == 0);
            //assert(picture.U()[i>>1][j>>1] == 0);
            //assert(picture.V()[i>>1][j>>1] == 0);
        }
    
    for (int i = 0; i < picture.chromaHeight(); i++)
        for (int j = 0; j < picture.chromaWidth(); j++)
            //for (int i = 0; i < fb->width*fb->height; i++)
        {
            //assert(picture.Y()[i][j] == 0);
            assert(picture.Array(Uch)[i][j] == 0);
            assert(picture.Array(Vch)[i][j] == 0);
        }

    std::cout << "basic picture IO finished " << std::endl;

    return 0;
}

int runTests() {
    
    testCompressWriteReadDecompress();
    testDumpSubcubes();
    testSubcubeIndex();
    testSubcube();
    testView();
    testSubbandList();
    testPictureReadWrite();
    testEncode();
    testDeinterleave();
    testSplit();
    testGetGOP();
    testVectorPicture();
    testLoadGOP();
    testOutput();
    testTypesConctructors();
    testFrameBufferIO();
    testPictureIO();
    std::cout << "********** all tests finished" << std::endl;
    return 0;
}
