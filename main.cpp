/**
	CS 446 Assignment 2
	main.cpp
	Purpose: contains the main function to run the program as well as a few functions
						needed in the main function

	@author Braeden J Richards
*/

/****HEADER FILES****/
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime> //used in the creation of a timer
#include <stdlib.h> //used to make a random number
#include <time.h> //used to make a random number
#include "configuration.h"
#include "log.h"
#include "metadata.h"
#include "thread.h"
#include "pcb.h"


/****DEFINITIONS****/
#define PCB_START 0
#define PCB_READY 1
#define PCB_RUNNING 2
#define PCB_WAIT 3
#define PCB_EXIT 4


/****PROTOTYPES****/
/**
	pthread function used to simulate an I/O operation. Right now, it just waits
		the proper amount of time before exiting

	@params void* my_data
	@return void*
*/
void *SimulateIO(void* my_data);

/**
	Timer that is 'activated' whenever the global variable 'timer_set' != 0

	@params void*
	@return void*
*/
void *Timer_Thread(void*);

/**
	Logs the data from configuration file as well as calculated run times to either
		the monitor, log file, or both depending on value of log_to

	@params log_out, config_class, log_to
	@return void
*/
void LogData(LogFile* log_out, Configuration config_file, int log_to, MetaData meta_data);
/**
	Returns the amount of time that has passed since start of the clock and the end

	@params two clock_t objects, current_clock and end_clock
	@return double
*/
double time_taken(clock_t current_clock, clock_t end_clock);

/**
	Outputs the time taken for each process to montor and/or logfile depending on
		log_out

	@params data_double, data, log_out, log_to
	@return void
*/
void logTime(double data_double, std::string data, LogFile* log_out, int log_to);

/**
	Essentially a timer. Function exists and runs until the runtime has exceeded
		run_time

	@params doubel run_time
	@return void
*/
void RunTillDone(double run_time);

/**
	Outputs Error Message

	@params error - an int
	@return void
*/
void OutputErrorMessage(int error);

/**
	Logs the data from configuration file as well as calculated run times to either
		the monitor, log file, or both depending on value of log_to

	@params log_out, config_class, log_to
	@return void
*/
void RunProgram(thread_data my_data, MetaData meta_data, LogFile* log_out, int log_to, Configuration config_file, PCB *pcb);

/**
	Returns a random number

	@params void
	@return int
*/
int GetRandomInt();

/**
	Logs the objects of MetaData and Configuration to a logfile

	@params void
	@return void
*/
void LogFiles(MetaData, Configuration, LogFile*);

/**
	Waits to return until timer_set is 0

	@params void
	@return void
*/
void wait();


/****GLOBAL VARIABLES****/
double timer_set = 0;


/****MAIN FUNCTION****/
int main(int argc, char *argv[])
{
	if(argc == 2)
	{
		Configuration config_file; //Object holding data from configuration file
		LogFile log_out; //Object used to log data to a log file
		MetaData meta_data; //Object holding data from meta data file
		thread_data my_data; //Struct for holding data for a thread
		PCB pcb; //Struct representing the pcb
		pthread_t timerID = 0;
		int log_to; //Used to signal whether to log to file, monitor, or both
		int error = 0; //Used for error handling, 0 means no error

		pthread_create(&timerID, NULL, Timer_Thread, NULL); //TIMER THREAD

		//Reads configuration file data in the Configuration object
		error = config_file.LoadConfigFile(argv[1]);

		if(error == 0)
		{
			// Opens the file to be used for logging
			log_out.OpenFile(config_file.GetLogFileName());

			//Reads in meta data file into MetaData object
			error = meta_data.LoadMetaFile(config_file.GetMetaDataName());

			if(error == 0)
			{
				//Decides where to log (depending on what config file says)
				if(config_file.GetLogTo().compare("Both") == 0)
				{
					log_to = 0; // Log to both monitor and log file
					LogFiles(meta_data, config_file, &log_out); //Log meta data and config data
				}
				else if(config_file.GetLogTo().compare("Monitor") == 0)
					log_to = 1; // Log to only monitor
				else if(config_file.GetLogTo().compare("File") == 0)
				{
					log_to = 2; // Log to only file
					LogFiles(meta_data, config_file, &log_out); //Log meta data and config data
				}

				/**SIMULATES THE PROGRAM**/
				RunProgram(my_data, meta_data, &log_out, log_to, config_file, &pcb);

			}
		}
		/** IF ERROR OCCURS **/
		if(error != 0)
		{
			OutputErrorMessage(error);
		}
	}
	//If argc value is incorrect
	else
	{
		std::cout << "COMMAND LINE ARGUMENTS INCORRECT" << std::endl;
	}
	return 0;
}


