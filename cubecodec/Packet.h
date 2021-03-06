/* 
 * File:   Packet.h
 * Author: korzec
 *
 * Created on August 12, 2011, 7:40 PM
 */

#ifndef PACKET_H
#define	PACKET_H

#include "types.h"
#include "Subcube.h"
#include "cubeHeaders.h"

//
class Packet;
typedef boost::shared_ptr<Packet> PacketPointer;

///Stores compressed Subcube data
class Packet
{
public:
    Packet();
public:
    PacketHeader header;
    ucharPtr compressedData;
//    int compressedSize;
//    int fullSize;
//    Coords3D location;
//    Channel channel;
//    int cubeNumer;
   // char headerCode = PACKETHEADERCODE;
};
#endif	/* PACKET_H */

