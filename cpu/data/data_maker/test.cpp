#include "myftp.h"
#include <cstdlib>
#include <cstdio>
#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <iostream>
const int N = 101000;


char fileName[200] = "test/file000.out";
char randName[200] = "test/file00000.out";
char FTPIPAddress[N], strUserName[N], strPassword[N];
pthread_mutex_t mylock;
int cnt; 
int main(){
	pthread_mutex_init(&mylock, NULL);
	FTPClient CFTPClinet;
	
	fprintf(stdout, "FTp addr:");
	fscanf(stdin, "%s",FTPIPAddress);
	fprintf(stdout, "Username:");
	fscanf(stdin, "%s",strUserName);
	fprintf(stdout, "Password:");
	fscanf(stdin, "%s",strPassword);

	int fd = CFTPClinet.ftp_connect(FTPIPAddress, 21, strUserName, strPassword);

	if (fd < 0){
		fprintf(stdout, "ftp connect falied\n");
	}
	int pid = fork();
	if (pid){

		int u = getpid();
		for (int i = 13;i >= 9;i--){
			randName[i] = '0' + u % 10;
			u /= 10;
		}
		while (~waitpid(-1,NULL,0));

		for (int i = 0;i < 10000;i++){
			uint64_t len,x;
			if (x = rand()&1) CFTPClinet.ftp_retrfile(fd, fileName, randName, &len, NULL);
			else CFTPClinet.ftp_storfile(fd, randName, fileName, &len, NULL);
			printf("%s %d \n",randName,x);
			
		}

		while (~waitpid(-1,NULL,0));	
		CFTPClinet.ftp_quit(fd);
	}
	else{
		int u = getpid();
		for (int i = 13;i >= 9;i--){
			randName[i] = '0' + u % 10;
			u /= 10;
		}
		for (int i = 0;i < 100;i++){
			uint64_t len,x;
			if (x = rand()&1) CFTPClinet.ftp_retrfile(fd, fileName, randName, &len, NULL);
			else CFTPClinet.ftp_storfile(fd, randName, fileName, &len, NULL);
			printf("%s %d\n",randName,x);
		}
	}

	
	return 0;
}
