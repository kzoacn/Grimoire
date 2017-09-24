#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long LL;

const int N = 105;

char str[N];
LL n;

int main(){
	
	while (scanf("%s", str + 1) == 1){
		int len = strlen(str + 1);
		if (len > 15){
			printf("TAT\n");
			continue;
		}
		n = 0;
		for (int i = 1; i <= len; i++)
			n = n * 10 + str[i] - '0';
		
		if (n == 0 || n >= (1LL << 32)){
			printf("TAT\n");
			continue;
		}
		
		for (LL i = 0, t = 2; i <= 5; i++, t = t * t){
			if (n < t){
				cout << i << endl;
				break;
			}
		}
	}
	
	return 0;
}

