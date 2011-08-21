/* 
 * File:   arrays.h
 * Author: korzec
 *
 * Created on August 21, 2011, 8:41 AM
 */

#ifndef ARRAYS_H
#define	ARRAYS_H

#ifndef DEBUG
#define BOOST_DISABLE_ASSERTS 
#endif

typedef short CoeffType;
typedef unsigned char ValueType;

#include <boost/multi_array.hpp>
#include <boost/smart_ptr.hpp>

typedef boost::multi_array_ref<ValueType, 2 > ValueArray2Dref;
typedef boost::shared_ptr<ValueArray2Dref> ValueArray2DrefPtr;
typedef boost::detail::multi_array::sub_array<CoeffType, 2> CoeffView2D;

typedef boost::multi_array<CoeffType, 3 > CoeffArray3D;
typedef boost::shared_ptr<CoeffArray3D> CoeffArray3DPtr;
typedef CoeffArray3D::array_view<3>::type CoeffView3D;
typedef boost::shared_ptr<CoeffView3D> CoeffView3DPtr;
//pointer to coded data
typedef boost::shared_array<unsigned char> ucharPtr;

typedef boost::multi_array_types::index_range range;

class Coords3D
{
public:
    int width;
    int height;
    int depth;
    Coords3D() : width(-1), height(-1), depth(-1)
    {
        
    }
    Coords3D(int width, int height, int depth)
    {
         this->width = width;
         this->height = height;
         this->depth = depth;
    }
    
    Coords3D(const boost::multi_array_types::size_type* dimensionality)
    {
         this->width = dimensionality[2];
         this->height = dimensionality[1];
         this->depth = dimensionality[0];
    }
    Coords3D& Set(int width, int height, int depth)
    {
         this->width = width;
         this->height = height;
         this->depth = depth;
         return *this;
    }
    int Volume()
    {
        return width*height*depth;
    }
};


#endif	/* ARRAYS_H */

