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
#include "cube_io.h"
#include <string>
#include <cstring>

#include "tests.h"
//#define cimg_display 2
//#include "cimg/CImg.h"

static void display_help()
{
    cout << "\nCube wavelet video coder.";
    cout << "\n";
    cout << "\nusage: program -width x -height y inputfile" ;
    cout << "\nwidth             ulong   -        Width of frame";
    cout << "\nheight            ulong   -        Length of frame";
    cout << endl;
}
bool parse_command_line(CodingParams& params, int argc, char **argv);

int main(int argc, char* argv[])
{

    runTests();
    //return 0;

    puts("Cube codec welcomes");

    string input, output;

    Encoder encoder;
    CodingParams params;

    if (!parse_command_line(params, argc, argv))
        return EXIT_FAILURE;
    encoder.SetParams(params);

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

    std::cout << "w " << encoder.GetParams().width << "h " << encoder.GetParams().height << std::endl;

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
    do
    {
         picture = ReadPicture(inputPicture,
                           encoder.GetParams().width, 
                           encoder.GetParams().height);
         //handle a new picture read
         if(picture.isValid())
         {
             picture.pictureNumber = frameNumber;
             bool ret = encoder.LoadNextPicture(picture);
             if(ret == false)
             {
                 std::cout << "failed to load picture to the encoder" << std::endl;
                 return EXIT_FAILURE;
             }
             frameNumber++;
         }
         else
         {
             std::cout << "invalid picture read" << std::endl;
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
                 gop = encoder.GetDecodedGOP();
                 for(size_t i=0; i<gop->size(); i++ )
                 {
                     WritePicture(*outputPicture, gop->at(i));
                 }
                 encoder.DeleteOldOutputGOP();
                 break;
             case NEED_BUFFER:
                 ///if need more pictures to continue encoding
                 break;
             case END_OF_SEQUENCE:
                 ///if encoder finished coding a sequence
                 //write out the rest of the buffer and stop the loop
                 go = false;
                 break;
             case INVALID:
                 ///if encoder stopped with an exception
                 return EXIT_FAILURE;
                 break;
             default:
                 std::cout << "Unknown state reported by encoder" << std::endl;
                 break;
                 
                 /*! TODO: @todo <<<<<<<<<<<< FIXME XXX  !*/
                 // FIXME 
// TODO: <<<<<<<<<<<<<<<<<<<<<<< @todo kolega   
//PENDING crazy
             }
         }while(state == PICTURE_AVAILABLE);
         
    } while(go);


    inputPicture.close();
    outputPicture->close();

    std::cout << "finished everyting" << std::endl;
    return EXIT_SUCCESS;
}

bool parse_command_line(CodingParams& params, int argc, char **argv)
{
    /**********  command line parameter parsing*********/

    // An array indicating whether a parameter has been parsed
    bool* parsed = new bool[argc];

    // Program name has been parsed
    parsed[0] = true;

    // No other parameters
    for (int i = 1; i < argc; ++i)
        parsed[i] = false;

    // The start and end-points of the parts of the file to be coded
    // (end_pos set to -1 means code to the end)

    //Now do the options
    // initialise the CodingParams
    //now go over again and override video format presets with other values
    for (int i = 1; i < argc;)
    {
        if (strcmp(argv[i], "-width") == 0)
        {
            parsed[i] = true;
            i++;
            params.width =
                    strtoul(argv[i], NULL, 10);
            parsed[i] = true;
        }
        else if (strcmp(argv[i], "-height") == 0)
        {
            parsed[i] = true;
            i++;
            params.height =
                    strtoul(argv[i], NULL, 10);
            parsed[i] = true;
        }
        i++;
    }

    for (int i = 0; i < argc;)
    {
        if (strcmp(argv[i], "-verbose") == 0)
        {
            parsed[i] = true;
            params.verbose = true;
        }
        else if (strcmp(argv[i], "-local") == 0)
        {
            parsed[i] = true;
            params.nolocal = false;
        }
        else if (strcmp(argv[i], "-start") == 0)
        {
            parsed[i] = true;
            i++;
            params.start_pos = strtoul(argv[i], NULL, 10);
            parsed[i] = true;
        }
        else if (strcmp(argv[i], "-stop") == 0)
        {
            parsed[i] = true;
            i++;
            params.end_pos = strtoul(argv[i], NULL, 10);
            parsed[i] = true;
        }
        i++;
    }//opt

    // check we have parsed everything
    bool all_parsed = true;
    for (int i = 0; i < argc - 2; ++i)
    {
        if (!parsed[i])
        {
            all_parsed = false;
            std::cerr << std::endl << "Unknown option " << argv[i];
        }
    }
    if (!all_parsed)
    {
        display_help();
        return false;
    }

    /* check that we have been suplied with input and output files */
    if (argc < 2 || parsed[argc - 2] || parsed[argc - 1])
    {
        display_help();
        std::cerr << std::endl << "Insufficient arguments" << std::endl;
        return false;
    }


    delete[] parsed;

    return true;
}

