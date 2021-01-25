#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "TestTool.h"
#include "doNothing.h"


static const int N = 101000;

char name[N] = "7.out";
uint32_t L = 1024, R = 2048;
uint32_t interval = 1;
void Help(){
//run for different size of hash buffer
	printf("-h\t: help\n");
	printf("-f <filename>\t: input filename\n");
	printf("-s <L> <R>\t: range for size\n");
	printf("-interval <value>\t: value of each step\n");
}
int main(int argc, char** argv){
//freopen("f4.txt","w",stdout);
	for (int i = 1;i < argc;i++){
		if (!strcmp(argv[i], "-h")){
			Help();			
			return 0;	
		}	
	}
	for (int i = 1;i < argc;i++){
		if (!strcmp(argv[i], "-f")){
			if (i == argc-1) {printf("need argument\n"); return -1;}
			sscanf(argv[i+1],"%s",name);
		}	
		if (!strcmp(argv[i], "-s")){
			if (i+2 >= argc) {printf("need argument\n"); return -1;}
			sscanf(argv[i+1],"%u",&L);
			sscanf(argv[i+2],"%u",&R);
		}
		if (!strcmp(argv[i], "-interval")){
			if (i == argc-1) {printf("need argument\n"); return -1;}
			sscanf(argv[i+1],"%u",&interval);
		}
	}
//	myTest test(L);
	for (int i = L;i < R;i+= interval ){
			fprintf(stderr,"%d\n",i);
		myTest test(i);
		test.Fopen(name);
		test.Run(); 
		test.Print();
	}
	return 0;
}
