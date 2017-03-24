all: clean Config.o getinmemory.o parser.o main.o
	g++ -std=gnu++11 -Wall -lcurl -lpthread -o site-tester parser.o Config.o main.o getinmemory.o

main.o: main.cpp getinmemory.o
	g++ -std=gnu++11 -Wall -c main.cpp

Config.o: Config.cpp Config.h
	g++ -std=gnu++11 -Wall -c Config.cpp

getinmemory.o: getinmemory.c getinmemory.h
	g++ -lcurl -Wall -Wno-write-strings -c getinmemory.c

parser.o: parser.cpp parser.h
	g++ -std=gnu++11 -Wall -c parser.cpp

clean:
	rm -rf *.o *.csv site-tester
