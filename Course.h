#pragma once
#include <string>
#include <vector>

class Course {
public:
	std::string number;
	std::string title;
	std::vector<std::string> prerequisites;

	Course() = default;
};

