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
uint32_t fakeid[2],id;
int status = 0,err = 0;
int main(){
	freopen("4.txt","r",stdin);
	freopen("4.out","w",stdout);
	fakeid[0] = rand();
	fakeid[1] = rand();

	while (fgets(str,N,stdin)){
		char* index;
		if (strstr(str, head)){
			status = 1;
			continue;		
		}

		if (status == 0) continue;

		if (status == 1 && (index = strstr(str, "FTP  "))){			
			if (strstr(str, "RETR")) id = 0, err++;
			else id = 1;
			status = 2;
			continue;
		}
		
		if (status == 1) continue;

		if (index = strstr(str, ipv4)){
			index += strlen(ipv4);
			sscanf(index,"%s",srcIP);
			srcIP[strlen(srcIP)-1] = 0;
			index = strstr(index, "Dst: ");
			index += strlen("Dst: ");
			sscanf(index,"%s",dstIP);
			status = 3;
			continue;
		}
		if (status == 2) continue;


		if (index = strstr(str, tcp)){
			index += strlen(tcp);
			sscanf(index,"%d",&srcPort);
			index = strstr(index, "Dst Port: ");
			index += strlen("Dst Port: ");
			sscanf(index,"%d",&dstPort);			
			status = 4;
			continue;
		}
		if (status == 3) continue;
		printf("%s %s %u %u %u\n",srcIP,dstIP,srcPort,dstPort,fakeid[id]);
		status = 0;
	}
fprintf(stderr, "%d\n",err);
	return 0;
}
