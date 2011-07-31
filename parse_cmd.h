/* 
 * File:   parse_cmd.h
 * Author: korzec
 *
 * Created on July 30, 2011, 5:57 PM
 */

#ifndef PARSE_CMD_H
#define	PARSE_CMD_H

#include "types.h"

static void display_help()
{
    std::cout << "\nCube wavelet video coder.";
    std::cout << "\n";
    std::cout << "\nusage: program -width x -height y inputfile" ;
    std::cout << "\nwidth             ulong   -        Width of frame";
    std::cout << "\nheight            ulong   -        Length of frame";
    std::cout << std::endl;
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
        else if (strcmp(argv[i], "-depth") == 0)
        {
            parsed[i] = true;
            i++;
            params.cubeDepth =
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


#endif	/* PARSE_CMD_H */
