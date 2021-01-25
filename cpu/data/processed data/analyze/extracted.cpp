#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace std;

/*
No.     Time           Source                Destination           Protocol Length Info
      5 0.008108973    121.36.6.255          192.168.75.132        TCP      60     21 → 39398 [SYN, ACK] Seq=0 Ack=1 Win=64240 Len=0 MSS=1460

Frame 5: 60 bytes on wire (480 bits), 60 bytes captured (480 bits) on interface 0
Ethernet II, Src: Vmware_e1:04:02 (00:50:56:e1:04:02), Dst: Vmware_61:6e:0f (00:0c:29:61:6e:0f)
Internet Protocol Version 4, Src: 121.36.6.255, Dst: 192.168.75.132
Transmission Control Protocol, Src Port: 21, Dst Port: 39398, Seq: 0, Ack: 1, Len: 0
*/

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
	freopen("7.txt","r",stdin);
	freopen("7.out","w",stdout);
	//int cnt = 10;
	while (fgets(str,N,stdin)){
		char* index;
//		printf("%s\n",str);
		switch(status){
			case 0:
				if (index = strstr(str, head)){
					status++;
				}
				break;
			case 1:
				if (index = strstr(str, ipv4)){
					index += strlen(ipv4);
					sscanf(index,"%s",srcIP);
					srcIP[strlen(srcIP)-1] = 0;
					index = strstr(index, "Dst: ");
					index += strlen("Dst: ");
					sscanf(index,"%s",dstIP);
					status++;
				}
				break;
			case 2:
				if (index = strstr(str, tcp)){
					index += strlen(tcp);
					sscanf(index,"%d",&srcPort);
					index = strstr(index, "Dst Port: ");
					index += strlen("Dst Port: ");
					sscanf(index,"%d",&dstPort);
					status++;
				}
				break;
			case 3:
				status = 0;
				printf("%s %d %s %d\n", srcIP, srcPort, dstIP, dstPort);
				//if (cnt--); else return 0;
				break;
			default:
				break;
		}
	}
	return 0;
}
