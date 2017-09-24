#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

typedef long long LL;

const int N = 70;

LL k[N];
int n;

LL Calc(LL A, int x){
	LL Ret = (A / (1LL << x)) * (1LL << (x - 1));
	
	Ret += max(A % (1LL << x) - (1LL << (x - 1)) + 1, 0LL);
	
	return Ret;
}

int main(){
	
	while (scanf("%d", &n) == 1){
		if (n == 0) break;
		
		for (int i = 1; i <= n; i ++)
			scanf("%lld", &k[i]);
		
		LL Len;
		LL Sum;
		LL A, B;
		LL AnsA = -1, AnsB = -1;
		int Ans = 0;
		
		for (int i = -1; i <= 1; i++){
			Len = k[1] * 2 + i;
			
			Sum = 0;
			for (int j = 1; j <= n; j++)
				Sum += (1LL << (j - 1)) * k[j];
			
			
			LL x = Len;
			
			
			if ((2 * Sum) % Len > 0) continue;
			
			LL y = (2 * Sum) / Len;
			
			if ((y - x + 1) % 2 > 0) continue;
			
			A = (y - x + 1) / 2;
			
			if ((x + y - 1) % 2 > 0) continue;
			
			B = (x + y - 1) / 2;
			
			if (A < 1 || A > 1e18) continue;
			if (B < 1 || B > 1e18) continue;
			
			bool flag = 1;
			
			LL Cnt;
			LL Cnt_B;
			LL Cnt_A;
			
			//printf("%lld %lld\n", A, B);
			
			for (int j = 1; j <= n; j++){
				
				Cnt_B = Calc(B, j);
				Cnt_A = Calc(A - 1, j);
				
				
				
				if (Cnt_B - Cnt_A != k[j]){
					flag = 0;
					break;
				}
			}
			
			if (flag){
				Ans++;
				printf("%lld %lld\n", A, B);
				AnsA = A;
				AnsB = B;
			}
		}
		
		if (Ans == 0) puts("None");
		else
		if (Ans == 1)
			cout << AnsA << ' ' << AnsB << endl;
		else
			puts("Many");
	}
	
	return 0;
}
