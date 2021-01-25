#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 101000;

char head[N] = "No.     Time           Source  ";
char ipv4[N] = "Internet Protocol Version 4, Src: ";
char tcp[N] = "Transmission Control Protocol, Src Port: ";
char str[N];
char srcIP[N],dstIP[N];
uint32_t srcPort,dstPort;
int status = 0;
int main(){
	freopen("3.txt","r",stdin);
	freopen("3.out","w",stdout);
	uint32_t fakeid1 = rand(), fakeid2 = rand();
	while (fgets(str,N,stdin)){
		char* index;
		if (strstr(str, head)){
			status = 1;
			continue;		
		}
		if (status == 0) continue;

		if (index = strstr(str, ipv4)){
			index += strlen(ipv4);
			sscanf(index,"%s",srcIP);
			srcIP[strlen(srcIP)-1] = 0;
			index = strstr(index, "Dst: ");
			index += strlen("Dst: ");
			sscanf(index,"%s",dstIP);
			status = 2;
		}
		if (status != 2) continue;

		if (index = strstr(str, tcp)){
			index += strlen(tcp);
			sscanf(index,"%d",&srcPort);
			index = strstr(index, "Dst Port: ");
			index += strlen("Dst Port: ");
			sscanf(index,"%d",&dstPort);			
			status = 3;
		}
		if (status != 3) continue;
		printf("%s %s %u %u %u\n",srcIP,dstIP,srcPort,dstPort,fakeid1,fakeid2);
		status = 0;
	}
	return 0;
}
