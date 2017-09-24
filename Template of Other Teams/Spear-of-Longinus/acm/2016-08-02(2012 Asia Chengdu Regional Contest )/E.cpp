

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 100005;

char s[N], t[N];
int fail[N];
int len, n;

void build(int x, int lst){
	for (int i = lst + 1, j; i <= x; i++){
		for (j = fail[i - 1]; j != -1 && t[i] != t[j + 1]; j = fail[j]);
		fail[i] = j + 1;
	}
}

int main(){
	
	int Case = 0;
	while (scanf("%s", s + 1) == 1){
		
		int len = strlen(s + 1);
		
		for (int i = 0; i <= len; i++)
			fail[i] = -1, t[i] = 'A';
		
		n = 1;
		build(1, 0);
		
		t[1] = s[1];
		int j = 0;
		int last = 0;
		for (int i = 1; i <= len; i++){
			for ( ; j != -1 && s[i] != t[j + 1]; j = fail[j]);
			
			
			j++;
			
			if (j == 0){
				int lst = n;
				for (int k = last + 1; k <= i; k++)
					t[++n] = s[k];
				last = i;
				build(n, lst); 
			} else if (j == n) {
				last = i;
			}
		}
		
		for (int i = last + 1; i <= len; i++)
			t[++n] = s[i];
			
		++Case;
		printf("Case %d: %d\n", Case, n);
		
	}
	
	return 0;
}


