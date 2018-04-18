/**
	CS 446 Assignment 3
	metadata.h
	Purpose: Contains prototype of the class metadata

	@author Braeden J Richards
*/
#ifndef iostream
#include <iostream>
#endif

#ifndef string
#include <string>
#endif

#ifndef fstream
#include <fstream>
#endif

#ifndef linkedlist
#include "linkedlist.h"
#endif

#ifndef stack
#include <stack>
#endif

#ifndef algorithm
#include <algorithm>
#endif

#ifndef sstream
#include <sstream>
#endif


class MetaData{
public:
  MetaData();
  int LoadMetaFile(std::string file_name); // Loads data into linked list 'data'

  void PrintAllData(); // Prints all data in the linked list to the monitor
  void BreakUpData(node *nodeForThis); // Breaks the data into smaller pieces in linked list
  void SortData(std::string sort_type); // Sorts the data into either FIFO, PS, or SJF

  LinkedList data; // Holds the sorted data for use in the main program

private:
  LinkedList unsorted_data; // Holds the parsed data from the meta data file
};
