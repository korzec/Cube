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
#include <map>
#include "CubeStream.h"

typedef std::multimap<float, Packet> PacketMap;
typedef std::pair<float, Packet> PacketPair;

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
    PacketMap allPackets;
    Compressor compressor;
    ///compresses the subcubes and stores them in a #packetList
    bool CompressSubcubes(Channel);
    ///compress all subcubes and put in #allPackets
    bool CompressAll();
    
    //decompres the packets and place into the cube array
    bool DecompressAll();
    
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
    bool SetParams(Parameters params);
    
    Picture GetNextDecodedPicture();
    
    PictureVectorPtr GetDecodedGOP();
    
    bool DeleteOldOutputGOP();

    //output currently coded cube to the stream
    bool OutputCube(std::ostream*);
    
    bool OutputSequenceHeader(std::ostream* stream);
    
    //read packets from stream
    bool ReadCube(std::istream* stream);
    
    //read file header
    bool ReadSequenceHeader(std::istream* stream);
};

#endif /* CUBE_ENCODER_H_ */
