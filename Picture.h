/* 
 * File:   Picture.h
 * Author: korzec
 *
 * Created on August 12, 2011, 8:17 PM
 */

#ifndef PICTURE_H
#define	PICTURE_H
#include "types.h"

class Picture;
//STL and BOOST containers for Picture
typedef std::vector<Picture> PictureVector;
typedef boost::shared_ptr<PictureVector> PictureVectorPtr;

///wrapper class for frame data with automatic memory management
class Picture
{
public:
    ValueArray2DrefPtr array[3];
    FrameBufferPtr frame;
    int pictureNumber;
public:
    int width();
    int height();
    int chromaWidth();
    int chromaHeight();

    ValueArray2Dref& Array(Channel);

    bool isValid();

    Picture();

    Picture(FrameBuffer* _frame);

    Picture(int width, int height);
};

#endif	/* PICTURE_H */

