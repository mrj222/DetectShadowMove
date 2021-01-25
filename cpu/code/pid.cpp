#include <iostream>
#include <ctime>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "BOBHash32.h"
#include "detect.h"
#include "packet.h"

static const int N = 200, M = 800;
/*
enum ErrorType { NO_ERROR, PROC_ID_CONFLICT, HASH_COLLISION };
*/

inline bool fake(){
	int u = rand()%100;
	return u == 0;
}

uint32_t src[N], port[N], id[N];
int main(){
	static int procid = 0, hash = 0;
	srand(time(NULL));
	DetectAPT* apt = new DetectAPT(1024);

	uint32_t mask = ~0;
	mask <<= 5;

	uint32_t net = rand();

	for (int i = 0;i < N;i++){
		int pid = rand()%65536+1;
		if (pid){
			uint32_t srcIP, dstIP;
			srcIP = rand();
//			srcIP = (net&mask) | (rand()&~mask);
//			dstIP = (net&mask) | (rand()&~mask);
			dstIP = net;
			int temp = rand()%65536;
			packet pkt(srcIP, dstIP, temp, 21, 6, pid);
			src[i] = srcIP;
			port[i] = temp;
			id[i] = pid;
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
			if (err == PROC_ID_CONFLICT){
				int val = apt->compute_bucket_key(pkt);
				for (int j = 0;j < i;j++) {
					packet old(src[j],net,port[j],21,6,id[j]);
					int tmp = apt->compute_bucket_key(old);
					if (val == tmp) {
						printf("%d %d %d\n",src[j],port[j],id[j]);
						printf("%d %d %d\n\n",src[i],port[i],id[i]);
					}
				}
			}
		}
		else{
			return 0;
		}		
	}
	printf("%d %d\n",procid, hash);
	while (~waitpid(-1, NULL, WUNTRACED));


	for (int i = 0;i < N;i++) 
		for (int j = 0;j < i;j++){
			if (src[i] == src[j] && port[i] == port[j]){
				printf("%d %d %d %d\n",i,j,id[i],id[j]);		
			}		
		}
printf("pass\n");

	int attack = 0;
	for (int i = 0;i < M;i++){
		int pid = rand()%65536+1;
		if (pid){
			if (fake()){
				int index = rand()%N;
//				printf("fake %d\n",index);
//				if (pid != id[index]) 
					attack++;				
				packet pkt(src[index], net, port[index], 21, 6, pid);
				ErrorType err = apt->detect(pkt);		
				if (err != PROC_ID_CONFLICT)	
					printf("%d %d %d %d %d %d\n",index,src[index], port[index], id[index], pid, err);
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
			else{
				int index = rand()%N;
				packet pkt(src[index], net, port[index], 21, 6, id[index]);
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
		}
		else {
			return 0;
		}
	}
	while (~waitpid(-1, NULL, WUNTRACED));
	printf("%d %d %d\n",attack, procid, hash);
	delete apt;
	return 0;
}
