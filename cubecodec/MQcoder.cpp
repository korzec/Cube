/* 
 * File:   MQcoder.cpp
 * Author: korzec
 * 
 * Created on August 26, 2011, 7:12 PM
 */

#include <iomanip>

#include "MQcoder.h"
namespace MQcoder
{

MQencoder::MQencoder(BitStream& in, BitStream& out) : input(in), output(out), codedBytes(0)
{
    NLPS = QeTable::NLPS;
    NMPS = QeTable::NMPS;
    SWITCH = QeTable::SWITCH;
    Qe = QeTable::Qe;
    
    CX.I = 0;
    CX.MPS = 0;
    BPST = out.GetSequence().get();
}

int MQencoder::GetCodedBytes()
{
    return codedBytes;
}

void MQencoder::ENCODER()
{
    INITENC();

    //loop until the end of bitstream
    for(unsigned long int i=0;;i++)
    {
    //read CX, D : use just one CX, read D from?
    D = input.GetBitAt(i);
    //CX = CX
    if(D == 2)
        break;
   
#ifdef QMDEBUG
    std::cout 
            << std::setw(4) << std::setfill(' ') << i+1
            << " D: " << (int)D 
            << " I: " << std::setw(2) << std::setfill(' ') <<(int)CX.I
            << " MPS: " << (int)CX.MPS
            << " Qe: " << std::setw(4) << std::setfill(' ') << std::hex << Qe[CX.I] << std::dec
            << " A: " << std::setw(4) << std::setfill(' ') << std::hex << A << std::dec
            << " C: " << std::setw(8) << std::setfill(' ') << std::hex << C << std::dec
            << " CT: " << std::setw(2) << std::setfill(' ') << CT 
            << " B: " << std::setw(2) << std::setfill(' ') << std::hex << (int)*BP << std::dec
            ;
#endif
    
    ENCODE();
    
    }    //if not finished goto read CX, D

    FLUSH();;
}

void MQencoder::INITENC()
{
    A = 0x8000;
    C = 0;
    BP = BPST - 1;
    CT = 12;
}

void MQencoder::ENCODE()
{
    if (D == 0)
        CODE0();
    else
        CODE1();
}

void MQencoder::FLUSH()
{
    SETBITS();
    C <<= CT;
    BYTEOUT();
    C <<= CT;
    BYTEOUT();
    if (*BP != 0xFF)
    {
#ifdef QMDEBUG
        std::cout << " OUT: " << std::setw(2) << std::setfill(' ')<< std::hex << (int)*BP << std::dec;
#endif
        codedBytes++;
        BP += 1;
        *BP = 0xFF;
    }
    //HERE: Optionally remove trailing 0x7FFF pairs following the leading 0xFF
#ifdef QMDEBUG
    std::cout << " OUT: " << std::setw(2) << std::setfill(' ')<< std::hex << (int)*BP << std::dec;
#endif
    codedBytes++;
    BP += 1;
    *BP = 0xAC;
    //codedBytes++;
    BP += 1;
}

void MQencoder::CODE1()
{
    if (CX.MPS == 1)
        CODEMPS();
    else
        CODELPS();
}

void MQencoder::CODE0()
{
    if (CX.MPS == 0)
        CODEMPS();
    else
        CODELPS();
}

void MQencoder::CODELPS()
{
    A -= Qe[CX.I];
    if (A < Qe[CX.I])
        C += Qe[CX.I];
    else
        A = Qe[CX.I];
    if (SWITCH[CX.I] == 1)
        CX.MPS = 1 - CX.MPS;
    CX.I = NLPS[CX.I];
    RENORME();
}

void MQencoder::CODEMPS()
{
    A -= Qe[CX.I];
    if (A < 0x8000)
    {
        if (A < Qe[CX.I])
            A = Qe[CX.I];
        else
            C += Qe[CX.I];
        CX.I = NMPS[CX.I];
        RENORME();
    }
    else
        C += Qe[CX.I];
}

void MQencoder::RENORME()
{
    do
    {
        A <<= 1;
        C <<= 1;
        CT -= 1;
        if (CT == 0)
            BYTEOUT();
    }
    while (A < 0x8000);
}

void MQencoder::BYTEOUT()
{
    if (*BP == 0xFF)
    {
with_carry:
#ifdef QMDEBUG
        std::cout << " OUT: " << std::setw(2) << std::setfill(' ')<< std::hex << (int)*BP << std::dec;
#endif
        codedBytes++;
        BP += 1;
        *BP = C >> 20;
        C &= 0xFFFFF;
        CT = 7;
        return;
    }
    else
    {
        if (C < 0x8000000)
        {
just_byte:
#ifdef QMDEBUG
            std::cout << " OUT: " << std::setw(2) << std::setfill(' ')<< std::hex << (int)*BP << std::dec;
#endif
            codedBytes++;
            BP += 1;
            *BP = C >> 19;
            C &= 0x7FFFF;
            CT = 8;
            return;
        }
        else
        {
            *BP += 1;
            if (*BP == 0xFF)
            {
                C &= 0x7FFFFFF;
                goto with_carry;
            }
            else
                goto just_byte;
        }
    }
}

void MQencoder::SETBITS()
{
    unsigned int TEMPC = C + A;
    C |= 0xFFFF;
    if (C >= TEMPC)
        C -= 0x8000;
}

void MQdecoder::DECODER()
{
    
}
void MQdecoder::INITDEC()
{
    
}
unsigned char MQdecoder::DECODE()
{
    
}
void MQdecoder::MPS_EXCHANGE()
{
    
}
void MQdecoder::LPS_EXCHANGE()
{
    
}
void MQdecoder::RENORMD()
{
    
}
void MQdecoder::BYTEIN(){
    
}

const unsigned char QeTable::NLPS[INDEXCOUNT] = {
    1,
    6,
    9,
    12,
    29,
    33,
    6,
    14,
    14,
    14,
    17,
    18,
    20,
    21,
    14,
    14,
    15,
    16,
    17,
    18,
    19,
    19,
    20,
    21,
    22,
    23,
    24,
    25,
    26,
    27,
    28,
    29,
    30,
    31,
    32,
    33,
    34,
    35,
    36,
    37,
    38,
    39,
    40,
    41,
    42,
    43,
    46
};
const unsigned char QeTable::NMPS[INDEXCOUNT] = {
    1,
    2,
    3,
    4,
    5,
    38,
    7,
    8,
    9,
    10,
    11,
    12,
    13,
    29,
    15,
    16,
    17,
    18,
    19,
    20,
    21,
    22,
    23,
    24,
    25,
    26,
    27,
    28,
    29,
    30,
    31,
    32,
    33,
    34,
    35,
    36,
    37,
    38,
    39,
    40,
    41,
    42,
    43,
    44,
    45,
    45,
    46
};
const unsigned char QeTable::SWITCH[INDEXCOUNT] = {
    1,
    0,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
};
const unsigned short QeTable::Qe[INDEXCOUNT] = {
    0x5601,
    0x3401,
    0x1801,
    0x0AC1,
    0x0521,
    0x0221,
    0x5601,
    0x5401,
    0x4801,
    0x3801,
    0x3001,
    0x2401,
    0x1C01,
    0x1601,
    0x5601,
    0x5401,
    0x5101,
    0x4801,
    0x3801,
    0x3401,
    0x3001,
    0x2801,
    0x2401,
    0x2201,
    0x1C01,
    0x1801,
    0x1601,
    0x1401,
    0x1201,
    0x1101,
    0x0AC1,
    0x09C1,
    0x08A1,
    0x0521,
    0x0441,
    0x02A1,
    0x0221,
    0x0141,
    0x0111,
    0x0085,
    0x0049,
    0x0025,
    0x0015,
    0x0009,
    0x0005,
    0x0001,
    0x5601
};
}