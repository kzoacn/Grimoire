#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 1005;
const int Mo = 1000000007;

int f[N], n;


int main(){
	
	f[1] = 1;
	for (int i = 2; i <= 1000; i++){
		f[i] = 0;
		for (int j = 1; j <= i - 1; j++)
			if ((i - 1) % j == 0)
				f[i] = (f[i] + f[j]) % Mo;
	}
	
	int Case = 0;
	while (scanf("%d", &n) == 1){
		++Case;
		printf("Case %d: %d\n", Case, f[n]);
	}
	
	return 0;
}
