

#include "cube_io.h"
#include "types.h"
#include "Encoder.h"
#include "PictureBuffer.h"
#include "WaveletTransform.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cassert>

int testEncode()
{
    Encoder encoder;
    CodingParams params;
    params.width = 16;
    params.height = 20;
    params.cubeDepth = 4;
    encoder.SetParams(params);
    
    Picture picture(params.width, params.height);
    
    assert(encoder.GetParams().cubeDepth == 4);
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
    CoeffArray3D arrayW(boost::extents[dims.depth][dims.height][dims.width]);

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
    CoeffArray3D arrayW(boost::extents[1][1][len]);
    CoeffArray3D arrayH(boost::extents[1][len][1]);
    CoeffArray3D arrayD(boost::extents[len][1][1]);
    
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
    buffer.Add(*(new Picture(4,4)));
    buffer.Add(*(new Picture(4,4)));
    
    PictureVector gop;
    bool ret = buffer.GetGOP(4,gop);
    assert(ret == false);
    assert(gop.size() == 0);
    
    buffer.Add(*(new Picture(4,4)));
    buffer.Add(*(new Picture(4,4)));
    buffer.Add(*(new Picture(4,4)));
    buffer.Add(*(new Picture(4,4)));

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
    CoeffCube cube(16,8,4);
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
                gop[d].Y()[h][w] = (d+h+w)%255;
            }
        }
    }
    //run LoadGOP();
    cube.LoadGOP(gop);
    CoeffType coeff = cube.Y()[0][0][0];
    ValueType value = gop[0].Y()[0][0];
    assert(coeff == value);
    assert(cube.Y()[0][0][0] == gop[0].Y()[0][0]);
    
    //validate values;
    for (int d = 0; d < dims.depth; d++)
    {
        for (int h = 0; h < dims.height; h++)
        {
            for (int w = 0; w < dims.width; w++)
            {
                assert(cube.Y()[d][h][w] == CoeffType ((d+h+w)%255));
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
            picture.Y()[i][j] = 'z';
            if (j == w - 1)
                picture.Y()[i][j] = '\n';
        }

    // open the decoded ouput file
    std::ofstream *OutputFile = NULL;

    std::string outputPictureName = "outputTest.txt";
    OutputFile = new std::ofstream(outputPictureName.c_str(),
            std::ios::out | std::ios::binary);

    std::cout << "result: " << WritePicture(*OutputFile, picture) << std::endl;
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
    FrameBuffer* fb = ReadPictureData(inputPicture, 16, 16);

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
    Picture picture = ReadPicture(inputPicture, 16, 16);

    assert(picture.width() == 16);
    assert(picture.height() == 16);

    for (int i = 0; i < picture.height(); i++)
        for (int j = 0; j < picture.width(); j++)
            //for (int i = 0; i < fb->width*fb->height; i++)
        {
            assert(picture.Y()[i][j] == 0);
        }

    std::cout << "tests completed" << std::endl;

    return 0;
}

int runTests() {
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
