/* 
 * File:   SubcubeIndex.h
 * Author: korzec
 *
 * Created on July 31, 2011, 7:25 PM
 */

#ifndef SUBCUBEINDEX_H
#define	SUBCUBEINDEX_H

#include "types.h"
#include "Subcube.h"
#include <map>

//types for SubcubeIndex
typedef std::multimap<float, Subcube*> WeightsMap;
typedef std::pair<float, Subcube*> WeightPair;
typedef boost::multi_array<Subcube, 3> SubcubeArray3D;
typedef boost::multi_array<float, 3 > FloatArray3D;

///stores an 3D array of Subcube (#SubcubeArray3D)
class SubcubeIndex
{
public:
    SubcubeIndex();
    SubcubeIndex(CoeffView3D& cube, Coords3D size );
    void Init(CoeffView3D& cube, Coords3D subSize );
    Subcube& GetSubcube(Coords3D& index);
    void ComputeWeights();
    Coords3D GetIndexDims();
    bool dump(std::string);
    WeightsMap& GetWeightsMap();
private:
    SubcubeArray3D list;
    FloatArray3D weights;
    WeightsMap weightsMap;
};

#endif	/* SUBCUBEINDEX_H */

