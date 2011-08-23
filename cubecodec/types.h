/*
 * cube_codec.h
 *
 *  Created on: Jul 8, 2011
 *      Author: korzec
 */

#ifndef TYPES_H_
#define TYPES_H_

#define OUTDIR "out/"

///orientation labels for the 3d subbands
enum Orientation
{
    ///order: width, height, depth
    LLL = 0,
    HLL = 1,
    LHL = 2,
    HHL = 3,
    LLH = 4,
    HLH = 5,
    LHH = 6,
    HHH = 7,
};

#define NOFCHANNELS 3
enum Channel
{
    Ych = 0,
    Uch = 1,
    Vch = 2,
    AllYUVch = 9
};

#endif /* TYPES_H_ */
