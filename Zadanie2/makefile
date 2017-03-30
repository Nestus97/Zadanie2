CC=g++

debug: CCFLAGS+=-g
debug: project

all: project

project: main.o class.o
	$(CC) $(CCFLAGS) main.o class.o -o Projekt1

main.o: main.cpp class.h
	$(CC) $(CCFLAGS) -c main.cpp

class.o: class.cpp class.h
	$(CC) $(CCFLAGS) -c class.cpp

clean:
	rm -rf *o Projekt1