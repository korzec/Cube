

#include "cube_io.h"
#include "types.h"
#include "Encoder.h"
#include "PictureBuffer.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cassert>

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
    
}

int testVectorPicture()
{
    PictureVector* v;
    v = new PictureVector;
    Picture pic(4,4);
    
    v->assign(2,pic);
    
    delete v;
    
    int i;
}

int testPictureRefCount()
{
    Picture pic3(33,33);
    Picture* p4 = new Picture(pic3);
    assert(p4->frame == pic3.frame);
    delete p4;
    assert(pic3.frame->refCount == 1);
    
    Picture pic(6,6);
    assert( pic.frame->refCount == 1);
    //copy few times;
    
    PictureVector gop;
    //make 3 copies;
    gop.assign(3,pic);
    assert(gop[0].frame == pic.frame);
    assert(gop[1].frame == pic.frame);
    assert(gop[2].frame == pic.frame);
    
    assert(pic.frame->refCount == 4);
    
    //copy a pic;
    Picture pic2(pic);
    
    pic2 = pic;
    assert(pic.frame == pic2.frame);
    assert(pic.frame->refCount == 5);
    assert(pic2.frame->refCount == 5);
       
    gop[2] = Picture(5,5);
    assert(pic.frame->refCount ==4);
            
    assert(gop[0].frame == pic.frame);
    assert(gop[1].frame == pic.frame);
    assert(gop[2].frame->refCount == 1);
    
    gop.erase(gop.begin());
    assert(pic.frame->refCount == 3);
   
    assert(gop.size() == 2);
    
    Picture* ptr[2];
    ptr[0] = &gop[0];
    ptr[1] = &gop[1];
    //ptr[2] = &gop[2];
    
    int a;
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
    assert(cube.Y()[0][0][0] == gop[0].Y()[0][0]);
    
    //validate values;
    for (int d = 0; d < dims.depth; d++)
        {
            for (int h = 0; h < dims.height; h++)
            {
                for (int w = 0; w < dims.width; w++)
                {
                    assert(cube.Y()[d][h][w] == (d+h+w)%255);
                }
            }
        }
    
    
    
    
    std::cout << "loadGOP tested" <<std::endl;
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
    testGetGOP();
    testVectorPicture();
    //testPictureRefCount();
    testLoadGOP();
    testOutput();
    testTypesConctructors();
    testFrameBufferIO();
    testPictureIO();
    std::cout << "********** all tests finished" << std::endl;
    return 0;
}
