/*
 * cube_encoder.h
 *
 *  Created on: Jul 10, 2011
 *      Author: korzec
 */

#ifndef CUBE_ENCODER_H_
#define CUBE_ENCODER_H_

#include "Decoder.h"

/// Main encoder class: takes pictures to a buffer and returns packets
class Encoder : public Decoder 
{
protected:
    PictureBuffer pictureInputBuffer;
    ///compresses the subcubes and stores them in a #packetList
    //bool CompressSubcubes(Channel);
    ///compress all subcubes and put in #allPackets
    bool CompressAll();
public:
    Encoder();
    /// Load next Picture to the buffer return true if success
    bool LoadNextPicture(Picture &picture);
    /// encodes pictures if enough pictures loaded into PcitureCube
    BufferState Encode();
    //int DecodedFrameAvailable();
    //int GetFrameBufferSize();
    ///check if encoder output buffer is ready
    //EncoderState OutputState();
    //finish encoding - no more pictures to encode
    bool EndOfSequence();
    ///set encoding parameters
    bool SetParams(Parameters params);
    //output currently coded cube to the stream
    bool WriteCubeData(std::ostream*);
    ///write sequence header
    bool WriteSequenceHeader(std::ostream* stream);
};

#endif /* CUBE_ENCODER_H_ */
