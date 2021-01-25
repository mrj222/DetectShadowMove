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
bool fake(){
	int u = rand()%10;
	return u > 0;
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



	int pid = fork();
	int pid2 = fork();

	for (int t = 0;t < 100;t++){
		int fd = CFTPClinet.ftp_connect(FTPIPAddress, 21, strUserName, strPassword);

		if (fd < 0){
			fprintf(stdout, "ftp connect falied\n");
		}
		printf("%d %d\n",getpid(),t);
		for (int i = 0;i < 20;i++){
			int u = i;
			for (int j = 11;j >= 9;j--){
				fileName[j] = '0' + u % 10;
				u /= 10;
			}
			uint64_t len,x;
			if (fake()) CFTPClinet.ftp_retrfile(fd, fileName, fileName, &len, NULL);
			else CFTPClinet.ftp_storfile(fd, fileName, fileName, &len, NULL);
		}
		CFTPClinet.ftp_quit(fd);
	}
	if (pid == 0 && pid2) while(~waitpid(-1,NULL,0));
	if (pid && pid2) while(~waitpid(-1,NULL,0));
	return 0;
}
