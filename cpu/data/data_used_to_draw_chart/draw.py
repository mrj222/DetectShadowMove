import matplotlib.pyplot as plt




a1 = []
b1 = []
c1 = []
e1 = []
i = 150000
with open("f1.txt") as f:
    for line in f:
        aa,bb,cc,dd = [int(x) for x in line.split()] # read first line
        a1.append(cc/dd)
        b1.append((bb+cc)/aa)
        c1.append(dd/(bb+cc))
        e1.append(i/aa)
        i += 50000

a2 = []
b2 = []
e2 = []
i = 150000
with open("f2.txt") as f:
    for line in f:
        aa,bb,cc,dd,ee = [int(x) for x in line.split()] # read first line
        #a2.append(cc/dd)
        b2.append((bb+cc)/aa)
        e2.append(i/aa)
        i += 100000

a3 = []
b3 = []
c3 = []
e3 = []
i = 150000
with open("f3.txt") as f:
    for line in f:
        aa,bb,cc,dd,ee = [int(x) for x in line.split()] # read first line
        a3.append(cc/dd)
        b3.append((bb+cc)/aa)
        c3.append(dd/(bb+cc))
        e3.append(i/aa)
        i += 100000

a4 = []
b4 = []
e4 = []
i = 150000
with open("f4.txt") as f:
    for line in f:
        aa,bb,cc,dd,ee = [int(x) for x in line.split()] # read first line
        #a4.append(cc/dd)
        b4.append((bb+cc)/aa)
        e4.append(i/aa)
        i += 100000


plt.xlabel("hash factor")
plt.ylabel("detect reuse")
plt.plot(e1, a1,label = 'many nodes',color='red',linewidth=2.0,linestyle='-')
#plt.plot(e2, a2,color='blue',linewidth=2.0,linestyle='-')
plt.plot(e3, a3,color='green',linewidth=2.0,linestyle='-',label = "2 nodes" )
#plt.plot(e4, a4,color='black',linewidth=2.0,linestyle='-')
plt.legend()
plt.show()


plt.xlabel("hash factor")
plt.ylabel("total collision")
plt.plot(e1, b1,color='red',linewidth=2.0,linestyle='-',label = "many nodes")
plt.plot(e2, b2,color='blue',linewidth=2.0,linestyle='-',label = "many nodes, no reuse")
plt.plot(e3, b3,color='green',linewidth=2.0,linestyle='-',label = "2 nodes")
plt.plot(e4, b4,color='black',linewidth=2.0,linestyle='-',label = "2 nodes, no reuse")
#plt.plot(e, c,color='black',linewidth=2.0,linestyle='-')
#plt.plot(e, d,color='black',linewidth=2.0,linestyle='-')
plt.legend()
plt.show()

plt.xlabel("hash factor")
plt.ylabel("reuse / total collision")
plt.plot(e1, c1,label = 'many nodes',color='red',linewidth=2.0,linestyle='-')
#plt.plot(e2, a2,color='blue',linewidth=2.0,linestyle='-')
plt.plot(e3, c3,color='green',linewidth=2.0,linestyle='-',label = "2 nodes" )
#plt.plot(e4, a4,color='black',linewidth=2.0,linestyle='-')
plt.legend()
plt.show()