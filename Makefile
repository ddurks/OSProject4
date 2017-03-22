all: Config.o getinmemory.o parser.o main.o
	g++ -std=gnu++11 -lcurl -o tester parser.o Config.o main.o getinmemory.o

main.o: main.cpp getinmemory.o
	g++ -std=gnu++11 -c main.cpp

Config.o: Config.cpp Config.h
	g++ -std=gnu++11 -c Config.cpp

getinmemory.o: getinmemory.c getinmemory.h
	g++ -lcurl -c getinmemory.c

parser.o: parser.cpp parser.h
	g++ -std=gnu++11 -c parser.cpp
