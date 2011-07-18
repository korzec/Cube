/*
 * cube_io.h
 *
 *  Created on: Jul 11, 2011
 *      Author: korzec
 */

#ifndef CUBE_IO_H_
#define CUBE_IO_H_

#include "types.h"

//#include <time.h>
#include <iostream>
//#include <limits>
#include <fstream>
//#include <set>
//#include <cmath>
//#include <ctime>
#include <cassert>
//#include <string>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <fcntl.h>
//#include <cstdlib>
//#include <cstring>
//#include <climits>

//namespace CubeIO
//{
using namespace std;

bool WritePictureData(std::ofstream &fdata, FrameBuffer* picture);

bool WritePicture(std::ofstream &fdata, Picture picture);

/// reads a picture from input stream and outputs a pointer to @FrameBuffer
FrameBuffer* ReadPictureData(std::ifstream &fdata, int width, int height);

Picture ReadPicture(std::ifstream &fdata, int width, int height);

#endif

