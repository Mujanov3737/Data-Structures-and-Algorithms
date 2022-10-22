//============================================================================
// Name        : FileHandler.cpp
// Author      : Ahmet Mujanovic
// Version     : 1.0
// Description : Class to handle file parsing and data loading. Definitions.
//============================================================================
#include "FileHandler.h"
#include "Course.h"

// This function will open the file, token each line, create a course object from line, and store that object into a vector
std::vector<Course> FileHandler::fileParseLoad(std::string fileName) {

	std::vector<Course> courses;

	std::fstream file;
	std::string line;
	std::string token;
	int count = 0;

	file.open(fileName, std::ios::in);

	// Throw exception if the file could not be opened
	if (!file.is_open()) {
		throw "Could not open file";
	}

	// Parse file line by line, break each line into tokens, and store into course object
	else if (file.is_open()) {
		while (std::getline(file, line)) {
			Course* course = new Course();
			std::stringstream sstream(line);
			while (std::getline(sstream, token, ',')) {
				//std::cout << token << std::endl;
				if (count == 0) {
					course->number = token;
					count++;
				}
				else if (count == 1) {
					course->title = token;
					count++;
				}
				else {
					course->prerequisites.push_back(token);
					count++;
				}
			}

			// Add the course object to the vector. Counter is to handle what token is attributed to what course object field
			courses.push_back(*course);
			count = 0;
		}
	}

	file.close();

	return courses;
}