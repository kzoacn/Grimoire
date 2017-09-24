#include <bits/stdc++.h>

typedef unsigned long long ull;

int n, sa[100005], rk[100005];

ull dp[100005][26]; // suf sum

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", sa + i); rk[sa[i]] = i;
		}
		rk[n + 1] = 0;
		
		for (int i = 0; i < 26; ++i) dp[n][i] = 26 - i;
		
		for (int i = n - 1; i; --i) {
			for (int j = 0; j < 26; ++j) {
				if (rk[sa[i] + 1] < rk[sa[i + 1] + 1])
					dp[i][j] = dp[i + 1][j];
				else
					dp[i][j] = j < 25 ? dp[i + 1][j + 1] : 0;
			}
			for (int j = 24; j >= 0; --j)
				dp[i][j] += dp[i][j + 1];
		}
		
		printf("%llu\n", dp[1][0]);
	}
	
	return 0;
}
