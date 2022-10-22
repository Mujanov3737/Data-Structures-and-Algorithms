//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Ahmet Mujanovic
// Version     : 1.0
// Description : CS300 Project Two Entry Point
//============================================================================

#include <iostream>
#include <iomanip>
#include <string>

#include "Course.h"
#include "FileHandler.h"
#include "Sorter.h"

void displayMenu() {

	// Data structure to hold course objects
	std::vector<Course> courses;

	FileHandler* loader = new FileHandler();
	Sorter* sorter = new Sorter();

	// Booleans to handle triggers throughout program, such as when data is sorted and loaded so actions do not repeat
	bool sorted = false;
	bool loaded = false;
	bool exit = false;
	while (!exit) {

		int userChoice;

		std::cout << "Welcome to the course planner.\n" << std::endl;
		std::cout << "1. Load Data Structure" << std::endl;
		std::cout << "2. Print Course List." << std::endl;
		std::cout << "3. Print Course" << std::endl;
		std::cout << "4. Exit" << std::endl;
		std::cout << "What would you like to do?: ";

		// Get user choice input
		std::cin >> userChoice;
		switch (userChoice)
		{
		case 1:
			// If the data was already loaded, don't do it again.
			if (loaded == true)
			{
				std::cout << std::endl;
				std::cout << "*****************DATA ALREADY LOADED*****************" << std::endl;
				std::cout << std::endl;
				break;
			}
			// Parse file, create tokens, and add to structure. 
			try {
				courses = loader->fileParseLoad("coursesFile.txt");
				std::cout << std::endl;
				std::cout << "*****************DATA LOADED*****************" << std::endl;
				std::cout << std::endl;
				loaded = true;
				break;
			}
			// Catch error if file couldn't be opened
			catch (const char* fileErrorExcpt) {
				std::cout << std::endl;
				std::cout << "EXCEPTION: " << fileErrorExcpt << std::endl;
			}
		case 2:
			// If the data wasn't loaded, prompt user to load it first.
			if (loaded != true) {
				std::cout << std::endl;
				std::cout << "*****************PLEASE LOAD DATA FIRST*****************" << std::endl;
				std::cout << std::endl;
				break;
			}
			// Sort data structure alphanumerically first if not sorted already
			std::cout << "\nHere is a sample schedule: \n" << std::endl;
			if (sorted != true) {
				sorter->quicksort(courses, 0, courses.size() - 1);
			}
			// If data is sorted, iterate over data structure and print each course number and corresponding title
			for (size_t i = 0; i < courses.size(); i++) {
				std::cout << courses.at(i).number << ", " << courses.at(i).title;
				/*
				for (size_t j = 0; j < courses.at(i).prerequisites.size(); j++) {
					std::cout << courses.at(i).prerequisites.at(j) << " | ";
				}
				*/
				std::cout << std::endl;
			}
			std::cout << std::endl;
			break;
		case 3:
			// If the data wasn't loaded, prompt user to load it first.
			if (loaded != true) {
				std::cout << std::endl;
				std::cout << "*****************PLEASE LOAD DATA FIRST*****************" << std::endl;
				std::cout << std::endl;
				break;
			}
			//Call function to ask for course number, search for match, then print that course's name, number, and prerequisites
			sorter->search(courses);
			break;
		case 4:
			// Exit case
			std::cin.clear();
			std::cin.ignore(999, '\n');
			std::cout << std::endl;
			std::cout << "Thank you for using the course planner!";
			std::cout << std::endl;
			exit = true;
			break;
		default:
			// Default case if no proper input is made. Clears input.
			std::cin.clear();
			std::cin.ignore(999, '\n');
			std::cout << std::endl;
			std::cout << "Please enter a valid choice." << std::endl;
			std::cout << std::endl;
			break;
		}
	}
}
int main() {
	displayMenu();
}