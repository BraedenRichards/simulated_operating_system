/**
	CS 446 Assignment 2
	thread.h
	Purpose: Contains the structure to be used in pthreads

	@author Braeden J Richards
*/

#include <ctime>

struct thread_data
{
  int cycle_time;
  int amount_cycles;
  clock_t current_time;
};