/****NON-MAIN FUNCTION FUNCTIONS****/
/**
	Writes the configuration object's data to a log file

	@params log_out, config_class, log_to
	@return void
*/

void LogData(LogFile* log_out, Configuration config_file, int log_to, MetaData meta_data)
{
	if(log_to == 0 || log_to == 2)
	{
		log_out->LogString("Configuration File Data\n");

		log_out->LogString("Monitor = ");
		log_out->LogInt(config_file.GetMonitorCycle());
		log_out->LogString(" ms/cycle\n");

		log_out->LogString("Processor = ");
		log_out->LogInt(config_file.GetProcessorCycle());
		log_out->LogString(" ms/cycle\n");

		log_out->LogString("Scanner = ");
		log_out->LogInt(config_file.GetScannerCycle());
		log_out->LogString(" ms/cycle\n");

		log_out->LogString("Hard Drive = ");
		log_out->LogInt(config_file.GetHardDriveCycle());
		log_out->LogString(" ms/cycle\n");

		log_out->LogString("Keyboard = ");
		log_out->LogInt(config_file.GetKeyboardCycle());
		log_out->LogString(" ms/cycle\n");

		log_out->LogString("Memory = ");
		log_out->LogInt(config_file.GetMemoryCycle());
		log_out->LogString(" ms/cycle\n");

		log_out->LogString("Projector = ");
		log_out->LogInt(config_file.GetProjectorCycle());
		log_out->LogString(" ms/cycle\n");

		if(log_to == 0)
		{
			log_out->LogString("Logged to: monitor and ");
			log_out->LogString(config_file.GetLogFileName());
		}
		else
		{
			log_out->LogString("Logged to: ");
			log_out->LogString(config_file.GetLogFileName());
		}

		log_out->LogString("\n\nMeta-Data Metrics\n");
	}

	if(log_to == 0 || log_to == 1)
	{
		config_file.PrintAllData();
		std::cout << "Meta-Data Metrics" << std::endl;
	}

	// CalculateMsTime(meta_data.data.head, config_file, log_to, log_out);
}

/**
	Outputs Error Message

	@params error - an int
	@return void
*/
void OutputErrorMessage(int error)
{
	switch(error)
	{
		case 1:
			std::cout << "CONFIGURATION FILE ERROR" << std::endl;
		break;
		case 2:
			std::cout << "META DATA FILE ERROR" << std::endl;
		break;
	}

	return;
}

