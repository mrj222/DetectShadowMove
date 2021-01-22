#include "pnet.h"
#include <linux/sched.h>

/*************************************/
/*********** SEND FUNCTION ***********/
/*************************************/

static struct net_device *pnet_dev;
static struct net_device *real_dev;
static inline struct sk_buff *pnet_put_hdr(struct sk_buff *skb) {
    uint16_t proto;
    struct pid_ethhdr_t *peth_hdr;
    if (skb_cow_head(skb, PNET_LEN) < 0) {
        kfree_skb(skb);
        return NULL;
    }

    peth_hdr = (struct pid_ethhdr_t *)skb_push(skb, PNET_LEN);
    proto = *((uint16_t *)(skb->data + PNET_LEN + 12));
    memmove(skb->data, skb->data + PNET_LEN, 12);
    memset(skb->data + ETH_HLEN, 0, PNET_LEN);
    skb->mac_header -= PNET_LEN;
    peth_hdr->ether_proto = htons(ETH_P_PNET); 
    peth_hdr->pnet_proto = proto;
    peth_hdr->pid = (uint32_t)task_pid_nr(current);
    skb->protocol = htons(ETH_P_PNET);
    return skb;
}

static int pnet_dev_init(struct net_device *dev){
    if(is_zero_ether_addr(dev->dev_addr)){
        memcpy(dev->dev_addr, real_dev->dev_addr, dev->addr_len);
    }
    if(is_zero_ether_addr(dev->broadcast)){
        memcpy(dev->broadcast, real_dev->broadcast, dev->addr_len);
    }
    return 0;
}

static int pnet_dev_hard_xmit(struct sk_buff *skb, struct net_device *dev){
    int ret;
    struct pid_ethhdr_t *peth_hdr = (struct pid_ethhdr_t *)(skb->data);
    struct iphdr *ip_hdr;
    ip_hdr = (struct iphdr *)((void*)skb->data + ETH_HLEN);
    //printk(KERN_INFO"src: %u.%u.%u.%u\n", NIPQUAD(ip_hdr->saddr));
    //printk(KERN_INFO"dst: %u.%u.%u.%u\n", NIPQUAD(ip_hdr->daddr));
    if(peth_hdr->ether_proto != (ETH_P_PNET)){
	skb = pnet_put_hdr(skb);
	if(!skb){
	    return NETDEV_TX_BUSY;
	}
    }
    ip_hdr = (struct iphdr *)((void*)skb->data + PNET_LEN + ETH_HLEN);
    //printk(KERN_INFO"src: %u.%u.%u.%u\n", NIPQUAD(ip_hdr->saddr));
    //printk(KERN_INFO"dst: %u.%u.%u.%u\n", NIPQUAD(ip_hdr->daddr));
    dev->stats.tx_packets++;
    dev->stats.tx_bytes += skb->len;
    skb->dev = real_dev;
    ret = dev_queue_xmit(skb);
    return ret;
}

static struct net_device_ops pnet_ops = {
    .ndo_start_xmit = pnet_dev_hard_xmit,
    .ndo_init = pnet_dev_init,
};

/*************************************/
/*********** RECV FUNCTION ***********/
/*************************************/

/* recv function */
static inline struct sk_buff *pnet_check_reorder_header(struct sk_buff *skb){
    struct pid_ethhdr_t *peth_hdr;
    if(skb_cow(skb, skb_headroom(skb)) < 0){
        skb = NULL;
    }
    if(skb){
    	peth_hdr = (struct pid_ethhdr_t *)(skb->data - ETH_HLEN - PNET_LEN);
    	peth_hdr->ether_proto = peth_hdr->pnet_proto;
        memmove(skb->data - ETH_HLEN,
                skb->data - ETH_HLEN - PNET_LEN, ETH_HLEN);
        skb->mac_header += PNET_LEN;
    }
    return skb;
}
int pnet_skb_recv(struct sk_buff *skb, struct net_device *dev, 
        struct packet_type *ptype, struct net_device *orig_dev){
    struct pid_hdr_t *p_hdr;
    skb = skb_share_check(skb, GFP_ATOMIC);
    if(!skb){
        goto err_free;
    }
    dev->stats.rx_packets++;
    dev->stats.rx_bytes += skb->len;
    //printk(KERN_INFO"INT!\n");
    //int_dev->stats.rx_packets++;
    //int_dev->stats.rx_bytes += skb->len;
    
    printk(KERN_INFO"RECIEVE PNET\n");
    //rcu_read_lock();
    // update rx stats
    pskb_may_pull(skb, PNET_LEN);
    p_hdr = (struct pid_hdr_t *)skb->data;
    skb_pull(skb, PNET_LEN);
    skb->protocol = p_hdr->proto;
    skb = pnet_check_reorder_header(skb);
    if(!skb){
        goto err_unlock;
    }
    netif_rx(skb);
    //rcu_read_unlock();    
    return NET_RX_SUCCESS;
err_unlock:
    //rcu_read_unlock();
err_free:
    kfree_skb(skb);
    return NET_RX_DROP;
}

/*************************************/
/*********** KERN FUNCTION ***********/
/*************************************/

/* linux kernel function */
static struct packet_type pnet_packet_type __read_mostly = {
    .type = cpu_to_be16(ETH_P_PNET),
    .func = pnet_skb_recv,
};
static int __init pnet_module_init(void){
    dev_add_pack(&pnet_packet_type);
    printk(KERN_INFO"pnet_hdr_length %ld\n", sizeof(struct pid_hdr_t));
    printk(KERN_ERR "%s,%d\n", __FUNCTION__, __LINE__);
    real_dev = __dev_get_by_name(&init_net, "veth1-2");
    pnet_dev = alloc_netdev(0, "pneteth%d", NET_NAME_UNKNOWN, ether_setup);
    pnet_dev -> netdev_ops = &pnet_ops;
    register_netdev(pnet_dev);
    return 0;
}
static void pnet_module_cleanup(void){
    unregister_netdev(pnet_dev);
    free_netdev(pnet_dev);
    dev_remove_pack(&pnet_packet_type);
}

/* module operation */
module_init(pnet_module_init);
module_exit(pnet_module_cleanup);
MODULE_LICENSE("GPL");
MODULE_VERSION("beta v0.1");
MODULE_DESCRIPTION("handler for Pid in packet header");