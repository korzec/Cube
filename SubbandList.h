/* 
 * File:   SubbandList.h
 * Author: korzec
 *
 * Created on July 30, 2011, 9:22 PM
 */

#ifndef SUBBANDLIST_H
#define	SUBBANDLIST_H

#include "types.h"

class SubbandList
{
public:
    bool SetLevel(unsigned char level);
    CoeffView3D& GetSubband(int level, Orientation orient);
    
    void Init(CoeffArray3D& cube, int levels);
    int GetLevel();
    
    SubbandList(CoeffArray3D& cube, int levels);
    SubbandList();
    SubbandList(const SubbandList& orig);
    virtual ~SubbandList();
    
private:
    std::vector< std::vector<CoeffView3D> > list;
};

#endif	/* SUBBANDLIST_H */

