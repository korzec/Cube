//============================================================================
// Name        : cube-codec.cpp
// Author      : Konrad Korzec
// Version     :
// Copyright   : 
// Description : Hello World in C, Ansi-style
//============================================================================

//#define VERSION 0.1
#include "types.h"
#include "Encoder.h"

#include <stdio.h>
#include <stdlib.h>
#include "PictureIO.h"
#include <string>
#include <cstring>

#include "tests.h"
//#define cimg_display 2
//#include "cimg/CImg.h"
#include "parse_cmd.h"

using namespace std;

int main(int argc, char* argv[])
{

    runTests();
    //return 0;

    puts("Cube codec welcomes");

    string input, output;

    Encoder encoder;
    Parameters params;

    if (!parse_command_line(params, argc, argv))
        return EXIT_FAILURE;
    
    
    params.codecParams.subcubeSize.width = 60;
    params.codecParams.subcubeSize.height = 32;
    params.codecParams.subcubeSize.depth = 4;
    
    //load params and check if they were correct
    if( ! encoder.SetParams(params))
    {
        std::cout << "some parameters were wrong" << std::endl;
        return EXIT_FAILURE;
    }

    if (argc < 2)
    {
        display_help();
        exit(1);
    }

    // last two arguments must be file names
    if (argv[argc - 1][0] == '-')
    {
        display_help();
        exit(1);
    }
    else
        output = argv[argc - 1];

    if (argv[argc - 2][0] == '-')
        input = "/dev/stdin";
    else
        input = argv[argc - 2];

    //check we have real inputs
    if ((input.length() == 0) || (output.length() == 0))
    {
        display_help();
        exit(1);
    }

    std::cout << "Params read" << std::endl;

    std::ifstream
    inputPicture(input.c_str(), std::ios::in | std::ios::binary);
    if (!inputPicture)
    {
        std::cerr << std::endl <<
                "Can't open input data file: " << input << std::endl;
        return EXIT_FAILURE;
    }
    else
        cout << "opened file " << input << std::endl;

    std::cout << "w " << encoder.GetParams().codecParams.cubeSize.width << " h " << encoder.GetParams().codecParams.cubeSize.height << std::endl;

    //open file for writing
    std::ofstream* codedFile = new std::ofstream(output.c_str(), std::ios::out | std::ios::binary);
    
    /// open the decoded output file
    std::ofstream *outputPicture = NULL;

    if (encoder.GetParams().nolocal == false)
    {
        std::string outputPictureName = output + ".localdec.yuv";
        outputPicture = new std::ofstream(outputPictureName.c_str(), std::ios::out | std::ios::binary);

    }

    //std::cout << "result: " << WritePicture(*outputPicture, picture) << std::endl;
   
    Picture picture;
    int frameNumber = 0;
    bool go = true;
    EncoderState state;
    
    //write a file header
    encoder.OutputSequenceHeader(codedFile);
    
    //skip frames
    for (int i=0; i<params.start_pos; ++i)
    {
        PictureIO::ReadPicture(inputPicture,
                           encoder.GetParams().codecParams.cubeSize.width, 
                           encoder.GetParams().codecParams.cubeSize.height);
    }
    
    do
    {
         picture = PictureIO::ReadPicture(inputPicture,
                           encoder.GetParams().codecParams.cubeSize.width, 
                           encoder.GetParams().codecParams.cubeSize.height);
         //handle a new picture read
         if( frameNumber <= (params.end_pos - params.start_pos) &&
                 picture.isValid())
         {
             picture.pictureNumber = frameNumber;
             bool ret = encoder.LoadNextPicture(picture);
             if(ret == false)
             {
                 std::cout << "failed to load picture to the encoder" << std::endl;
                 return EXIT_FAILURE;
             }
             frameNumber++;
             std::cout << "frame: " << frameNumber << std::endl; 
             
         }
         else
         {
             std::cout << "no more pictures to read" << std::endl;
             encoder.EndOfSequence();
             break;
         }
         
         do
         {
             //should encode 1 picture at a time
             state  = encoder.Encode();
             PictureVectorPtr gop;
             switch (state)
             {
             case OUTPUT_AVAILABLE:
                 ///if encoded data is available
                 ///write out the buffer and continue
                 break;
             case PICTURE_AVAILABLE:
                 ///if decoded picture is available
                 ///write output picture and continue
                 
                 //lets output the coded data
                 encoder.OutputCube(codedFile);            
                 
                 gop = encoder.GetDecodedGOP();
                 if(!params.nolocal)
                     for(size_t i=0; i<gop->size(); i++ )
                     {
                         PictureIO::WritePicture(*outputPicture, gop->at(i));
                     }
                 encoder.DeleteOldOutputGOP();
                 break;
             case NEED_BUFFER:
                 ///if need more pictures to continue encoding
                 break;
             case END_OF_SEQUENCE:
                 //TODO: handle EOS
                 ///if encoder finished coding a sequence
                 //write out the rest of the buffer and stop the loop
                 go = false;
                 break;
             case INVALID:
                 ///if encoder stopped with an exception
                 //return EXIT_FAILURE;
                 go = false;
                 break;
             default:
                 std::cout << "Unknown state reported by encoder" << std::endl;
                 break;
                 
             }
         }while(state == PICTURE_AVAILABLE);
         
    } while(go);

    
    //AFTER ALL JUST READ THE FILE BACK
    
    
    
    
    

    inputPicture.close();
    if(codedFile)
        codedFile->close();
    if(outputPicture)
            outputPicture->close();

    std::cout << "finished everyting" << std::endl;
    return EXIT_SUCCESS;
}


