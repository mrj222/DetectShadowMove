#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cstring>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

using namespace std;

const int N = 10100;

char srcIP[N], dstIP[N];
uint32_t srcPort,dstPort,srcPid;
void change(char* str){
	uint32_t strIP = inet_addr(str);
	uint32_t old = strIP;
	strIP <<= 16;
	strIP >>= 16;
	strIP |= rand()<<16;
	struct in_addr ia;
	ia.s_addr = strIP;
	const char *buf = inet_ntoa(ia);
//	fprintf(stderr, "old: %s\n", str);
	strcpy(str, buf);
//	fprintf(stderr, "new: %s\n", str);
}
void change(uint32_t &val){
	if (rand()%10 == 0) val = rand()%65536;
}
bool fake(){
	return rand()%20 == 0;
}
int main(int argc, char** argv){
	srand(time(NULL));
	freopen("7c.out","r",stdin);
	freopen("7d.out","w",stdout);
	while (~scanf("%s%u%s%u%u", srcIP, &srcPort, dstIP, &dstPort, &srcPid)){
		printf("%s %u %s %u %u\n",srcIP, srcPort, dstIP, dstPort , srcPid);
		if (fake()) {	
			srcPid = rand() % 65536;
		printf("%s %u %s %u %u\n",srcIP, srcPort, dstIP, dstPort , srcPid);
		}
	}
	return 0;
}
