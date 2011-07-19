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

#include "tests.h"

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

    Picture picture = ReadPicture(inputPicture,
                                  encoder.GetParams().width, encoder.GetParams().height);

    std::cout << "Picture read" << std::endl;


//TODO: loop loading a picture and checking the state;

    
    // open the decoded ouput file
    std::ofstream *outputPicture = NULL;

    if (encoder.GetParams().nolocal == false)
    {
        std::string outputPictureName = output + ".localdec.yuv";
        outputPicture = new std::ofstream(outputPictureName.c_str(), std::ios::out | std::ios::binary);

    }

    std::cout << "result: " << WritePicture(*outputPicture, picture) << std::endl;
    outputPicture->close();

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

    //memset (&enc_ctx, 0, sizeof(dirac_encoder_context_t));
    //dirac_encoder_presets_t preset = VIDEO_FORMAT_CUSTOM;
    //Now do the options
    // initialise the encoder context
    //dirac_encoder_context_init (&enc_ctx, preset);

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

