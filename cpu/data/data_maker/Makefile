all: prog filemaker test test2

prog: data.cpp myftp.h myftp.cpp
	g++ -o prog data.cpp myftp.h myftp.cpp -lpthread

filemaker: filemaker.cpp
	g++ -o filemaker filemaker.cpp

test: test.cpp myftp.h myftp.cpp
	g++ -o a test.cpp myftp.h myftp.cpp -lpthread


test2: test2.cpp myftp.h myftp.cpp
	g++ -o test2 test2.cpp myftp.h myftp.cpp -lpthread
