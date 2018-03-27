/**
	CS 446 Assignment 2
	configuration.h
	Purpose: Contains prototype of the class Configuration

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

#ifndef sstream
#include <sstream>
#endif

class Configuration{
public:
	Configuration();

	bool SetProjector(int cycle_time); //Sets the cycle time of the projector
	bool SetProcessor(int cycle_time); //Sets the cycle time of the processor
	bool SetKeyboard(int cycle_time);  //Sets the cycle time of the keyboard
	bool SetMonitor(int cycle_time);   //Sets the cycle time of the monitor
	bool SetScanner(int cycle_time);   //Sets the cycle time of the scanner
	bool SetHardDrive(int cycle_time); //Sets the cycle time of the hard drive
	bool SetMemory(int cycle_time);    //Sets the cycle time of the memory
	bool SetMetaDataName(std::string file_name); //Sets name for the meta data file
	bool SetLogFileName(std::string file_name); //Sets name for the log file
	bool SetLogTo(std::string choice); //Sets whether to log to monitor, logile, or both
	bool SetSystemMemory(int system_memory); //Sets the system memory
  bool SetProjectorQuantity(int quantity); //Sets the projector quantity
  bool SetHardDriveQuantity(int quantity); //Sets the hard drive quantity
  bool SetMemoryBlockSize(int size); //Sets the size of the memory blocks in kilobytes

	int LoadConfigFile(std::string file_name); //Loads the file data
	int GetProjectorCycle(); //Returns the value of m_cycle_projector
	int GetProcessorCycle(); //Returns the value of m_cycle_processor
	int GetKeyboardCycle();  //Returns the value of m_cycle_keyboard
	int GetMonitorCycle();   //Returns the value of m_cycle_monitor
	int GetScannerCycle();   //Returns the value of m_cycle_scanner
	int GetMemoryCycle();    //Returns the value of m_cycle_memory
	int GetHardDriveCycle(); //Returns the value of m_cycle_hard_drive
	int GetSystemMemory();   //Returns the value of m_system_memory
  int GetProjectorQuantity(); //Returns the quantity of projectors
  int GetHardDriveQuantity(); //Returns the quantity of hard drives
  int GetMemoryBlockSize(); //Returns the size of the memory blocks in kilobytes

	void PrintAllData();     //Prints all int values of this object out

	std::string GetMetaDataName(); //Returns the name of the meta data file
	std::string GetLogFileName(); //Returns the name of the log file
	std::string GetLogTo(); //Returns where to log to

private:
	int m_cycle_projector; //cycle time in ms of the projector
	int m_cycle_processor; //cycle time in ms of the processor
	int m_cycle_keyboard;  //cycle time in ms of the keyboard
	int m_cycle_monitor;   //cycle time in ms of the monitor
	int m_cycle_scanner;   //cycle time in ms of the scanner
	int m_cycle_memory;    //cycle time in ms of the memory
	int m_cycle_hard_drive; //cycle time in ms of the hard drive
	int m_system_memory; //amount of system memory
  int m_projector_quantity; //quantity of projectors in system
  int m_hard_drive_quantity; //quantity of hard drive in system
  int m_memory_block_size; //size of the memory's blocks, in kilobytes

	std::string m_meta_data_name; //name of the meta data file
	std::string m_log_file_name; //name of the log file
	std::string m_log_to; //Whether to log to monitor, logfile, or both

};
