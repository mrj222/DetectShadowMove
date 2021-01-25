#include <iostream>
#include <ctime>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "BOBHash32.h"
#include "detect.h"
#include "packet.h"

static const int N = 200, M = 800;
/*
enum ErrorType { NO_ERROR, PROC_ID_CONFLICT, HASH_COLLISION };
*/

char src[N],dst[N];
uint32_t srcPort,dstPort,srcPid,dstPid;

int main(){
//	freopen("3.out","r",stdin);
	static int procid = 0, hash = 0;
	DetectAPT* apt = new DetectAPT(1024);

	uint32_t sum = 0;
	
	while (~scanf("%s %s %u %u %u %u", src,dst,&srcPort,&dstPort,&srcPid,&dstPid)){
		sum++;
		uint32_t srcIP = inet_addr(src);
		uint32_t dstIP = inet_addr(dst);
		packet pkt(srcIP, dstIP, srcPort, dstPort, 6, srcPid);
		ErrorType err = apt->detect(pkt);
		switch (err){
			case NO_ERROR: 
				break;
			case PROC_ID_CONFLICT: 
				procid++;
				break;
			case HASH_COLLISION: 
				hash++;
				break;
			default:				
				break;
		}
	}	
	printf("%d %d %d\n",sum, procid, hash);
	return 0;
}
