/**
	CS 446 Assignment 2
	linkedlist.h
	Purpose: Contains prototype of the class linkedlist and has the node struct

	@author Braeden J Richards
*/

#ifndef string
#include <string>
#endif

struct node
{
  char data_code; //Holds the data code
  std::string data_descriptor; //Holds the descritor
  int number_of_cycles; //Holds the number of cycles to run
  std::string data; //Holds data_code, data_descriptor, and number_of_cycles as one string
  node *next; //next node
};

class LinkedList{
public:
  LinkedList();

  void AddNode(std::string data);

  node *head;
  node *tail;
};
