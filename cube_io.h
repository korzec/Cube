/*
 * cube_io.h
 *
 *  Created on: Jul 11, 2011
 *      Author: korzec
 */

#ifndef CUBE_IO_H_
#define CUBE_IO_H_

#include "types.h"

#include <iostream>
#include <fstream>
#include <cassert>
//namespace CubeIO

using namespace std;
/// frites data from FrameBuffer* to a file
bool WritePictureData(std::ofstream &fdata, FrameBuffer* picture);
/// writes a Picture to a file
bool WritePicture(std::ofstream &fdata, Picture picture);
/// reads a frame from input stream and returns a pointer to a FrameBuffer
FrameBuffer* ReadPictureData(std::ifstream &fdata, int width, int height);
/// reads a frame from file and returns Picture
Picture ReadPicture(std::ifstream &fdata, int width, int height);

#endif

