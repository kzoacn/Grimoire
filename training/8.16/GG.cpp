#include <bits/stdc++.h>
using namespace std;
#define __advance __attribute__((optimize("O3")))

const int match[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int Mod;

int dp[130][505][1 << 4];
int t[130][505][1 << 4], kase;

__advance int DP(int bit, int mat, bool A, bool B, bool C, bool ten) {
//	fprintf(stderr, "%d:: %d %d %d %d %d\n", bit, mat, A, B, C, ten);
	if (bit == 0) {
		//int cnt = (3 - A - B - C) * match[0];
		return !ten && !mat && A && B && C;
	}
//	if (mat < bit / 4) return 0;
	
	register int S = ((int)A << 3) + ((int)B << 2) + ((int)C << 1) + ten;
	
	if (t[bit][mat][S] == kase) return dp[bit][mat][S];
	t[bit][mat][S] = kase;
	register long long res = 0;
	
	for (register int a = 0; a <= 9; ++a) {
		register int ma = match[a] * (bool)(a || A);
		for (register int b = 0; b <= 9; ++b) {
			register int mb = match[b] * (bool)(b || B);
			register int c = a + ten * 10 - b, cost;
			if (c >= 0 && c <= 9) {
				cost = ma + mb + match[c] * (bool)(c || C);
				
//				fprintf(stderr, "%d: %d %d %d\n", bit, a, b, c);
				
				if (mat - cost >= 0) res += DP(bit - 1, mat - cost, A | a, B | b, C | c, 0);
			}
			c = a + ten * 10 - b - 1;
			if (c >= 0 && c <= 9) {
				cost = ma + mb + match[c] * (bool)(c || C);
				
//				fprintf(stderr, "%d: %d %d %d\n", bit, a, b, c);
				
				if (mat - cost >= 0) res += DP(bit - 1, mat - cost, A | a, B | b, C | c, 1);
			}
		}
	}
	
	return dp[bit][mat][S] = res % Mod;
}

inline int calc_state(int A, int B, int C, int ten) {
	return ((int)A << 3) + ((int)B << 2) + ((int)C << 1) + ten;
}

__advance int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (kase = 1; kase <= caseCnt; ++kase) {
		static int n;
		
		scanf("%d%d", &n, &Mod); n -= 3;
		
		for (int i = 0; i <= n / 4; ++i) {
			for (int j = 0; j <= n; ++j) {
				memset(dp[i][j], 0, sizeof(dp[i][j]));
			}
		}
		//dp[0][0][1][1][1][0] = 1;
		dp[0][0][calc_state(1, 1, 1, 0)] = 1;
		for (int bit = 1; bit <= n / 4; ++bit) {
			for (int mat = 1; mat <= n; ++mat) {
				for (int S = 0; S < 16; ++S) {
					int A = (S >> 3) & 1,
						B = (S >> 2) & 1,
						C = (S >> 1) & 1,
						ten = (S) & 1;
					long long res = 0;
					for (register int a = 0; a <= 9; ++a) {
						register int ma = match[a] * (bool)(a || A);
						for (register int b = 0; b <= 9; ++b) {
							register int mb = match[b] * (bool)(b || B);
							register int c = a + ten * 10 - b, cost;
							if (c >= 0 && c <= 9) {
								cost = ma + mb + match[c] * (bool)(c || C);
								if (mat - cost >= 0) res += dp[bit - 1][mat - cost][calc_state(A | a, B | b, C | c, 0)];
							}
							c = a + ten * 10 - b - 1;
							if (c >= 0 && c <= 9) {
								cost = ma + mb + match[c] * (bool)(c || C);
								if (mat - cost >= 0) res += dp[bit - 1][mat - cost][calc_state(A | a, B | b, C | c, 1)];
							}
						}
					}
					
					dp[bit][mat][S] = res % Mod;
				}
			}
		}
		
		printf("Case #%d: %d\n", kase, dp[n / 4][n][calc_state(0, 0, 0, 0)]);
		//printf("Case #%d: %d\n", kase, DP(n / 4, n, 0, 0, 0, 0));
	}
	
	return 0;
}
