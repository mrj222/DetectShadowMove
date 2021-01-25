#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

char fileName[50] = "test/file000.out";
int main(){
	FILE *handle;
	for (int i = 0;i < 100;i++){
		fileName[9] = '0' + i/100;
		fileName[10] = '0' + (i/10)%10;
		fileName[11] = '0' + i%10;
		printf("%s\n",fileName);
		handle = fopen(fileName, "w+");
		int u = rand()%1000+100;
		for (int j = 0;j < u;j++) {
			char ch = rand()%26+'a';
			fprintf(handle, "%c", ch);

		}
		fprintf(handle, "\n");
		fclose(handle);
	}
}
