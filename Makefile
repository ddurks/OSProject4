all: Config.o
	g++ -std=gnu++11 Config.o -o tester

Config.o: Config.cpp Config.h
	g++ -std=gnu++11 -c Config.cpp
