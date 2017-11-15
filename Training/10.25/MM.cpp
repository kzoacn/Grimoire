#include <bits/stdc++.h>

const int MAXN = 20 + 5, MAXM = 500 + 5;
const int Mod = 1e9 + 7;

int n, m;
int a[MAXN], b[MAXM];
int dp[MAXN][MAXM][MAXM];

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
		
		for (int i = 2; i <= n; ++i) {
			for (int j = i; j <= m; ++j) {
				for (int k = 1; k < j; ++k) if ((a[i - 1] == 0 && b[j] >= b[k]) || (a[i - 1] == 1 && b[j] <= b[k])) {
					if (a[i - 1] ^ a[i]) {
						int &res = dp[i][j][b[k]];
						res = (res + dp[i - 1][k][b[j]]) % Mod;
					}
					else {
						if (a[i] == 0)
							for (int t = b[j]; t <= m; ++t)
								dp[i][j][t] = (1ll * dp[i][j][t] + dp[i - 1][k][t] - dp[i - 1][k][t + 1] + Mod) % Mod;
						else
							for (int t = b[j]; t > 0; --t)
								dp[i][j][t] = (1ll * dp[i][j][t] + dp[i - 1][k][t] - dp[i - 1][k][t - 1] + Mod) % Mod;
					}
				}
				
				if (a[i] == 0)
					for (int k = m; k > 0; --k)
						dp[i][j][k] = (dp[i][j][k] + dp[i][j][k + 1]) % Mod;
				else
					for (int k = 1; k <= m; ++k)
						dp[i][j][k] = (dp[i][j][k] + dp[i][j][k - 1]) % Mod;
				
				if (i == n)
					ans = (ans + (a[i] == 0 ? dp[i][j][1] : dp[i][j][m])) % Mod;		
			}
		}
		
		printf("%d\n", ans);
	}
	
	return 0;
}