/**
	Simulates a program

	@params thread_data my_data, MetaData meta_data, LogFile* log_out, int log_to, Configuration config_file
	@return void
*/
void RunProgram(thread_data my_data, MetaData meta_data, LogFile* log_out, int log_to, Configuration config_file, PCB *pcb)
{
	node* temp = meta_data.data.head;
	clock_t start_clock = clock();
	clock_t end_clock = clock();

	logTime(time_taken(start_clock, end_clock), " - Simulator program starting\n", log_out, log_to);

	while(temp != NULL)
	{
		pcb->processState = PCB_START;
		if(temp->data_code == 'S')
		{
			if(temp->data_descriptor.compare("begin") == 0)
			{
				pcb->processState = PCB_READY;
				pcb->processState = PCB_RUNNING;
				end_clock = clock();
				pcb->processState = PCB_EXIT;
				logTime(time_taken(start_clock, end_clock), " - OS: preparing process 1\n", log_out, log_to);
			}
			else if(temp->data_descriptor.compare("finish") == 0)
			{
				pcb->processState = PCB_READY;
				pcb->processState = PCB_RUNNING;
				end_clock = clock();
				pcb->processState = PCB_EXIT;
				logTime(time_taken(start_clock, end_clock), " - Simulator program ending\n", log_out, log_to);
			}
		}
		else if(temp->data_code == 'A')
		{
			if(temp->data_descriptor.compare("begin") == 0)
			{
				pcb->processState = PCB_READY;
				pcb->processState = PCB_RUNNING;
				end_clock = clock();
				logTime(time_taken(start_clock, end_clock), " - OS: starting process 1\n", log_out, log_to);
				pcb->processState = PCB_EXIT;
			}
			else if(temp->data_descriptor.compare("finish") == 0)
			{
				pcb->processState = PCB_READY;
				pcb->processState = PCB_RUNNING;
				end_clock = clock();
				logTime(time_taken(start_clock, end_clock), " - OS: removing process 1\n", log_out, log_to);
				pcb->processState = PCB_EXIT;
			}
		}
		else if(temp->data_code == 'P')
		{
			pcb->processState = PCB_READY;
			pcb->processState = PCB_RUNNING;
			end_clock = clock();
			logTime(time_taken(start_clock, end_clock), " - Process 1: start processing action\n", log_out, log_to);
			timer_set = (temp->number_of_cycles * config_file.GetProcessorCycle())/(double)1000;
			wait();
			end_clock = clock();
			logTime(time_taken(start_clock, end_clock), " - Process 1: end processing action\n", log_out, log_to);
			pcb->processState = PCB_EXIT;
		}
		else if(temp->data_code == 'M')
		{
			if(temp->data_descriptor.compare("allocate") == 0)
			{
				int hex_memory = GetRandomInt();
				pcb->processState = PCB_READY;
				pcb->processState = PCB_RUNNING;
				end_clock = clock();
				logTime(time_taken(start_clock, end_clock), " - Process 1: allocating memory\n", log_out, log_to);
				timer_set = (temp->number_of_cycles * config_file.GetMemoryCycle())/(double)1000;
				wait();
				end_clock = clock();
				logTime(time_taken(start_clock, end_clock), " - Process 1: memory allocated at 0x000000", log_out, log_to);
				std::cout << std::fixed << std::setprecision(2) << std::hex << hex_memory << std::endl;
				log_out->LogHex(hex_memory);
				log_out->LogChar('\n');
				pcb->processState = PCB_EXIT;
			}
			else if(temp->data_descriptor.compare("block") == 0)
			{
				pcb->processState = PCB_READY;
				pcb->processState = PCB_RUNNING;
				end_clock = clock();
				logTime(time_taken(start_clock, end_clock), " - Process 1: start memory blocking\n", log_out, log_to);
				timer_set = (temp->number_of_cycles * config_file.GetMemoryCycle())/(double)1000;
				wait();
				end_clock = clock();
				logTime(time_taken(start_clock, end_clock), " - Process 1: end memory blocking\n", log_out, log_to);
				pcb->processState = PCB_EXIT;
			}
		}
		else if(temp->data_code == 'I')
		{
			if(temp->data_descriptor.compare("harddrive") == 0)
			{
				my_data.cycle_time = config_file.GetHardDriveCycle();
				my_data.amount_cycles = temp->number_of_cycles;
				pthread_t temporary = 0;

				pcb->processState = PCB_READY;
				pcb->processState = PCB_RUNNING;
				pcb->processState = PCB_WAIT;
				end_clock = clock();
				logTime(time_taken(start_clock, end_clock), " - Process 1: start hard drive input\n", log_out, log_to);

				pthread_create(&temporary, NULL, SimulateIO, (void *) &my_data);
				pthread_join(temporary, NULL);

				end_clock = clock();
				logTime(time_taken(start_clock, end_clock), " - Process 1: end hard drive input\n", log_out, log_to);
				pcb->processState = PCB_RUNNING;
				pcb->processState = PCB_EXIT;
			}
			else if(temp->data_descriptor.compare("keyboard") == 0)
			{
				my_data.cycle_time = config_file.GetKeyboardCycle();
				my_data.amount_cycles = temp->number_of_cycles;
				pthread_t temporary = 0;

				pcb->processState = PCB_READY;
				pcb->processState = PCB_RUNNING;
				pcb->processState = PCB_WAIT;
				end_clock = clock();
				logTime(time_taken(start_clock, end_clock), " - Process 1: start keyboard input\n", log_out, log_to);

				pthread_create(&temporary, NULL, SimulateIO, (void *) &my_data);
				pthread_join(temporary, NULL);

				end_clock = clock();
				logTime(time_taken(start_clock, end_clock), " - Process 1: end keyboard input\n", log_out, log_to);
				pcb->processState = PCB_RUNNING;
				pcb->processState = PCB_EXIT;
			}
			else if(temp->data_descriptor.compare("scanner") == 0)
			{
				my_data.cycle_time = config_file.GetScannerCycle();
				my_data.amount_cycles = temp->number_of_cycles;
				pthread_t temporary = 0;

				pcb->processState = PCB_READY;
				pcb->processState = PCB_RUNNING;
				pcb->processState = PCB_WAIT;
				end_clock = clock();
				logTime(time_taken(start_clock, end_clock), " - Process 1: start scanner input\n", log_out, log_to);

				pthread_create(&temporary, NULL, SimulateIO, (void *) &my_data);
				pthread_join(temporary, NULL);

				end_clock = clock();
				logTime(time_taken(start_clock, end_clock), " - Process 1: end scanner input\n", log_out, log_to);
				pcb->processState = PCB_RUNNING;
				pcb->processState = PCB_EXIT;
			}
	}
	else if(temp->data_code == 'O')
	{
		if(temp->data_descriptor.compare("harddrive") == 0)
		{
			my_data.cycle_time = config_file.GetHardDriveCycle();
			my_data.amount_cycles = temp->number_of_cycles;
			pthread_t temporary = 0;

			pcb->processState = PCB_READY;
			pcb->processState = PCB_RUNNING;
			pcb->processState = PCB_WAIT;
			end_clock = clock();
			logTime(time_taken(start_clock, end_clock), " - Process 1: start hard drive output\n", log_out, log_to);

			pthread_create(&temporary, NULL, SimulateIO, (void *) &my_data);
			pthread_join(temporary, NULL);

			end_clock = clock();
			logTime(time_taken(start_clock, end_clock), " - Process 1: end hard drive output\n", log_out, log_to);
			pcb->processState = PCB_RUNNING;
			pcb->processState = PCB_EXIT;
		}
		else if(temp->data_descriptor.compare("monitor") == 0)
		{
			my_data.cycle_time = config_file.GetMonitorCycle();
			my_data.amount_cycles = temp->number_of_cycles;
			pthread_t temporary = 0;

			pcb->processState = PCB_READY;
			pcb->processState = PCB_RUNNING;
			pcb->processState = PCB_WAIT;
			end_clock = clock();
			logTime(time_taken(start_clock, end_clock), " - Process 1: start monitor output\n", log_out, log_to);

			pthread_create(&temporary, NULL, SimulateIO, (void *) &my_data);
			pthread_join(temporary, NULL);

			end_clock = clock();
			logTime(time_taken(start_clock, end_clock), " - Process 1: end monitor output\n", log_out, log_to);
			pcb->processState = PCB_RUNNING;
			pcb->processState = PCB_EXIT;
		}
		else if(temp->data_descriptor.compare("projector") == 0)
		{
			my_data.cycle_time = config_file.GetProjectorCycle();
			my_data.amount_cycles = temp->number_of_cycles;
			pthread_t temporary = 0;

			pcb->processState = PCB_READY;
			pcb->processState = PCB_RUNNING;
			pcb->processState = PCB_WAIT;
			end_clock = clock();
			logTime(time_taken(start_clock, end_clock), " - Process 1: start projector output\n", log_out, log_to);

			pthread_create(&temporary, NULL, SimulateIO, (void *) &my_data);
			pthread_join(temporary, NULL);

			end_clock = clock();
			logTime(time_taken(start_clock, end_clock), " - Process 1: end projector output\n", log_out, log_to);
			pcb->processState = PCB_RUNNING;
			pcb->processState = PCB_EXIT;
		}
	}

		temp = temp->next;
	}

	return;
}

