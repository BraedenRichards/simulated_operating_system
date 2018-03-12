/**
	CS 446 Assignment 2
	configuration.cpp
	Purpose: Contains the functions included in the class 'Configuration'

	@author Braeden J Richards
*/

#include "configuration.h"

/**
	Creator function for a Configuration object

	@param void
	@return void
*/
Configuration::Configuration()
{


	return;
}

/**
	Opens, extracts, and saves the needed data from the config file

	@param fileName - the name of the config file to open
	@return int value - 0 if successful, 1 if not
*/
int Configuration::LoadConfigFile(std::string file_name)
{
	std::ifstream in_file;

	in_file.open(file_name.c_str());

	if(in_file.is_open())
	{
		/**
				when file_name_flag == false, save file name to meta data file string
		    when file_name_flag == true, save file name to log file string
		*/
		bool file_name_flag = false;
		int what_cycle = 0;
		std::string meta_file, log_file, temp, log_to;

		/**
				THE FOLLOWING CAN AND WILL BE MADE SIMPLER AND EASIER TO READ,
					however it DOES WORK in its current state
		*/
		while(!in_file.eof())
		{
			in_file >> temp;

			//to get the integer cycle times
			if(temp.compare("{msec}:") == 0)
			{
				in_file >> temp;

				/** TO GET CYCLE TIMES **/
				if(what_cycle == 0)
				{
					int val = 5;
					std::stringstream typ_int(temp);
					typ_int >> val;
					SetMonitor(val);
					what_cycle++;
				}
				else if(what_cycle == 1)
				{
					int val = 5;
					std::stringstream typ_int(temp);
					typ_int >> val;
					SetProcessor(val);
					what_cycle++;
				}
				else if(what_cycle == 2)
				{
					int val = 5;
					std::stringstream typ_int(temp);
					typ_int >> val;
					SetScanner(val);
					what_cycle++;
				}
				else if(what_cycle == 3)
				{
					int val = 5;
					std::stringstream typ_int(temp);
					typ_int >> val;
					SetHardDrive(val);
					what_cycle++;
				}
				else if(what_cycle == 4)
				{
					int val = 5;
					std::stringstream typ_int(temp);
					typ_int >> val;
					SetKeyboard(val);
					what_cycle++;
				}
				else if(what_cycle == 5)
				{
					int val = 5;
					std::stringstream typ_int(temp);
					typ_int >> val;
					SetMemory(val);
					what_cycle++;
				}
				else if(what_cycle == 6)
				{
					int val = 5;
					std::stringstream typ_int(temp);
					typ_int >> val;
					SetProjector(val);
					what_cycle++;
				}
			}

			else if(temp.compare("{kbytes}:") == 0)
			{
				in_file >> temp;
				int val = 5;
				std::stringstream typ_int(temp);
				typ_int >> val;
				SetSystemMemory(val);
			}
			else if(temp.compare("{gbytes}:") == 0)
			{
				in_file >> temp;
				int val = 5;
				std::stringstream typ_int(temp);
				typ_int >> val;
				val = val*1000000;
				SetSystemMemory(val);
			}
			else if(temp.compare("{mbytes}:") == 0)
			{
				in_file >> temp;
				int val = 5;
				std::stringstream typ_int(temp);
				typ_int >> val;
				val = val * 1000;
				SetSystemMemory(val);
			}

			/** TO GET META NAME AND LOG NAME **/
			else if(temp.compare("Path:") == 0)
			{
				if(!file_name_flag)
				{
					in_file >> meta_file;
					SetMetaDataName(meta_file);
					file_name_flag = true;
				}
				else
				{
					in_file >> log_file;
					SetLogFileName(log_file);
				}
			}

			/** TO GET WHERE TO LOG TO **/
			else if(temp.compare("Log:") == 0)
			{
				for(int i = 0; i < 2; i++)
				{
					in_file >> temp;
				}
				in_file >> log_to;
				SetLogTo(log_to);
			}
		}
		in_file.close();

		//If there was an invalid amount of hardware cycles or file names
		if(!(what_cycle == 7 && file_name_flag))
			return 1; //AN ERROR CODE

		return 0;
	}
	else //IF THERE IS AN ERROR
	{
		return 1;
	}
}

/**
	Saves the value of cycle_time into m_cycle_projector

	@param cycle_time
	@return boolean value - true if successful, false if not
*/
bool Configuration::SetProjector(int cycle_time)
{
	m_cycle_projector = cycle_time;

	return true;
}

/**
	Saves the value of cycle_time into m_cycle_processor

	@param cycle_time
	@return boolean value - true if successful, false if not
*/
bool Configuration::SetProcessor(int cycle_time)
{
	m_cycle_processor = cycle_time;

	return true;
}

/**
	Saves the value of cycle_time into m_cycle_keyboard

	@param cycle_time
	@return boolean value - true if successful, false if not
*/
bool Configuration::SetKeyboard(int cycle_time)
{
	m_cycle_keyboard = cycle_time;

	return true;
}

/**
	Saves the value of cycle_time into m_cycle_monitor

	@param cycle_time
	@return boolean value - true if successful, false if not
*/
bool Configuration::SetMonitor(int cycle_time)
{
	m_cycle_monitor = cycle_time;

	return true;
}

