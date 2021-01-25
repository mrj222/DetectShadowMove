#include <iostream>
#include <ctime>
#include "BOBHash32.h"
#include "detect.h"


static const int N = 100000,M = 100000;


int con_sum[M]={0}, con_max[M]={0};
int a[N],b[N];
int main(){
	srand(time(NULL));
	for (int i = 0;i < M;i++) 
		rand();
	BOBHash32 bucket(200);
	for (int i = 0;i < M;i++){
		char str[20];
		for (int j = 0;j < 13;j++) 
			str[j] = rand();
		str[13] = 0;
		uint val = bucket.run(str, 13);
		con_sum[i+1] = con_sum[i];
		con_max[i+1] = con_max[i];
		if (a[val%N]) {
			if (a[val%N] != val){ 
				b[val%N]++;	
				a[val%N] = val;
			}
			con_sum[i+1]++;
			con_max[i+1] = max(con_max[i+1], b[val%N]);
		}
		a[val%N] = val;		
	}
	printf("%d %d\n",con_sum[M], con_max[M]);
	return 0;
}

