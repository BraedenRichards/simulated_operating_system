/**
	CS 446 Assignment 2
	linkedlist.cpp
	Purpose: Contains prototype of the class metadata

	@author Braeden J Richards
*/

#include "linkedlist.h"

/**
  Constructor for the class LinkedList

  @params void
  @return void
*/
LinkedList::LinkedList()
{
  head = NULL;
  tail = NULL;

  return;
}

/**
  Creates a new node in the linked list

  @params data - string containing data to hold in the node
  @return void
*/
void LinkedList::AddNode(std::string data)
{
  node *temp = new node;
  temp->data = data;
  temp->next = NULL;

  if(head ==NULL)
  {
    head = temp;
    tail = temp;
  }
  else
  {
    tail->next = temp;
    tail = tail->next;
  }

  return;
}
