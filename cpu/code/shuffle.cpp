#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

const int N = 10100,M = 150000,K = 110;
char str[M][110],tmp[K];
int len = 0,id[M];
int main(int argc, char** argv){
	srand(time(NULL));
	freopen("7a.out","r",stdin);
	freopen("7b.out","w",stdout);
	while (fgets(str[len], K, stdin)){
		len++;
	}
	for (int i = 0;i < len;i++) 
		id[i] = i;
	random_shuffle(id,id+len);
	for (int i = 0;i < len;i++){
		int j = id[i];
		printf("%s",str[j]);
	}
	return 0;
}
