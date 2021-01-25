all: test0 test1 test3 remake remake2 remake3 offlineCount

hash: hash.cpp BOBHash32.h detect.h packet.h
	g++ -o hash hash.cpp BOBHash32.h detect.h packet.h

pid: pid.cpp BOBHash32.h detect.h packet.h
	g++ -o pid pid.cpp BOBHash32.h detect.h packet.h

test: test.cpp BOBHash32.h detect.h packet.h
	g++ -o test test.cpp BOBHash32.h detect.h packet.h

test0: test0.cpp TestTool.h TestTool.cpp BOBHash32.h detect.h packet.h doNothing.h
	g++ -o test0 test0.cpp

remake: remake.cpp
	g++ -o remake remake.cpp

test1: test1.cpp TestTool.h TestTool.cpp BOBHash32.h detect.h packet.h doNothing.h
	g++ -o test1 test1.cpp

test3: test3.cpp TestTool.h TestTool.cpp BOBHash32.h detect.h packet.h doNothing.h
	g++ -o test3 test3.cpp

remake2: remake2.cpp
	g++ -o remake2 remake2.cpp

remake3: remake3.cpp
	g++ -o remake3 remake3.cpp

testtest: test0.cpp TestTool.h TestTool.cpp BOBHash32.h detect.h packet.h doNothing.h
	g++ -o testtest test0.cpp TestTool.cpp

offlineCount: offlineCount.cpp
	g++ -o offlineCount offlineCount.cpp

clean:
	rm test0 hash pid test test1 test3 remake remake2 remake3 offlineCount
