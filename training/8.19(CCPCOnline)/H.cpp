#include <bits/stdc++.h>

#define deb(x, y, z) if (i == x && j == y && k == z) fprintf(stderr, "DP: %lld\n", dp[i][j][k])

typedef long long ll;

const ll INF = 0x3f3f3f3f3f3f3f3fll;

ll dp[105][105][105];

int n, m, cturn, d[105];

int main() {
	while (~scanf("%d%d%d", &n, &m, &cturn)) {
		for (int i = 2; i <= n; ++i) scanf("%d", d + i);
		
		for (int i = 0; i <= n; ++i)
			for (int j = 0; j <= m; ++j)
				for (int k = 0; k <= m; ++k) {
					if (i && j == 1 && k == 1) dp[i][j][k] = cturn;
					else dp[i][j][k] = -INF;
				}
		
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j <= m; ++j) {
				for (int k = 0; k <= j; ++k) {
//					if (j == 1 && k == 1) continue;
					if (k) dp[i][j][k] = std::max(dp[i][j][k], dp[i - 1][j][k] + 2ll * d[i] * k);
					
//					deb(2, 2, 1);
					
					if (j - 1 >= 0) {
						if (k) dp[i][j][k] = std::max(dp[i][j][k], dp[i - 1][j - 1][k] + 2ll * d[i] * k);
						if (k - 1 > 0) dp[i][j][k] = std::max(dp[i][j][k], dp[i - 1][j - 1][k - 1] + 2ll * d[i] * (k - 1) + cturn);
						if (k + 1 <= j - 1) dp[i][j][k] = std::max(dp[i][j][k], dp[i - 1][j - 1][k + 1] + 2ll * d[i] * (k + 1) + cturn);
					}
				}
			}
		}
		
		ll ans = -INF;
		for (int i = 1; i <= n; ++i) {
			ans = std::max(ans, dp[i][m][0]);
//			fprintf(stderr, "%d: ans = %lld\n", i, ans);
		}
		
		printf("%lld\n", ans);
	}
	
	return 0;
}
