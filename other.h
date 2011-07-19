/* 
 * File:   other.h
 * Author: korzec
 *
 * Created on July 18, 2011, 7:04 PM
 */

#ifndef OTHER_H
#define	OTHER_H

///implementation of Picture class with manually programmed reference counting
class PictureCount
{
public:
    ValueArray2Dref* arrayY;
    //ValueArray2D U;
    //ValueArray2D V;
    //boost::shared_ptr<FrameBuffer> frame;
    FrameBuffer* frame;
    int pictureNumber;

    int width()
    {
        if (!frame)
            return 0;

        return frame->width;
        //return Y().shape()[0];
    }

    int height()
    {
        if (!frame)
            return 0;
        return frame->height;
        //return Y().shape()[1];
    }

    ValueArray2Dref& Y()
    {
        return *arrayY;
    }

    PictureCount& operator=(const PictureCount &rhs)
    {
        // Check for self-assignment!
        if (this == &rhs) // Same object?
            return *this; // Yes, so skip assignment, and just return *this.

        pictureNumber = rhs.pictureNumber;
        if (frame)
            frame->refCount--;
        frame = rhs.frame;
        if (frame)
            frame->refCount++;
        arrayY = rhs.arrayY;

        return *this;
    }

    PictureCount(const PictureCount& orig)
    {
        pictureNumber = orig.pictureNumber;
        arrayY = orig.arrayY;
        frame = orig.frame;
        frame->refCount++;
    }

    PictureCount() : frame(NULL)
    {
        //Y(NULL, boost::extents[0][0]);
        arrayY = new ValueArray2Dref(NULL, boost::extents[0][0]);
    }

    PictureCount(FrameBuffer* _frame)
    {
        //frame = boost::shared_ptr<FrameBuffer > (_frame);

        frame = _frame;
        ///dereferencing external pointer maybe produce problems with bad usage
        if (!frame || !(frame->data))
            return;
        arrayY = new ValueArray2Dref(frame->buf[0],
                                     boost::extents[frame->height][frame->width]);
        frame->refCount++;
    }

    PictureCount(int width, int height)
    {
        frame = new FrameBuffer(width, height);
        arrayY = new ValueArray2Dref(frame->buf[0],
                                     boost::extents[frame->height][frame->width]);
        frame->refCount++;
    }

    virtual ~PictureCount()
    {
        //delate data if its the only owner
        if (frame)
        {

            frame->refCount--;
            if (frame->refCount == 0)
            {
                //deleting external memory
                delete frame;
                delete arrayY;
            }

        }
        else //delete mapping if thers no data;
            delete arrayY;


    }
};

#endif	/* OTHER_H */

