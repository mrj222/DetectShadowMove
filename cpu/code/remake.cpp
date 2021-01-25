#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cstring>
#include <string>

using namespace std;

const int N = 10100;

char srcIP[N], dstIP[N];
uint32_t srcPort,dstPort;
uint32_t tempPort;
uint32_t reverse(uint32_t val){
	uint32_t ret = 0;
	for (int i = 0;i < 16;i++){
		ret = (ret<<1) | (val&1);
		val >>= 1;
	}

	return ret;
}
uint32_t gen(int argc, char** argv){
	if (argc <= 1) return 0;
	if (!strcmp(argv[1], "pid")){
		uint32_t ret;
		sscanf(argv[2], "%u", &ret);
		return ret;
	}  
	if (!strcmp(argv[1], "port")){
		if (srcPort == 21 || dstPort == 21){
			tempPort = srcPort + dstPort - 21;		
		}
		else tempPort = 0;
		return reverse(tempPort);
	}
	return 0;
}
int main(int argc, char** argv){

	freopen("7.out","r",stdin);
	freopen("7a.out","w",stdout);
	while (~scanf("%s%u%s%u", srcIP, &srcPort, dstIP, &dstPort)){
		uint32_t pid = gen(argc, argv); 
		printf("%s %u %s %u %u\n",srcIP, srcPort, dstIP, dstPort , pid);
	}
	return 0;
}
