/**
	CS 446 Assignment 2
	log.cpp
	Purpose: Contains the functions included in the class 'LogFile'

	@author Braeden J Richards
*/

#include "log.h"

/**
 	Creator function for a LogFile object

	@param file_name - string containing the name of the log file to be used
	@return void
*/
LogFile::LogFile(std::string file_name)
{
  m_out_file.open(file_name.c_str());

  return;
}

/**
  Creator function for a LogFile object

  @param void
  @return void
*/
LogFile::LogFile()
{

  return;
}

/**
  Opens the file to be used as the log file

  @param file_name - string containing the name of the log file to be used
  @return: void
*/
void LogFile::OpenFile(std::string file_name)
{
  m_out_file.open(file_name.c_str());

  return;
}

/**
  Outputs a string to the log file

  @param data - string containing data to be output to the log file
  @return void
*/
void LogFile::LogString(std::string data)
{
  m_out_file << data;

  return;
}

/**
  Outputs an integer to the log file

  @param data - int containing the data to be output to the log file
  @return void
*/
void LogFile::LogInt(int data)
{
  m_out_file << data;

  return;
}

/**
  Outputs a float to the log fileName

  @param data - float containing the data to be output ot the log file
  @return void
*/
void LogFile::LogFloat(float data)
{
  m_out_file << data;

  return;
}

/**
  Outputs a char to the log fileName

  @param data - char containing the data to be output ot the log file
  @return void
*/
void LogFile::LogChar(char data)
{
  m_out_file << data;

  return;
}

/**
  Outputs a double to the log fileName

  @param data - double containing the data to be output ot the log file
  @return void
*/
void LogFile::LogDouble(double data)
{
  m_out_file << data;

  return;
}

/**
  Outputs a hex to the log fileName

  @param data - int containing the data to be output ot the log file
  @return void
*/
void LogFile::LogHex(int data)
{
  m_out_file << std::hex << data;

  return;
}