/**
	Saves the value of cycle_time into m_cycle_scanner

	@param cycle_time
	@return boolean value - true if successful, false if not
*/
bool Configuration::SetScanner(int cycle_time)
{
	m_cycle_scanner = cycle_time;

	return true;
}

/**
	Saves the value of cycle_time into m_cycle_memory

	@param cycle_time
	@return boolean value - true if successful, false if not
*/
bool Configuration::SetMemory(int cycle_time)
{
	m_cycle_memory = cycle_time;

	return true;
}

/**
	Saves the value of cycle_time into m_cycle_hard_drive

	@param cycle_time
	@return boolean value - true if successful, false if not
*/
bool Configuration::SetHardDrive(int cycle_time)
{
	m_cycle_hard_drive = cycle_time;

	return true;
}
/**
	Saves the name of the meta data file

	@param file_name
	@return boolean value - true if successful, false if not
*/
bool Configuration::SetMetaDataName(std::string file_name)
{
	m_meta_data_name += file_name;

	return true;
}

/**
	Saves the name of the log file

	@param file_name
	@return boolean value - true if successful, false if not
*/
bool Configuration::SetLogFileName(std::string file_name)
{
	m_log_file_name += file_name;

	return true;
}

/**
	Saves where to log to

	@param choice
	@return boolean value - true if successful, false if not
*/
bool Configuration::SetLogTo(std::string choice)
{
	m_log_to += choice;

	return true;
}

/**
	Sets the amount of system Memory

	@param system_memory
	@return boolean value - true if successful, false if not
*/
bool Configuration::SetSystemMemory(int system_memory)
{
	m_system_memory = system_memory;

	return true;
}


/**
	Returns the value stores in m_cycle_projector

	@param void
	@return m_cycle_projector
*/
int Configuration::GetProjectorCycle()
{
	return m_cycle_projector;
}

/**
	Returns the value stored in m_cycle_processor

	@param void
	@return m_cycle_processor
*/
int Configuration::GetProcessorCycle(){

	return m_cycle_processor;
}

/**
	Returns the value stored in m_cycle_keyboard

	@params void
	@return m_cycle_keyboard
*/
int Configuration::GetKeyboardCycle()
{

	return m_cycle_keyboard;
}

/**
	Returns the value stored in m_cycle_monitor

	@params void
	@return m_cycle_monitor
*/
int Configuration::GetMonitorCycle()
{

	return m_cycle_monitor;
}

/**
	Returns the value stored in m_cycle_scanner

	@params void
	@return m_cycle_scanner
*/
int Configuration::GetScannerCycle()
{

	return m_cycle_scanner;
}

/**
	Returns the value stored in m_cycle_memory

	@params void
	@return m_cycle_memory
*/
int Configuration::GetMemoryCycle()
{

	return m_cycle_memory;
}

/**
	Returns the value stored in m_cycle_hard_drive

	@params void
	@return m_cycle_hard_drive
*/
int Configuration::GetHardDriveCycle()
{

	return m_cycle_hard_drive;
}

/**
	Returns the value stored in m_system_memory

	@params void
	@return m_system_memory
*/
int Configuration::GetSystemMemory()
{
	return m_system_memory;
}

/**
	Prints the values of all data held in the object to display (monitor)

	@params void
	@return void
*/
void Configuration::PrintAllData()
{
	std::cout << "Configuration File Data" << std::endl;
	std::cout << "Monitor = " << m_cycle_monitor << " ms/cycle" << std::endl;
	std::cout << "Processor = " << m_cycle_processor << " ms/cycle" << std::endl;
	std::cout << "Scanner = " << m_cycle_scanner << " ms/cycle" << std::endl;
	std::cout << "Hard Drive = " << m_cycle_hard_drive << " ms/cycle" << std::endl;
	std::cout << "Keyboard = " << m_cycle_keyboard << " ms/cycle" << std::endl;
	std::cout << "Memory = " << m_cycle_memory << " ms/cycle" << std::endl;
	std::cout << "Projector = " << m_cycle_projector << " ms/cycle" << std::endl;
	std::cout << "System memory: " << m_system_memory << " kbytes" << std::endl;
	std::cout << "Logged to: ";

	if(m_log_to.compare("Both") == 0)
	{
		std::cout << "monitor and " << m_log_file_name << std::endl;
		std::cout << std::endl;
	}
	else if(m_log_to.compare("Monitor") == 0)
	{
		std::cout << m_log_file_name << std::endl;
		std::cout << std::endl;
	}
	else if(m_log_to.compare("File") == 0)
		std::cout << "monitor\n\n";

	return;
}

/**
	Returns the string containing the name of the meta data file

	@params void
	@return m_meta_data_name
*/
std::string Configuration::GetMetaDataName()
{
	return m_meta_data_name;
}

/**
	Returns the string containing the name of the log file

	@params void
	@return m_log_file_name
*/
std::string Configuration::GetLogFileName()
{
	return m_log_file_name;
}

/**
	Returns the string containing where to log to

	@params void
	@return m_log_to
*/
std::string Configuration::GetLogTo()
{
	return m_log_to;
}