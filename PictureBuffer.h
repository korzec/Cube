/* 
 * File:   PictureBuffer.h
 * Author: korzec
 *
 * Created on July 17, 2011, 3:30 PM
 */

#ifndef PICTUREBUFFER_H
#define	PICTUREBUFFER_H

#include "types.h"
#include <vector>

class PictureBuffer
{
    size_t maxSize;
    PictureVector pictures;
public:
    /// initializes buffer with max size
    PictureBuffer(int);
    ///adds picture to the buffer
    bool Add(Picture&);
    ///removes oldest picture
    bool RemoveOldest();
    ///outputs current buffer size
    int GetCount();
    bool isNotFull();
    bool GetGOP(size_t, PictureVector&);
    ///returns false if buffer is smaller than size
    bool RemoveOldGOP(size_t);
};


#endif	/* PICTUREBUFFER_H */