/**
	Returns how much time something took

	@params clock_t start_clock, clock_t end_clock
	@return double
*/
double time_taken(clock_t start_clock, clock_t end_clock)
{
	return (end_clock - start_clock) / (double) CLOCKS_PER_SEC;
}

/**
	Timer

	@params double run_time
	@return void
*/
void RunTillDone(double run_time)
{
	run_time /= 1000;
	clock_t starting = clock();

	clock_t finish = clock();

	double time_gone = (finish - starting) / (double)CLOCKS_PER_SEC;
	while ( time_gone < run_time)
	{
		finish = clock();
		time_gone = (finish - starting) / (double)CLOCKS_PER_SEC;
	}

	return;
}

/**
	Timer simulating an I/O device

	@params void* my_data
	@return void
*/
void *SimulateIO(void* my_data)
{
	thread_data* data = (thread_data *) my_data;

	long double time_to_run = ((double)data->cycle_time * (double)data->amount_cycles)/(double)1000;

	timer_set = time_to_run;

	wait();

	pthread_exit(0);
}

/**
	Outputs the time taken for each process to montor and/or logfile depending on
		log_out

	@params data_double, data, log_out, log_to
	@return void
*/
void logTime(double data_double, std::string data, LogFile* log_out, int log_to)
{
	if(log_to == 0 || log_to == 2)
	{
		log_out->m_out_file << std::fixed << std::setprecision(6);
		log_out->LogDouble(data_double);
		log_out->LogString(data);
	}
	if(log_to == 0 || log_to == 1)
	{
		std::cout << std::fixed << std::setprecision(6);
		std::cout << data_double << data;
	}

	return;
}

