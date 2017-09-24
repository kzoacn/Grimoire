#include <bits/stdc++.h>
using namespace std;
#define __advance __attribute__((optimize("O3")))

const int match[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int Mod;

int dp[505][1 << 4];
int t[505][1 << 4], kase;

__advance int DP(int mat, bool A, bool B, bool C, bool ten) {
//	fprintf(stderr, "%d:: %d %d %d %d %d\n", bit, mat, A, B, C, ten);
	if (!mat) {
		//int cnt = (3 - A - B - C) * match[0];
		return !ten && A && B && C;
	}
//	if (mat < bit / 4) return 0;
	
	int S = ((int)A << 3) + ((int)B << 2) + ((int)C << 1) + ten;
	
	if (t[mat][S] == kase) return dp[mat][S];
	t[mat][S] = kase;
	long long res = 0;
	
	for (register int a = 0; a <= 9; ++a) {
		int ma = match[a] * (bool)(a || A);
		for (register int b = 0; b <= 9; ++b) {
			int mb = match[b] * (bool)(b || B);
			int c = a + ten * 10 - b, cost;
			if (c >= 0 && c <= 9) {
				cost = ma + mb + match[c] * (bool)(c || C);
				
//				fprintf(stderr, "%d: %d %d %d\n", bit, a, b, c);
				
				if (mat - cost >= 0) res += DP(mat - cost, A | a, B | b, C | c, 0);
			}
			c = a + ten * 10 - b - 1;
			if (c >= 0 && c <= 9) {
				cost = ma + mb + match[c] * (bool)(c || C);
				
//				fprintf(stderr, "%d: %d %d %d\n", bit, a, b, c);
				
				if (mat - cost >= 0) res += DP(mat - cost, A | a, B | b, C | c, 1);
			}
		}
	}
	
	return dp[mat][S] = res % Mod;
}

__advance int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (kase = 1; kase <= caseCnt; ++kase) {
		static int n;
		
		scanf("%d%d", &n, &Mod); n -= 3;
		
		printf("Case #%d: %d\n", kase, DP(n, 0, 0, 0, 0));
	}
	
	return 0;
}
