#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 2000005;
const int Mo = 1000000007;

int inv2;

char s[N];
char text[N];
int length;
int R[N], sum0[N], cnt0[N], sum1[N], cnt1[N];

void Manacher(){
	R[1] = 1;
	for (int i = 2, j = 1; i <= length; i++){
		if (j + R[j] <= i){
			R[i] = 0;
		} else {
			R[i] = min(R[j * 2 - i], j + R[j] - i);
		}
		
		while (i - R[i] >= 1 && i + R[i] <= length && text[i - R[i]] == text[i + R[i]]){
			R[i]++;
		}
		
		if (i + R[i] > j + R[j]){
			j = i;
		}
	}
}

void Add0(int x, int val, int cnt){
	sum0[x] = (sum0[x] + val) % Mo;
	cnt0[x] = (cnt0[x] + cnt) % Mo;
}

void Add1(int x, int val, int cnt){
	sum1[x] = (sum1[x] + val) % Mo;
	cnt1[x] = (cnt1[x] + cnt) % Mo;
}

int main(){

	inv2 = (Mo + 1) / 2;
	
	while (scanf("%s", s + 1) == 1){
		length = 0;
		int n = strlen(s + 1);
		for (int i = 1; i <= n; i++){
			text[++length] = '*';
			text[++length] = s[i];
		}
		text[++length] = '*';
		
		Manacher();
		
		
		for (int i = 0; i <= length + 1; i++){
			sum0[i] = sum1[i] = cnt0[i] = cnt1[i] = 0;
		}
		
		for (int i = 1; i <= length; i++){
			Add0( i,  2 * i, 1);
			Add0( i + R[i], -2 * i, -1);
			Add1( i - R[i] + 1, 2 * i, 1);
			Add1( i + 1, -2 * i, -1);
		}
		
		for (int i = 1; i <= length + 1; i++){
			sum0[i] = (sum0[i] + sum0[i - 1]) % Mo;
			sum1[i] = (sum1[i] + sum1[i - 1]) % Mo;
			cnt0[i] = (cnt0[i] + cnt0[i - 1]) % Mo;
			cnt1[i] = (cnt1[i] + cnt1[i - 1]) % Mo;
		}
		
		
		int Ans = 0;
		int Sum0 = 0, Sum1 = 0, Cnt0 = 0, Cnt1 = 0;
		
		for (int i = 1; i <= length; i++){
			if (text[i] == '*') continue;
			if (i + 2 > length) continue;
			
			Sum0 = (sum0[i]) % Mo;
			Cnt0 = (cnt0[i]) % Mo;
			
			
			
			int Ans0 = (Sum0 - 1LL * Cnt0 * i % Mo) % Mo;
			
			Ans0 = (1LL * Ans0 * inv2) % Mo;
			
			
			Sum1 = (Sum1 + sum1[i]) % Mo;
			Cnt1 = (Cnt1 + cnt1[i]) % Mo;
			
			
			int Sum = (sum1[i + 2]) % Mo;
			int Cnt = (cnt1[i + 2]) % Mo;
			
		
			//printf("%d %d\n", Sum, Cnt);
		
			int Ans1 = (Sum - 1LL * Cnt * (i + 2) % Mo) % Mo;
			
			Ans1 = (1LL * Ans1 * inv2) % Mo;
			Ans = (Ans + 1LL * Ans0 * Ans1 % Mo) % Mo;
		}
		
		printf("%d\n", Ans);
	}
	
	return 0;
}

/*
*a*a*a*
1 2 3 4 3 2 1 
56
*a*b*c*
1 2 1 2 1 2 1 
32

*/
