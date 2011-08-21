/* 
 * File:   PictureIO.h
 * Author: korzec
 *
 * Created on August 12, 2011, 7:16 PM
 */

#ifndef PICTUREIO_H
#define	PICTUREIO_H

#include "types.h"
#include "Picture.h"
#include <iostream>
#include <fstream>
#include <cassert>

class PictureIO
{
public:
    /// writes data from FrameBuffer* to a file
    static bool WritePictureData(std::ofstream &fdata, FrameBuffer* picture);
    /// writes a Picture to a file
    static bool WritePicture(std::ofstream &fdata, Picture picture);
    /// reads a frame from input stream and returns a pointer to a FrameBuffer
    static FrameBuffer* ReadPictureData(std::ifstream &fdata, int width, int height);
    /// reads a frame from file and returns Picture
    static Picture ReadPicture(std::ifstream &fdata, int width, int height);

private:

};

#endif	/* PICTUREIO_H */

