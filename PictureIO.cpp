/* 
 * File:   PictureIO.cpp
 * Author: korzec
 * 
 * Created on August 12, 2011, 7:16 PM
 */

#include "PictureIO.h"

//PictureIO::PictureIO()
//{
//}
//
bool PictureIO::WritePictureData(std::ofstream &fdata, FrameBuffer* frame)
{
    FrameBuffer* fbuf = frame;
    bool ret_stat = true;

    if (fbuf->data)
    {
        std::ios::iostate oldExceptions = fdata.exceptions();
        fdata.exceptions(std::ios::failbit | std::ios::badbit);
        try {
            assert(fbuf->buf[0] != 0);
            fdata.write((char *) fbuf->buf[0], fbuf->SizeY());
            assert(fbuf->buf[1] != 0);
            assert(fbuf->buf[2] != 0);
            fdata.write((char *) fbuf->buf[1], fbuf->SizeU());
            fdata.write((char *) fbuf->buf[2], fbuf->SizeU());
        } catch (...) {
            std::cout << "Incomplete frame " << std::endl;
            ret_stat = false;
        }
        fdata.exceptions(oldExceptions);
    }
    return ret_stat;
}

bool PictureIO::WritePicture(std::ofstream &fdata, Picture picture)
{
	return WritePictureData(fdata, picture.frame.get());
}

/// reads a picture from input stream and outputs a pointer to @FrameBuffer
FrameBuffer* PictureIO::ReadPictureData(std::ifstream &fdata, int width, int height)
{
    FrameBuffer* fb = new FrameBuffer(width, height);
    std::ios::iostate oldExceptions = fdata.exceptions();
    fdata.exceptions(std::ios::failbit | std::ios::badbit);
    try {
        fdata.read((char *) fb->data, fb->Size());
    } catch (...) {
        delete fb;
        fb = NULL;
        std::cout << "file ended or reading error " << std::endl;
    }
    fdata.exceptions(oldExceptions);
    return fb;
}

Picture PictureIO::ReadPicture(std::ifstream &fdata, int width, int height)
{
	FrameBuffer * frame = ReadPictureData(fdata, width, height);
	Picture picture(frame);
	return picture;
}