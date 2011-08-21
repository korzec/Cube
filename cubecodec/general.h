/* 
 * File:   general.h
 * Author: korzec
 * 
 * General purpose functions
 *
 * Created on July 28, 2011, 11:00 PM
 */

#ifndef GENERAL_H
#define	GENERAL_H

#include "types.h"
#include "Subcube.h"
#include "SubcubeIndex.h"
#include <string>
#include <iostream>
#include <fstream>
#include <map>

/// copy a Picture to slice in CoeffCube
bool copyArrayFromValueToCoeff(ValueArray2Dref& from, CoeffView2D& to);
/// copy a slice from CoeffCube to a Picture
bool copyArrayFromCoeffToValue(CoeffView2D& from, ValueArray2Dref& to);

///saves CoeffArray3D to a file for analysis
bool dumpCube(CoeffArray3D& cube, std::string fileName);
/// writes weights of each value in CoeffCube to a file for analysis
bool dumpSubcubes(SubcubeArray3D& subcubes, FloatArray3D& weights, std::string fileName);

///find number of occurencies of CoeffType symbols and put into a map
typedef std::map<CoeffType, int> CoeffMap;
//typedef boost::shared_ptr<CoeffMap> CoeffMapPtr;

CoeffMap getSymbolStatistics(CoeffView3D& array);
//output a statistics map to csv file
bool writeMap(CoeffMap map, std::string fileName);
#endif	/* GENERAL_H */