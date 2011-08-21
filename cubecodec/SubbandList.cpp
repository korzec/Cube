/* 
 * File:   SubbandList.cpp
 * Author: korzec
 * 
 * Created on July 30, 2011, 9:22 PM
 */

#include "SubbandList.h"

SubbandList::SubbandList()
{
}

SubbandList::SubbandList(CoeffArray3D& cube, int levels)
{
    Init(cube, levels);
}

CoeffView3D& SubbandList::GetSubband(int level, Orientation orient)
{
    return list[level][orient];
}
    

void SubbandList::Init(CoeffArray3D& cube, int levels)
{
    //use a dummy vector to initialise the list 
    //because #CoeffView3D does not have default constructor 
    std::vector<CoeffView3D> vec;
    list.resize(levels+1, vec);

    Coords3D dims(cube.shape());
    
    //set level 0 subband LLL
    //size/2^levels
    CoeffView3D view =  cube[ boost::indices
                        [range(0,dims.depth)]
                        [range(0,dims.height)]
                        [range(0,dims.width)] ];

    list[0].push_back(view);

    for (int i = 1; i <= levels; i++)
    {
        int dL = dims.depth>>i; 
        int hL = dims.height>>i; 
        int wL = dims.width>>i; 
        for (int d = 0; d < 2 ; d++)
        {
            for (int h = 0; h < 2 ; h++)
            {
                for (int w = 0; w < 2 ; w++)
                {
                    CoeffView3D view = cube[ boost::indices
                        [range(d*dL,(d+1)*dL)]
                        [range(h*hL,(h+1)*hL)]
                        [range(w*wL,(w+1)*wL)] ];
                    list[i].push_back(view);
                }
            }
        } 

        
    }
}


int SubbandList::GetLevel()
{
    return list.size()-1;
}

int SubbandList::SubbandCountForLevel(size_t level)
{
    //level out of range
    if( list.size() <= level)
        return -1;
    return list[level].size();
}