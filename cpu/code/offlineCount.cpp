#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cstring>
#include <string>
#include <algorithm>
#include <map>

#include "BOBHash32.h"

using namespace std;

map<string, uint32_t> mp;
const int N = 10100,M = 150000,K = 110;
char tmp[K], *str;
int cnt = 0,len = 0,id[M];
int main(int argc, char** argv){
	printf("%d %d\n",prime32[200],prime32[500]);
	while (str = fgets(tmp, K, stdin)){
		char* index = str;
		for (int i = 0;i < 4;i++) {
			index = strstr(index, " ");
			index++;
		}
		string ss = "";
		for (int i = 0;i < index-str;i++)
			ss += str[i];
		uint32_t val;
		sscanf(index,"%u",&val);
		if (mp.find(ss) == mp.end()){
			mp[ss] = val;
		}
		else{
			if (mp[ss] != val) {
				cnt++; 
/*
				cout << ss;
				printf("%ukk\n",mp[ss]);
				printf("%s",str);
*/
			}			
		}
		len++;
	}
	printf("%d\n",cnt);
	return 0;
}
