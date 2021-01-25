#include "detect.h"
#include "packet.h"
#include <arpa/inet.h>

/*
3593610361 2638653632 21 52362
121.36.50.214 21 192.168.70.157 52362 20787
fingprint: 581673630
bucket_key: 8420209
3213173881 402565312 21 55946



fingprint: 581673630
bucket_key: 8420209
3593610361 2638653632 21 52362
121.36.50.214 21 192.168.70.157 52362 20787
fingprint: 581673630
bucket_key: 8420209
3213173881 402565312 21 55946
121.36.133.191 21 192.168.254.23 55946 20827


    packet(uint32_t _srcIP, uint32_t _dstIP, uint16_t _srcPort, uint16_t _dstPort, uint8_t _proto, ProcID _pid) {
*/
int main(){
	DetectAPT apt(10000000);
	uint32_t srcIP = inet_addr("121.36.50.214");
	uint32_t dstIP = inet_addr("192.168.70.157");
	uint16_t srcPort = 21;
	uint16_t dstPort = 52362;
	ProcID pid = 20787;

	packet pkt(srcIP, dstIP, srcPort, dstPort, 6, pid);
	printf("%d %u\n",apt.compute_bucket_key(pkt), apt.compute_fingprint(pkt));

	srcIP = inet_addr("121.36.133.191");
	dstIP = inet_addr("192.168.254.23");
	srcPort = 21;
	dstPort = 55946;
	pid = 20827;
	pkt = packet(srcIP, dstIP, srcPort, dstPort, 6, pid );
	printf("%d %u\n",apt.compute_bucket_key(pkt), apt.compute_fingprint(pkt));
	return 0;
}
