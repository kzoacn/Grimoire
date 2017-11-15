#include <bits/stdc++.h>

const int MAXN = 1e5 + 5;

int n, a[MAXN], dp[MAXN];

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
			scanf("%d", a + i);
		
		std::sort(a + 1, a + n + 1);
		
		memset(dp, 0x3f, sizeof dp);
		dp[0] = 0;
		for (int i = 1; i <= n; ++i) {
			dp[i] = dp[i - 1] + a[i];
			if (i >= 3) dp[i] = std::min(dp[i], dp[i - 3] + a[i] + a[i - 1]);
		}
		
		printf("Case #%d: %d\n", kase, dp[n]);
	}
	
	return 0;
}
