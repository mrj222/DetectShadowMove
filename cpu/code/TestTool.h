#ifndef __TestTool_h__
#define __TestTool_h__

#include "detect.h"
#include <map>
#include <iostream>
#include <ctime>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>

//#define DEBUG

class myTest{
public:
	myTest(int n = 1024);
	~myTest();
	void Run();
	void RunK(int k);
	void Reset();
	void Rebuild(int n = 1024);
	int Fopen(const char*);
	void Print();
private:
	std::map<std::string, uint32_t> mp;
	DetectAPT* apt;
	uint32_t total, hashErr, pidErr, realErr, fp;
	FILE* file;
};


myTest::myTest(int n){
	apt = new DetectAPT(n);
	total = 0;
	hashErr = 0;
	pidErr = 0;
	realErr = 0;
	fp = 0;
	mp.clear();
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
	realErr = 0;
	fp = 0;
	mp.clear();
	if (file != stdin) fclose(file);	
	file = stdin;
}

void myTest::Rebuild(int n){
	if (apt) delete apt;
	apt = new DetectAPT(n);
	total = 0;
	hashErr = 0;
	pidErr = 0;
	realErr = 0;
	fp = 0;
	mp.clear();
	if (file != stdin) fclose(file);
	file = stdin;
}

int myTest::Fopen(const char* name){
	if (file != stdin) fclose(file);
	file = fopen(name, "r");
	return file == NULL ? -1 : 0;
}

void myTest::Run(){
	int N = 30;
	char src[N],dst[N];
	uint32_t srcPort,dstPort,srcPid;
	int cnt = 0;
	while (~fscanf(file, "%s %u %s %u %u", src, &srcPort,
		dst, &dstPort, &srcPid)){

		bool real = false;
		std::string ss = "";
		for (int i = 0;i < strlen(src);i++) 
			ss += src[i];
		ss += ' ';
		for (int i = 0;i < strlen(dst);i++) 
			ss += dst[i];
		ss += ' ';
		ss += std::to_string(srcPort);
		ss += ' ';
		ss += std::to_string(dstPort);
		if (mp.find(ss) == mp.end()){
			mp[ss] = srcPid;
		}
		else{
			if (mp[ss] != srcPid) {
/*
192.168.75.132 58784 121.36.6.255 16246
121.36.6.255 192.168.75.132 52842 47618 
*/
				realErr++;
				real = true;
			}
		}


		total++;
		uint32_t srcIP = inet_addr(src);
		uint32_t dstIP = inet_addr(dst);
		packet pkt(srcIP, dstIP, srcPort, dstPort, 6, srcPid);

		ErrorType err = apt->detect(pkt);

		switch (err){
			case NO_ERROR: 
#ifdef DEBUG
		if (apt->compute_bucket_key(pkt) == 8420209){
				printf("fingprint: %u\n",apt->compute_fingprint(pkt) );
				printf("bucket_key: %u\n",apt->compute_bucket_key(pkt) );
				printf("%u %u %u %u\n", srcIP, dstIP, srcPort, dstPort );
				printf("%s %u %s %u %u\n", src,srcPort,dst,dstPort,srcPid);
		}
#endif
				break;
			case PROC_ID_CONFLICT:
#ifdef DEBUG

		if (apt->compute_bucket_key(pkt) == 8420209){
				printf("fingprint: %u\n",apt->compute_fingprint(pkt) );
				printf("bucket_key: %u\n",apt->compute_bucket_key(pkt) );
				printf("%u %u %u %u\n", srcIP, dstIP, srcPort, dstPort );
				printf("%s %u %s %u %u\n", src,srcPort,dst,dstPort,srcPid);
		}

#endif
				pidErr++;
				if (!real) fp++;
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
//	printf("toal: %d, hashErr: %d, pidErr: %d\n",total, hashErr, pidErr);
	printf("%d %d %d %d %d\n",total, hashErr, pidErr, realErr, fp);
}

void myTest::RunK(int k){
	int N = 30;
	char src[N],dst[N];
	uint32_t srcPort,dstPort,srcPid;
	int cnt = 0,tot = k;
	while (~fscanf(file, "%s %u %s %u %u", src, &srcPort,
		dst, &dstPort, &srcPid)){

		bool real = false;
		std::string ss = "";
		for (int i = 0;i < strlen(src);i++) 
			ss += src[i];
		ss += ' ';
		for (int i = 0;i < strlen(dst);i++) 
			ss += dst[i];
		ss += ' ';
		ss += std::to_string(srcPort);
		ss += ' ';
		ss += std::to_string(dstPort);
		if (mp.find(ss) == mp.end()){
			mp[ss] = srcPid;
		}
		else{
			if (mp[ss] != srcPid) {
/*
192.168.75.132 58784 121.36.6.255 16246
121.36.6.255 192.168.75.132 52842 47618 
*/
				realErr++;
				real = true;
			}
		}


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
				if (!real) fp++;
				break;
			case HASH_COLLISION: 
				hashErr++;
				break;
			default:				
				break;
		}
		Print();
		if (--tot);else break;
	}
}

#endif
