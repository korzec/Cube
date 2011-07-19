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
/// Main encoder class

class Encoder {
private:
    CodingParams params;
    PictureBuffer pictureBuffer;
    CoeffCube coeffCube;
    
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

    CodingParams GetParams() const;
    void SetParams(CodingParams params);

};

#endif /* CUBE_ENCODER_H_ */
