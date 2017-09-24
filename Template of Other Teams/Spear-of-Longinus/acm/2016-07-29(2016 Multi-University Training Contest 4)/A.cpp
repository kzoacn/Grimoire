#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 100005;
const int Mo = 1000000007;

int f[N], fail[N], match[N];
char test[N], pattern[N];

void build(){
	int length = (int) strlen(pattern + 1);
	fail[0] = -1;
	for (int i = 1, j; i <= length; i++){
		for (j = fail[i - 1]; j != -1 && pattern[i] != pattern[j + 1]; j = fail[j]);
		fail[i] = j + 1;
	}
}

void solve(){
	int length = (int) strlen(test + 1);
	match[0] = 0;
	for (int i = 1, j; i <= length; i++){
		for (j = match[i - 1]; j != -1 && test[i] != pattern[j + 1]; j = fail[j]);
		match[i] = j + 1;
	}
}

int main(){
	
	int Case;
	scanf("%d", &Case);
	
	for (int ii = 1; ii <= Case; ii++){
		scanf("%s", test + 1);
		scanf("%s", pattern + 1);
		
		build();
		solve();
		
		int length = (int) strlen(test + 1);
		int m = (int) strlen(pattern + 1);
		for (int i = 0; i <= length; i++) f[i] = 0;
		f[0] = 1;
		for (int i = 1; i <= length; i++){
			f[i] = f[i - 1];
			if (i - m + 1  >= 1){
				if (match[i] == m){
					f[i] = (f[i] + f[i - m]) % Mo;
				}
			}
		}
		
		printf("Case #%d: %d\n", ii, f[length]);
		
	}
	
	return 0;
}
