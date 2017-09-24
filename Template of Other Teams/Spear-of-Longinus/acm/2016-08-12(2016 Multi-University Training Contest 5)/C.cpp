#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

typedef long long LL;

const int N = 1000005;

int n;
int a[N];

int main(){
	
	while (scanf("%d", &n) == 1){
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
			
		int Ans = 0;
		LL Sum = 0;
		for (int i = n; i >= 1; i--){
			Sum += a[i];
			if (Sum >= 0){
				Ans++;
				Sum = 0;
			}
		}
		
		printf("%d\n", Ans);
	}
	
	return 0;
}
