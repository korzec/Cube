/* 
 * File:   parse_cmd.h
 * Author: korzec
 *
 * Created on July 30, 2011, 5:57 PM
 */

#ifndef PARSE_CMD_H
#define	PARSE_CMD_H

#include "../cubecodec/types.h"
#include "../cubecodec/Parameters.h"
#include <iostream>

/// displays a help message
void display_help()
{
    std::cout << "\nCube wavelet video coder.";
    std::cout << "\n";
    std::cout << "\nusage: program -width x -height y inputfile" ;
    std::cout << "\nwidth             ulong   -   Width of frame";
    std::cout << "\nheight            ulong   -   Length of frame";
    std::cout << "\ndepth             ulong   -   Depth of a cube";
    std::cout << "\nlevels            short   -   max levels of wavelet transform";
    std::cout << "\nverbose                   -   turns on diagnosting messages";
    std::cout << "\nlocal                     -   local decoding output form encoder";
    std::cout << "\nanalysis                  -   write transformed cubes to files";
    std::cout << "\nstart             ulong   -   starting frame";
    std::cout << "\nstop              ulong   -   last frame to encode";
    std::cout << std::endl;
}
///parses command line options and sets parameters for use with Encoder
bool parse_command_line(Parameters& params, int argc, char **argv)
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
    // initialise the parameters
    //now go over again and override video format presets with other values
    for (int i = 1; i < argc;)
    {
        if (strcmp(argv[i], "-width") == 0)
        {
            parsed[i] = true;
            i++;
            params.codecParams.cubeSize.width =
                    strtoul(argv[i], NULL, 10);
            parsed[i] = true;
        }
        else if (strcmp(argv[i], "-height") == 0)
        {
            parsed[i] = true;
            i++;
            params.codecParams.cubeSize.height =
                    strtoul(argv[i], NULL, 10);
            parsed[i] = true;
        }
        else if (strcmp(argv[i], "-depth") == 0)
        {
            parsed[i] = true;
            i++;
            params.codecParams.cubeSize.depth =
                    strtoul(argv[i], NULL, 10);
            parsed[i] = true;
        }
        else if (strcmp(argv[i], "-sw") == 0)
        {
            parsed[i] = true;
            i++;
            params.codecParams.subcubeSize.width =
                    strtoul(argv[i], NULL, 10);
            parsed[i] = true;
        }
        else if (strcmp(argv[i], "-sh") == 0)
        {
            parsed[i] = true;
            i++;
            params.codecParams.subcubeSize.height =
                    strtoul(argv[i], NULL, 10);
            parsed[i] = true;
        }
        else if (strcmp(argv[i], "-sd") == 0)
        {
            parsed[i] = true;
            i++;
            params.codecParams.subcubeSize.depth =
                    strtoul(argv[i], NULL, 10);
            parsed[i] = true;
        }
        i++;
    }

    for (int i = 0; i < argc;)
    {
        if (strcmp(argv[i], "-decode") == 0)
        {
            parsed[i] = true;
            params.decode = true;
        }       
        else if (strcmp(argv[i], "-compressor") == 0)
        {
            parsed[i] = true;
            i++;
            std::cout << "USING COMPRESSOR: ";
            //sompare strings
            if( strcmp(argv[i], "huffman") == 0)
                params.codecParams.compression = Huffman,
                        std::cout << "huffman coder" << std::endl;
            else if( strcmp(argv[i], "lzo") == 0)
                params.codecParams.compression = LZO,
                        std::cout << "LZO" << std::endl;
            else if( strcmp(argv[i], "ac") == 0)
                params.codecParams.compression = AC,
                        std::cout << "arithmetic coding of bitplanes" << std::endl;
            else if( strcmp(argv[i], "copy") == 0)
                params.codecParams.compression = Copy,
                        std::cout << "no compression - just copy" << std::endl;
            else
                std::cout << "default" << std::endl;
            parsed[i] = true;
        }
        else if (strcmp(argv[i], "-skip") == 0)
        {
            parsed[i] = true;
            i++;
            params.skipRatio = strtof(argv[i], NULL);
            parsed[i] = true;
        }
        else if (strcmp(argv[i], "-verbose") == 0)
        {
            parsed[i] = true;
            params.verbose = true;
        }
        else if (strcmp(argv[i], "-analysis") == 0)
        {
            parsed[i] = true;
            params.analysis = true;
        }        
        else if (strcmp(argv[i], "-analysis2") == 0)
        {
            parsed[i] = true;
            params.analysis2 = true;
        }        
        else if (strcmp(argv[i], "-stats") == 0)
        {
            parsed[i] = true;
            params.stats = true;
        }        
        else if (strcmp(argv[i], "-levels") == 0)
        {
            parsed[i] = true;
            i++;
            params.codecParams.levels = strtoul(argv[i], NULL, 10);
            parsed[i] = true;
        }        
        else if (strcmp(argv[i], "-local") == 0)
        {
            parsed[i] = true;
            params.nolocal = false;
        }
        else if (strcmp(argv[i], "-dumpcubes") == 0)
        {
            parsed[i] = true;
            params.dumpCubes = true;
        }
        else if (strcmp(argv[i], "-nofile") == 0)
        {
            parsed[i] = true;
            params.nofile = true;
        }
        else if (strcmp(argv[i], "-test") == 0)
        {
            parsed[i] = true;
            params.test = true;
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


#endif	/* PARSE_CMD_H */

