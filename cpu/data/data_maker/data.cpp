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
char FTPIPAddress[N], strUserName[N], strPassword[N];
pthread_mutex_t mylock;
int cnt; 

void *func(void* arg){
	pthread_detach(pthread_self());
	std::pair<FTPClient*, int> *tmp = (std::pair<FTPClient*, int>*)arg;
	int fd = tmp->second;
	FTPClient *CFTPClinet = tmp->first;
	while (true){
		pthread_mutex_lock(&mylock);
		if (cnt >= 100) {
			pthread_mutex_unlock(&mylock);
			break;
		}	
		fileName[9] = '0' + cnt/100;
		fileName[10] = '0' + (cnt/10)%10;
		fileName[11] = '0' + cnt%10;
		uint64_t len = 0;	
		int ret;
		CFTPClinet->ftp_retrfile(fd, fileName, fileName, &len, NULL);

 		fprintf(stdout, "file len: %llu, ret = %d\n", len, ret);		
		cnt++;
		pthread_mutex_unlock(&mylock);
	}	
}
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
/*
	uint64_t len = 0;
	int ret = CFTPClinet.ftp_retrfile(fd, "test.cpp", "test.cpp", &len, NULL);
 	fprintf(stdout, "file len: %llu, ret = %d\n", len, ret);
*/
/*
	for (int i = 0;i < 100;i++){
		fileName[9] = '0' + i/100;
		fileName[10] = '0' + (i/10)%10;
		fileName[11] = '0' + i%10;
		uint64_t len = 0;	
		int ret = CFTPClinet.ftp_storfile(fd, fileName, fileName, &len, NULL);
 		fprintf(stdout, "file len: %llu, ret = %d\n", len, ret);
	}
*/
	std::pair<FTPClient*, int> tmp = std::make_pair(&CFTPClinet, fd);
	pthread_t tid;
	pthread_create(&tid, NULL, func, (void*)&tmp);

	while (true){
		pthread_mutex_lock(&mylock);
		if (cnt >= 100) {
			pthread_mutex_unlock(&mylock);
			break;
		}	 
		fileName[9] = '0' + cnt/100;
		fileName[10] = '0' + (cnt/10)%10;
		fileName[11] = '0' + cnt%10;
		uint64_t len = 0;	
		int ret;
		
		ret = CFTPClinet.ftp_storfile(fd, fileName, fileName, &len, NULL);

 		fprintf(stdout, "file len: %llu, ret = %d\n", len, ret);		
		cnt++;
		pthread_mutex_unlock(&mylock);
	}	


	CFTPClinet.ftp_quit(fd);
	
	return 0;
}
