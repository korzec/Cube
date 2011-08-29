/* 
 * File:   MQcoder.h
 * Author: korzec
 *
 * Created on August 26, 2011, 7:12 PM
 */

#ifndef MQCODER_H
#define	MQCODER_H

#include "BitStream.h"

//implements MQ-coder as of JBIG2 standard
namespace MQcoder
{
struct QeTable
{
#define INDEXCOUNT 47
static const unsigned char NLPS[INDEXCOUNT];
static const unsigned char NMPS[INDEXCOUNT];
static const unsigned char SWITCH[INDEXCOUNT];
static const unsigned short Qe[INDEXCOUNT];    
};

struct CONTEXT
{
    unsigned char I;
    unsigned char MPS;
};

class MQencoder
{
    BitStream* input;
    BitStream* output;
    int codedBytes;
    
    unsigned int C;
    unsigned int A;
    int CT;
    CONTEXT CX;
    unsigned char D;
    unsigned char *BP;
    unsigned char *BPST;
    
    const unsigned char* NLPS;
    const unsigned char* NMPS;
    const unsigned char* SWITCH;
    const unsigned short* Qe;
public:
    //set input Bitstream and output buffer
    MQencoder(BitStream& input, BitStream& output );
    //returns number of bytes written to coding buffer
    int GetCodedBytes();
    bool Encode();
    bool Continue(BitStream& in);
private:
    void ENCODER();
    void INITENC();
    void ENCODE();
    void FLUSH();
    void CODE1();
    void CODE0();
    void CODELPS();
    void CODEMPS();
    void RENORME();
    void BYTEOUT();
    void SETBITS();
};    

class MQdecoder
{
    BitStream* input;
    BitStream* output;
    unsigned int outputSize;
    int codedBytes;
    
    unsigned int C;
    unsigned short& Clow;
    unsigned short& Chigh;
    int A;
    int CT;
    CONTEXT CX;
    unsigned char D;
    unsigned char *BP;
    unsigned char *BPST;
    
    const unsigned char* NLPS;
    const unsigned char* NMPS;
    const unsigned char* SWITCH;
    const unsigned short* Qe;
public:
    MQdecoder(BitStream& input, BitStream& output, unsigned int outSize /* = 0 */);
    ///continues decoding from the same compressed stream into the new output stream
    bool Continue(BitStream& output, unsigned int outSize);
    bool Decode();
private:
    void DECODER();
    void INITDEC();
    unsigned char DECODE();
    unsigned char MPS_EXCHANGE();
    unsigned char LPS_EXCHANGE();
    void RENORMD();
    void BYTEIN();
};
}


#endif	/* MQCODER_H */

