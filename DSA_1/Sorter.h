//============================================================================
// Name        : Sorter.h
// Author      : AM
// Version     : 1.0
// Description : Class to provide functions for sorting. Declarations.
//============================================================================
#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include "Course.h"

class Sorter {
public: 
	int partition(std::vector<Course>& p_courses, int begin, int end);
	void quicksort(std::vector<Course>& p_courses, int begin, int end);
	void search(std::vector<Course>& p_courses);
	std::string toLower(std::string str);
};
