/**
	CS 446 Assignment 1
	log.h
	Purpose: Contains prototype of the class LogFile

	@author Braeden J Richards
*/

#ifndef string
#include <string>
#endif

#ifndef fstream
#include <fstream>
#endif

#ifndef iostream
#include <iostream>
#endif

class LogFile{
public:
  LogFile(std::string file_name); //Constructor
  LogFile(); //Constructor

  void OpenFile(std::string file_name); //Opens the file to be used
  void LogString(std::string data); //Writes a string to the log file
  void LogInt(int data); //Writes an integer to the log file
  void LogFloat(float data); //Writes a float to the log file
  void LogChar(char data); //Writes a character to the log file
  void LogDouble(double data); //Writes a double to the log file
  void LogHex(int data); //Writes a hex value to the log file

  std::ofstream m_out_file; //File that is open to written to

private:
  std::string m_file_name; //File name
};
