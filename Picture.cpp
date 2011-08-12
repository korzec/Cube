/*
 * File:   Picture.cpp
 * Author: korzec
 *
 * Created on August 12, 2011, 8:17 PM
 */

#include "Picture.h"

int Picture::width()
{
    if (!frame)
        return 0;
    return frame->width;
}

int Picture::height()
{
    if (!frame)
        return 0;
    return frame->height;
}

int Picture::chromaWidth()
{
    if (!frame)
        return 0;
    return frame->width >> 1;
}

int Picture::chromaHeight()
{
    if (!frame)
        return 0;
    return frame->height >> 1;
}

ValueArray2Dref& Picture::Array(Channel channel)
{
    return *array[channel];
}

//ValueArray2Dref& Picture::Y()
//{
//    return *arrayY;
//}
//
//ValueArray2Dref& Picture::U()
//{
//    return *arrayU;
//}
//
//ValueArray2Dref& Picture::V()
//{
//    return *arrayV;
//}

bool Picture::isValid()
{
    if (frame == NULL)
        return false;
    return frame->Size() > 0;
}

Picture::Picture()
{
}

Picture::Picture(FrameBuffer* _frame)
{
    frame = FrameBufferPtr(_frame);
    ///dereferencing external pointer maybe produce problems with bad usage
    if (!frame || !(frame->data))
        return;
    array[Ych] = ValueArray2DrefPtr(new ValueArray2Dref
            (frame->buf[0], boost::extents[frame->height][frame->width]));
    array[Uch] = ValueArray2DrefPtr(new ValueArray2Dref
            (frame->buf[1], boost::extents[frame->height >> 1][frame->width >> 1]));
    array[Vch] = ValueArray2DrefPtr(new ValueArray2Dref
            (frame->buf[2], boost::extents[frame->height >> 1][frame->width >> 1]));
}

Picture::Picture(int width, int height)
{
    frame = FrameBufferPtr(new FrameBuffer(width, height));
    array[Ych] = ValueArray2DrefPtr(new ValueArray2Dref
            (frame->buf[0], boost::extents[frame->height][frame->width]));
    array[Uch] = ValueArray2DrefPtr(new ValueArray2Dref
            (frame->buf[1], boost::extents[frame->height >> 1][frame->width >> 1]));
    array[Vch] = ValueArray2DrefPtr(new ValueArray2Dref
            (frame->buf[2], boost::extents[frame->height >> 1][frame->width >> 1]));

}