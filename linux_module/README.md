## Environment

We load our kernel module and successfully send packets in Ubuntu14.04. 

For higher version of linux kernel, you should verify the target kernel module before loading it. For convenience, we only test the code in older version of linux kernel, which does not ask for  verification.

## Usage

#### Modify the code

Before run the code, you should modify the line 134 in `pnet.c`

```c
real_dev = __dev_get_by_name(&init_net, "eth0");
```

use real network device in your computer instead of "veth1-2".

#### Compile and load module

```shell
make
sudo insmod pnet.ko
```

If no error occurs, then type

```shell
lsmod | grep pnet
```

will show the loaded module.

#### Send packets

Check the name of the added network device

```
ifconfig -a
```

Activate the new network device

```shell
ifconfig pneteth0 up
```

Allocate IP address for network device

```shell
ifconfig pneteth0 "allocated IP address"
```

Now if you type `ifconfig`, you will see new device. Send packets!

```shell
ping -I pneteth0 www.baidu.com
```

Of course you cannot get feedback, because we use our new-defined ethernet header type. But after type `ctrl C` and `ifconfig`, you will find the TX of new device increase.