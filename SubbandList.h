/* 
 * File:   SubbandList.h
 * Author: korzec
 *
 * Created on July 30, 2011, 9:22 PM
 */

#ifndef SUBBANDLIST_H
#define	SUBBANDLIST_H

#include "types.h"

///stores a list of all subbands of a #CoeffArray3D
class SubbandList
{
public:
    bool SetLevel(unsigned char level);
    CoeffView3D& GetSubband(int level, Orientation orient);
    
    void Init(CoeffArray3D& cube, int levels);
    int GetLevel();
    
    ///returns number of subbands per given level
    int SubbandCountForLevel(size_t level);
    
    SubbandList(CoeffArray3D& cube, int levels);
    SubbandList();
    
private:
    std::vector< std::vector<CoeffView3D> > list;
};

#endif	/* SUBBANDLIST_H */

