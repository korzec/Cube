/* 
 * File:   Decoder.h
 * Author: korzec
 *
 * Created on August 19, 2011, 7:48 PM
 */

#ifndef DECODER_H
#define	DECODER_H

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

///posible states of the decoder and encoder after encoding iteration
enum BufferState
{
    PICTURE_AVAILABLE, NEED_BUFFER, END_OF_SEQUENCE, INVALID,
    OUTPUT_AVAILABLE
};


class Decoder
{
protected:
    Parameters params;
    PictureBuffer pictureOutputBuffer;
    CoeffCube coeffCube;
    int pictureNumber;
    int cubeNumber;
    //std::deque<Packet> packetList[3];
    PacketMap allPackets;
    CompressorPtr compressor;
    ///decompres the packets and place into the cube array
    bool DecompressAll();
    ///initialize the cube buffer with #params
    bool Init();
public:
    Decoder();
    /// outputs transformed pictures;
    CoeffCube GetCoeffCube();
    /// decodes the coeffcube
    BufferState Decode();
    ///returns a copy of parameters used by codec
    Parameters GetParams() const;
    //TODO: return next picture in the sequence
    Picture GetNextDecodedPicture();
    ///returns decoded GOP
    PictureVectorPtr GetDecodedGOP();
    ///removes currently available GOP
    bool DeleteOldOutputGOP();
    ///read packets from stream
    bool ReadCube(std::istream* stream);
    ///read file header
    bool ReadSequenceHeader(std::istream* stream);
private:

};

#endif	/* DECODER_H */

