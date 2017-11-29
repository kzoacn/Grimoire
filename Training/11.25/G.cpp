#include <bits/stdc++.h>

const int MAXN = 105;

int n, a[MAXN], p1;

bool dp[MAXN][MAXN][2];

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	while (caseCnt--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			if (a[i] == 1) p1 = i;
		}
		
//		memset(dp, 0, sizeof dp);
		dp[p1][p1][0] = dp[p1][p1][1] = 1;
		for (int len = 2; len <= n; ++len) {
			for (int L = 1, R = len; R <= n; ++L, ++R) if (L <= p1 && p1 <= R) {
				static bool tmp;
				
				// 0
				
				tmp = 1;
				
				for (int i = L; i < p1; ++i)
					if ((i == L && a[i] > a[i + 1]) || (a[i] > a[i - 1] && a[i] > a[i + 1]))
						tmp &= dp[i + 1][R][0 ^ ((i - L) & 1)];
				for (int i = R; i > p1; --i)
					if ((i == R && a[i] > a[i - 1]) || (a[i] > a[i - 1] && a[i] > a[i + 1]))
						tmp &= dp[L][i - 1][0 ^ ((R - i) & 1)];
				
				dp[L][R][0] = tmp ^ 1;
				
				// 1
				
				tmp = 1;
				
				for (int i = L; i < p1; ++i)
					if ((i == L && a[i] > a[i + 1]) || (a[i] > a[i - 1] && a[i] > a[i + 1]))
						tmp &= dp[i + 1][R][1 ^ ((i - L) & 1)];
				for (int i = R; i > p1; --i)
					if ((i == R && a[i] > a[i - 1]) || (a[i] > a[i - 1] && a[i] > a[i + 1]))
						tmp &= dp[L][i - 1][1 ^ ((R - i) & 1)];
				tmp &= dp[L][R][0];
				
				dp[L][R][1] = tmp ^ 1;
			}
		}
		
		puts(dp[1][n][0] ? "Alice" : "Bob");
	}
	
	return 0;
}
