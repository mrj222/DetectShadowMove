#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "TestTool.h"
#include "doNothing.h"


static const int N = 101000;

char name[N] = "7.out";
uint32_t siz = 1024;
void Help(){
	printf("-h\t: help\n");
	printf("-f <filename>\t: input filename\n");
	printf("-s\t: size of hash pool\n");
}
int main(int argc, char** argv){
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
			if (i == argc-1) {printf("need argument\n"); return -1;}
			sscanf(argv[i+1],"%u",&siz);		
		}
	}
	myTest test(siz);
	test.Fopen(name);
	test.Run(); 
	test.Print();
	return 0;
}
