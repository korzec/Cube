/* 
 * File:   cube_codec.h
 * Author: korzec
 *
 * Created on August 19, 2011, 11:20 PM
 */

#ifndef CUBE_CODEC_H
#define	CUBE_CODEC_H

#include "../cubecodec/Parameters.h"

int cube_decode(Parameters params, std::string input, std::string output);
int cube_encode(Parameters params, std::string input, std::string output);
void display_help();
bool parse_command_line(Parameters& params, int argc, char **argv);

#endif	/* CUBE_CODEC_H */

