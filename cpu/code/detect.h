#ifndef _DETECT_H_
#define _DETECT_H_

#include "packet.h"
#include "BOBHash32.h"
#include <cstring>

enum ErrorType { NO_ERROR, PROC_ID_CONFLICT, HASH_COLLISION };

class DetectAPT {
    int len;
    bool *existence;
    uint32_t *fingprint;
    ProcID *proc_id;

    BOBHash32 bucketHash, fingHash;

public:
    DetectAPT(int _len) {
        len = _len;
        existence = new bool[len];
        fingprint = new uint32_t[len];
        proc_id = new ProcID[len];
        memset(existence, 0, len);
/*
        for (int i= 0;i < len;i++) 
			if (existence[i] != 0) printf("%d\n",i);
*/
        bucketHash.initialize(200);
        fingHash.initialize(500);
    }

    ~DetectAPT() {
        delete[] existence;
        delete[] fingprint;
        delete[] proc_id;
    }

    int compute_bucket_key(packet &p) {
        char tuple[15] = { 0 };
        for (int i = 0; i < 4; ++i) {
            tuple[i] = (char)(p.srcIP >> (i<<3));
        }

        for (int i = 0; i < 4; ++i) {
            tuple[i + 4] = (char)(p.dstIP >> (i<<3));
        }

        for (int i = 0; i < 2; ++i) {
            tuple[i + 8] = (char)(p.srcPort >> (i<<3));
        }

        for (int i = 0; i < 2; ++i) {
            tuple[i + 10] = (char)(p.dstPort >> (i<<3));
        }
        
        tuple[12] = (char)(p.protocol);

        int pos = bucketHash.run(tuple, 13) % len;
        return pos;
    }

    uint32_t compute_fingprint(packet &p) {
        char tuple[15] = { 0 };
        for (int i = 0; i < 4; ++i) {
            tuple[i] = (char)(p.srcIP >> (i<<3));
        }

        for (int i = 0; i < 4; ++i) {
            tuple[i + 4] = (char)(p.dstIP >> (i<<3));
        }

        for (int i = 0; i < 2; ++i) {
            tuple[i + 8] = (char)(p.srcPort >> (i<<3));
        }

        for (int i = 0; i < 2; ++i) {
            tuple[i + 10] = (char)(p.dstPort >> (i<<3));
        }
        
        tuple[12] = (char)(p.protocol);

        return (uint32_t)fingHash.run(tuple, 13);
    }

    ErrorType detect(packet &p) {
        int bucket_key = compute_bucket_key(p);
        uint32_t fingprint_id = compute_fingprint(p);

        ErrorType ret = NO_ERROR;

        if (!existence[bucket_key]) {
            existence[bucket_key] = true;
            proc_id[bucket_key] = p.pid;
            fingprint[bucket_key] = fingprint_id;
        }
        else if (fingprint[bucket_key] != fingprint_id) {
            ret = HASH_COLLISION;
        }
        else if (proc_id[bucket_key] != p.pid) {
            ret = PROC_ID_CONFLICT;
        }

        return ret;
    }
};


#endif
