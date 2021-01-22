#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/if_ether.h>
#include <linux/if.h>
#include <linux/ip.h>

#define ETH_P_PNET 0x1000
#define PNET_LEN sizeof(struct pid_hdr_t)

struct pid_ethhdr_t {
    uint8_t ether_dst[ETH_ALEN];
    uint8_t ether_src[ETH_ALEN];
    uint16_t ether_proto;
    uint16_t pnet_proto;
    uint32_t pid;
};

struct pid_hdr_t {
    uint16_t proto;
    uint32_t pid;
};