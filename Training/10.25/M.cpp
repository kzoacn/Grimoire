#include <bits/stdc++.h>

const int MAXN = 20 + 5, MAXM = 500 + 5;
const int Mod = 1e9 + 7;

int n, m;
int a[MAXN], b[MAXM];
int dp[MAXN][MAXM][MAXM];

__attribute__((optimize("O3"))) __inline int fix(int x) {
	return x < 0 ? x + Mod : (x >= Mod ? x - Mod : x);
}

int main() {
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		for (int i = 1; i <= m; ++i) scanf("%d", b + i);
		
		memset(dp, 0, sizeof dp);
		for (int i = 1; i <= m; ++i) {
			for (int j = 1; j <= m; ++j) {
				if (a[1] == 0)
					dp[1][i][j] = 1;
				else
					dp[1][i][j] = 1;
			}
		}
		
		if (n == 1) {
			printf("%d\n", m);
			continue;
		}
		
		int ans = 0;
		
		for (register int i = 2; i <= n; ++i) {
			for (register int j = i; j <= m; ++j) {
				for (register int k = 1; k < j; ++k) if ((a[i - 1] == 0 && b[j] >= b[k]) || (a[i - 1] == 1 && b[j] <= b[k])) {
					if (a[i - 1] ^ a[i]) {
						int &res = dp[i][j][b[k]];
						res = fix(res + dp[i - 1][k][b[j]]);
					}
					else {
						if (a[i] == 0) {
							int *kk = dp[i][j] + b[j], *pp = dp[i - 1][k] + b[j];
							for (int t = b[j]; t <= m; ++t) {
								*kk = fix(*kk + *pp - *(pp + 1));
								++kk; ++pp;
							}
						}
						else {
							int *kk = dp[i][j] + b[j], *pp = dp[i - 1][k] + b[j];
							for (int t = b[j]; t > 0; --t) {
								*kk = fix(*kk + *pp - *(pp - 1));
								--kk; --pp;
							}
						}
					}
				}
				
				if (a[i] == 0)
					for (register int k = m; k > 0; --k)
						dp[i][j][k] = fix(dp[i][j][k] + dp[i][j][k + 1]);
				else
					for (register int k = 1; k <= m; ++k)
						dp[i][j][k] = fix(dp[i][j][k] + dp[i][j][k - 1]);
				
				if (i == n)
					ans = fix(ans + (a[i] == 0 ? dp[i][j][1] : dp[i][j][m]));
			}
		}
		
		printf("%d\n", ans);
	}
	
	return 0;
}
