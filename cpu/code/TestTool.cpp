#include <iostream>
#include <ctime>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "TestTool.h"


static const int N = 30;

myTest::myTest(int n){
	apt = new DetectAPT(n);
	total = 0;
	hashErr = 0;
	pidErr = 0;
	file = stdin;
}

myTest::~myTest(){
	if (file != stdin) fclose(file);
	if (apt) delete apt;
}


void myTest::Reset(){
	total = 0;
	hashErr = 0;
	pidErr = 0;	
	file = stdin;
}

void myTest::Rebuild(int n){
	if (apt) delete apt;
	apt = new DetectAPT(n);
	total = 0;
	hashErr = 0;
	pidErr = 0;
	file = stdin;
}

int myTest::Fopen(const char* name){
	if (file != stdin) fclose(file);
	file = fopen(name, "r");
	return file == NULL ? -1 : 0;
}

void myTest::Run(){

	char src[N],dst[N];
	uint32_t srcPort,dstPort,srcPid;
	
	while (~fscanf(file, "%s %u %s %u %u", src, &srcPort,
		dst, &dstPort, &srcPid)){
		total++;
		uint32_t srcIP = inet_addr(src);
		uint32_t dstIP = inet_addr(dst);
		packet pkt(srcIP, dstIP, srcPort, dstPort, 6, srcPid);
		ErrorType err = apt->detect(pkt);
		switch (err){
			case NO_ERROR: 
				break;
			case PROC_ID_CONFLICT: 
				pidErr++;
				break;
			case HASH_COLLISION: 
				hashErr++;
				break;
			default:				
				break;
		}
	}

}

void myTest::Print(){
	printf("toal: %d, hashErr: %d, pidErr: %d\n",total, hashErr, pidErr);
}
