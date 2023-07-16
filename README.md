# Data-Structures
Included in this repository are two folders that contain applications written in C++ that explore various data structures and algorithms.
## DSA_1 Courses List
This folder contains a solution file and code which simply reads a course list from a text file, parses through the file, sorts the contents, and presents a few options for the user through the console window. The application utilizes a partition and quicksorting to handle the sorting portion and a vector to store the data.

![dsa1](https://github.com/Mujanov3737/Data-Structures/assets/75598761/c7bb2abe-af5e-4a18-a604-7f5e28165f5b)
![dsa2](https://github.com/Mujanov3737/Data-Structures/assets/75598761/ff1c8da4-1b39-4b37-b58f-288d94f7d140)

## DSA_2 Data Structures
The other folder in this repository contains 4 .cpp files that each implement a version of various data structures, such as a BST, hash table, linked list, and vector, as well as implement their corresponding member functions for traversal, insertion, and deletion. The test functions in each of these files rely on a CSVParser file and CSV data file to retrieve data of inventory items, but these files are unfortunately unavailable, so testing these implementations is not possible with this repository. However, the implementations of each data structure contain working code which can be implemented with another dataset.

## Importance of data structures

Analyzing the capabilities of each data structure was the first step in the process of choosing which would be best suited for a particular scenario. No data structure is perfect for every scenario thus it is important to understand when and where to use a structure appropriately. For instance, a hash table may provide constant access time but only if there exists a sufficient hash function to eliminate collisions. A linked-list may provide constant insertion time but requires linear traversal time to find a particular element in the list. After considering all the options of each structure, the appropriate one could be chosen and utilized in the project scenario.

## Overcoming issues

Data structures and algorithms are certainly a difficult computer science subject that require a significant amount of practice and comfort with logical thinking. Often, learning the conceptual version of the data structure or algorithm was clear and logical. Implementing the structures or algorithms using the constructs of the programming language was more difficult. Having a solid grasp on the concept of a structure, the repetition of implementing the structure in a coding environment was key to solidifying the concept as a whole. Referring back to documentation, readings, and examples helped to provide the necessary guidance to push through and make breakthroughs in understanding.

The question when implementing algorithms is often one of efficiency. Are there unnecessary and redundant iterations? Was there a more efficient way to approach solving this problem that involved less time and less memory? Analyzing the strengths and weaknessess of each algorithm and data structure for a particular scenario is a crucial skill in developing applications that run efficiently and produce acceptable results for each use case. Simply using a dynamic array for most collections is a mistake because it does not take into consideration what kind of data is being stored. Additionally, many programming languages or environments differ in how they implement a data structure, so it is important to become familiar with the tools being used in order to reach a desirable decision on how to use them. 
