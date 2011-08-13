/*
 * cube_encoder.h
 *
 *  Created on: Jul 10, 2011
 *      Author: korzec
 */

#ifndef CUBE_ENCODER_H_
#define CUBE_ENCODER_H_

#include "types.h"
#include "PictureBuffer.h"
#include "CoeffCube.h"
#include "Packet.h"
#include "Compressor.h"
#include <deque>

/// Main encoder class: takes pictures to a buffer and returns packets
class Encoder {
private:
    Parameters params;
    PictureBuffer pictureBuffer;
    PictureBuffer pictureOutputBuffer;
    CoeffCube coeffCube;
    int pictureNumber;
    int cubeNumber;
    std::deque<Packet> packetList[3];
    Compressor compressor;
    ///compresses the subcubes and stores them in a list
    bool CompressSubcubes(Channel);
    
public:

    Encoder();
    /// Load next Picture to the buffer return true if success
    bool LoadNextPicture(Picture &picture);
    /// encodes pictures if enough pictures loaded into PcitureCube
    EncoderState Encode();
    /// outputs transformed pictures;
    CoeffCube GetCoeffCube();
    /// decodes the coeffcube
    void Decode();

    int DecodedFrameAvailable();
    int GetFrameBufferSize();
    
    ///check if encoder output buffer is ready
    EncoderState OutputState();
    
    //finish encoding without further frames
    bool EndOfSequence();

    Parameters GetParams() const;
    void SetParams(Parameters params);
    
    Picture GetNextDecodedPicture();
    
    PictureVectorPtr GetDecodedGOP();
    
    bool DeleteOldOutputGOP();

};

#endif /* CUBE_ENCODER_H_ */
