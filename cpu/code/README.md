## Introduction

* `BOBHash32.h, detect.h, doNothing.h`: the detecting algorithm
* `hash.cpp `: evaluate the hash function with random data.
* `pid.cpp`: evaluate the process id reuse algorithm with random data.
* `TestTool.h, TestTool.cpp`: tools of evaluation. 
* `offlineCount.cpp`: calculate the exact result of input data, use map instead of hash(without limitation of memory)
* `test0.cpp, test1.cpp, test2.cpp`: evaluate the data and output the result.



## Usage

use

```makefile
make test0
make test1
make test3
```

to compile the testing programs, or

```makefile
make
```

to build all.

for each testing, use

```bash
./test* -h
```

for help. 

* `test0`: calculate the real pid reuse, total collision, detected pid reuse with fix window(hash factor).
* `test1`: calculate the real pid reuse, total collision, detected pid reuse , with changing window from L to R.
* `test3`: calculate the real pid reuse, total collision, detected pid reuse, output for each entry coming in. 

to use these programs, you need to put the input data file in the same directory with them.

