#ifndef _PACKET_H_
#define _PACKET_H_

#include <cinttypes>

typedef uint32_t ProcID;

struct packet {
    uint32_t srcIP, dstIP;
    uint16_t srcPort, dstPort;
    uint8_t protocol;
    ProcID pid;

    packet(uint32_t _srcIP, uint32_t _dstIP, uint16_t _srcPort, uint16_t _dstPort, uint8_t _proto, ProcID _pid) {
        srcIP = _srcIP; 
        dstIP = _dstIP;
        srcPort = _srcPort;
        dstPort = _dstPort;
        protocol = _proto;
        pid = _pid;
    }
};

#endif