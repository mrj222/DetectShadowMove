import matplotlib.pyplot as plt





a1 = []
b1 = []
e1 = []
i = 1
with open("t1.txt") as f:
    for line in f:
        aa,bb,cc,dd,ee = [int(x) for x in line.split()] # read first line
        a1.append((cc+bb)/aa)
        if (dd != 0): 
            b1.append((cc/dd))
        else:
            b1.append(1)
        e1.append(i)

        i += 1

a2 = []
b2 = []
c2 = []
e2 = []
i = 1
with open("t2.txt") as f:
    for line in f:
        aa,bb,cc,dd,ee = [int(x) for x in line.split()] # read first line
        a2.append((cc+bb)/aa)
        if (dd != 0): 
            b2.append((cc/dd))
            c2.append(dd/(bb+cc))
        else:
            b2.append(1)
            c2.append(0)
        e2.append(i)

        i += 1

a3 = []
b3 = []
e3 = []
i = 1
with open("t3.txt") as f:
    for line in f:
        aa,bb,cc,dd,ee = [int(x) for x in line.split()] # read first line
        a3.append((cc+bb)/aa)
        if (dd != 0): 
            b3.append((cc/dd))
        else:
            b3.append(1)
        e3.append(i)

        i += 1

a4 = []
b4 = []
c4 = []
e4 = []
i = 1
with open("t4.txt") as f:
    for line in f:
        aa,bb,cc,dd,ee = [int(x) for x in line.split()] # read first line
        a4.append((cc+bb)/aa)
        if (dd != 0): 
            b4.append((cc/dd))
            c4.append(dd/(bb+cc))    
        else:
            b4.append(1)
            c4.append(1)
        e4.append(i)

        i += 1

plt.xlabel("throughput")
plt.ylabel("detect reuse")
#plt.plot(e1, b1,color='red',linewidth=2.0,linestyle='-',label = 'many nodes')
plt.plot(e4, b4,color='red',linewidth=2.0,linestyle='-',label = 'many nodes',)
#plt.plot(e3, b3,color='green',linewidth=2.0,linestyle='-',label = "2 nodes" )
plt.plot(e2, b2,color='green',linewidth=2.0,linestyle='-',label = "2 nodes")
plt.legend()
plt.show()

plt.xlabel("throughput")
plt.ylabel("total collision")
plt.plot(e3, a3,color='blue',linewidth=2.0,linestyle='-',label = "many nodes, no reuse")
plt.plot(e4, a4,color='red',linewidth=2.0,linestyle='-',label = "many nodes")
plt.plot(e1, a1,color='black',linewidth=2.0,linestyle='-',label = "2 nodes, no reuse")
plt.plot(e2, a2,color='green',linewidth=2.0,linestyle='-',label = "2 nodes")
#plt.plot(e, c,color='black',linewidth=2.0,linestyle='-')
#plt.plot(e, d,color='black',linewidth=2.0,linestyle='-')
plt.legend()
plt.show()

plt.xlabel("throughput")
plt.ylabel("reuse / total collision")
#plt.plot(e1, b1,color='red',linewidth=2.0,linestyle='-',label = 'many nodes')
plt.plot(e4, c4,color='red',linewidth=2.0,linestyle='-',label = 'many nodes',)
#plt.plot(e3, b3,color='green',linewidth=2.0,linestyle='-',label = "2 nodes" )
plt.plot(e2, c2,color='green',linewidth=2.0,linestyle='-',label = "2 nodes")
plt.legend()
plt.show()