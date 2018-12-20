# Simulated Operating System

## Description
Simulation of a simple operating system, originally created for CS 446 (Operating Systems) at the University of Nevada Reno. It simulates the time required (in real-time) to complete tasks read into it from the metadata file. This simulation takes advantage of pthread to allow for certain pieces of simulated hardware and the timer to run alongside each other.

## Requirements
```
C++, Pthread
Tested on both Ubuntu 16.04 and MacOS
```

## How to Run
Run 'make' in the same directory as the files. After being made, when running the program include the configuration file name as the only argument.
```
make
./sim02 config_2.conf
```

In order to run, make sure to have a correct configuration file and metadata file. Use the included config_2.conf as an example configuration file and Test_2e.mdf as an example metadata file. The metadata file can be of any name, as long as the name is specified in the configuration file, as shown in the example file. The configuration file can also be of any name as long as the name is correctly specified as an argument when starting the program.
