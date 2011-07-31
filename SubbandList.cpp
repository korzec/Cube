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
    //create the data structure wtih 2d vector
    std::vector<CoeffView3D> vec;
    list.resize(levels+1, vec);

    Coords3D dims(cube.shape());
    
    //set level 0 subband LL
    //size/2^levels
    CoeffView3D view =  cube[ indices
                        [range(0,dims.depth)]
                        [range(0,dims.height)]
                        [range(0,dims.width)] ];
    
    vec.push_back(view);
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
                    CoeffView3D view = cube[ indices
                        [range(d*dL,(d+1)*dL)]
                        [range(h*hL,(h+1)*hL)]
                        [range(w*wL,(w+1)*wL)] ];
                    list[i].push_back(view);
                }
            }
        } 

        
    }
}

SubbandList::SubbandList(const SubbandList& orig)
{
}

SubbandList::~SubbandList()
{
}

int SubbandList::GetLevel()
{
    return list.size()-1;
}