/**
	Timer that is 'activated' whenever the global variable 'timer_set' != 0

	@params void*
	@return void*
*/
void *Timer_Thread(void*)
{
	while(true)
	{
		if(timer_set != 0)
		{
			clock_t start = clock();
			clock_t end = clock();
			// std::cout << timer_set << ' ' << ((end-start)/(double)1000) << std::endl;
			double time_elapsed = (double)((end-start)/(double)CLOCKS_PER_SEC);
			// std::cout << timer_set << " - " << time_elapsed << " = " <<  timer_set - time_elapsed << std::endl;
			while(timer_set - time_elapsed > 0)
			{
				time_elapsed = (((end-start)/(double)CLOCKS_PER_SEC));
				// std::cout << timer_set << ' ' << ((end-start)/(double)CLOCKS_PER_SEC) << std::endl;
				end = clock();
			}
			timer_set = 0;
		}
	}

	pthread_exit(0);
}

/**
	Waits to return until timer_set is 0

	@params void
	@return void
*/
void wait()
{
	clock_t start, end;
	start = clock();
	end = clock();
	while(timer_set != 0)
	{
		start = clock();
		end = clock();
		while(((end - start)/(double)CLOCKS_PER_SEC) < 0.100)
		{
			// std::cout << (end-start)/(double)CLOCKS_PER_SEC << std::endl;
			end = clock();
		}
	}
		// std::cout << "Timer_set = " << timer_set << std::endl;

	return;
}

/**
	Returns a random number

	@params void
	@return int
*/
int GetRandomInt()
{
	srand(time(NULL));

	return (rand() % 100 + 1);
}

/**
	Logs the objects of MetaData and Configuration to a logfile

	@params void
	@return void
*/
void LogFiles(MetaData meta_data, Configuration config_file, LogFile* log_out)
{
	log_out->LogString("Configuration File Data\n");
	log_out->LogString("Monitor = ");
	log_out->LogInt(config_file.GetMonitorCycle());
	log_out->LogString(" ms/cycle");
	log_out->LogChar('\n');
	log_out->LogString("Processor = ");
	log_out->LogInt(config_file.GetProcessorCycle());
	log_out->LogString(" ms/cycle");
	log_out->LogChar('\n');
	log_out->LogString("Scanner = ");
	log_out->LogInt(config_file.GetScannerCycle());
	log_out->LogString(" ms/cycle");
	log_out->LogChar('\n');
	log_out->LogString("Hard Drive = ");
	log_out->LogInt(config_file.GetHardDriveCycle());
	log_out->LogString(" ms/cycle");
	log_out->LogChar('\n');
	log_out->LogString("Keyboard = ");
	log_out->LogInt(config_file.GetKeyboardCycle());
	log_out->LogString(" ms/cycle");
	log_out->LogChar('\n');
	log_out->LogString("Memory = ");
	log_out->LogInt(config_file.GetMemoryCycle());
	log_out->LogString(" ms/cycle");
	log_out->LogChar('\n');
	log_out->LogString("Projector = ");
	log_out->LogInt(config_file.GetProjectorCycle());
	log_out->LogString(" ms/cycle");
	log_out->LogChar('\n');
	log_out->LogString("System memory: ");
	log_out->LogInt(config_file.GetSystemMemory());
	log_out->LogString(" kbytes");
  log_out->LogChar('\n');
  log_out->LogString("Projector quantity: ");
  log_out->LogInt(config_file.GetProjectorQuantity());
  log_out->LogString("\n\n");

	//Logs the meta_data;
	node* temp = meta_data.data.head;
	log_out->LogString("Meta-Data Metrics\n");
	while(temp != NULL)
	{
		log_out->LogChar(temp->data_code);
		log_out->LogChar('{');
		log_out->LogString(temp->data_descriptor);
		log_out->LogChar('}');
		log_out->LogInt(temp->number_of_cycles);
		log_out->LogChar('\n');

		temp = temp->next;
	}
	log_out->LogString("\n\n");
}
