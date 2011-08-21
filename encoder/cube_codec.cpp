//============================================================================
// Name        : cube_codec.cpp
// Author      : Konrad Korzec
// Version     :
// Copyright   : 
// Description : Encoder executable
//============================================================================

//#define VERSION 0.1
#include "../cubecodec/types.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <iostream>

#include "tests.h"
//#define cimg_display 2
//#include "cimg/CImg.h"
#include "parse_cmd.h"
#include "cube_codec.h"

using namespace std;

int main(int argc, char* argv[])
{
    puts("Cube codec welcomes");

    string input, output;

    Parameters params;

    if (!parse_command_line(params, argc, argv))
        return EXIT_FAILURE;

    if(!params.notest)
        runTests();   
    
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

    if(params.decode)
        cube_decode(params, input, output);
    else
        cube_encode(params, input, output);

    std::cout << "finished everyting" << std::endl;
    return EXIT_SUCCESS;
}


