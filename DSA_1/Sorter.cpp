//============================================================================
// Name        : Sorter.cpp
// Author      : AM
// Version     : 1.0
// Description : Class to provide functions for sorting. Definitions.
//============================================================================
#include "Sorter.h"

int Sorter::partition(std::vector<Course>& p_courses, int begin, int end) {

    //set low and high equal to begin and end
    unsigned int low = begin;
    unsigned int high = end;

    // pick the middle element as pivot point
    std::string pivot = p_courses[low + (high - low) / 2].number;

    // while not done 
    bool done = false;
    while (!done)
    {
        // keep incrementing low index while bids[low] < bids[pivot]
        while (p_courses[low].number.compare(pivot) < 0)
        {
            low++;
        }
        // keep decrementing high index while bids[pivot] < bids[high]
        while (p_courses[high].number.compare(pivot) > 0)
        {
            high--;
        }
        /* If there are zero or one elements remaining,
            all courses are partitioned. Return high */
        if (low >= high)
        {
            done = true;
        }
        // else swap the low and high courses (built in vector method)
        else
        {
            std::swap(p_courses.at(high), p_courses.at(low));
            // move low and high closer ++low, --high
            high--;
            low++;
        }
    }

    return high;
}

void Sorter::quicksort(std::vector<Course>& p_courses, int begin, int end) {
    //set mid equal to 0
    int midpoint = 0;

    /* Base case: If there are 1 or zero courses to sort,
     partition is already sorted otherwise if begin is greater
     than or equal to end then return*/
    if (begin >= end)
    {
        return;
    }

    /* Partition courses into low and high such that
     midpoint is location of last element in low */
    midpoint = partition(p_courses, begin, end);

    // recursively sort low partition (begin to mid)
    quicksort(p_courses, begin, midpoint);

    // recursively sort high partition (mid+1 to end)
    quicksort(p_courses, midpoint + 1, end);

}

// Simple function to make each character in string lowercase. Used to ignore case of user input for comparison
std::string Sorter::toLower(std::string str) {
    transform(str.begin(), str.end(), str.begin(), tolower);
    return str;
}

void Sorter::search(std::vector<Course>& p_courses) {

    std::string choice;

    std::cout << std::endl;
    std::cout << "What course would you like to know more about?: ";
    std::cin >> choice;
    std::cout << std::endl;

    // Iterate through course list and look for course entered by user
    for (size_t i = 0; i < p_courses.size(); i++) {
        // If course is found, print course information and prerequisites
        if (toLower(p_courses.at(i).number).compare(toLower(choice)) == 0) {  // toLower method used to ignore case of user input
            std::cout << p_courses.at(i).number << ", " << p_courses.at(i).title << std::endl;
            std::cout << "Prerequisites: ";
            for (size_t j = 0; j < p_courses.at(i).prerequisites.size(); j++) {
                std::cout << p_courses.at(i).prerequisites.at(j) << ", ";
            }
            std::cout << std::endl;
            std::cout << std::endl;
            return;
        }
    }

    // If course is not found, return error
    std::cout << "*****************COURSE NOT FOUND*****************" << std::endl;

    // Clear input
    std::cin.clear();
    std::cin.ignore(999, '\n');
    std::cout << std::endl;

}