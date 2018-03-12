CC=g++
CFLAGS=-I.
DEP= configuration.h log.h metadata.h linkedlist.h thread.h pcb.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

sim02: main.o
	g++ -o sim02 main.o configuration.cpp log.cpp metadata.cpp linkedlist.cpp -lpthread -I.
