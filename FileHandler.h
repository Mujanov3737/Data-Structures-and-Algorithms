//============================================================================
// Name        : FileHandler.h
// Author      : Ahmet Mujanovic
// Version     : 1.0
// Description : Class to handle file parsing and data loading. Declarations.
//============================================================================
#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

#include "Course.h"

class FileHandler
{
public:
	std::vector<Course> fileParseLoad(std::string fileName);
};