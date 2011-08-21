/* 
 * File:   cube_codec.h
 * Author: korzec
 *
 * Created on August 19, 2011, 11:20 PM
 */

#ifndef CUBE_CODEC_H
#define	CUBE_CODEC_H

int cube_decode(Parameters params, std::string input, std::string output);
int cube_encode(Parameters params, std::string input, std::string output);

#endif	/* CUBE_CODEC_H */

