#include <bits/stdc++.h>

#define __advance __attribute__((optimize("O3")))

typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
const int sgn[2] = {1, -1};

int n, v[20005];
ll presum[20005];

ll dp[2][20005][2];

__advance ll Max(ll a, ll b, int tp) {
	return tp == 0 ? std::max(a, b) : std::min(a, b);
}

__advance int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d", &n);
		for (register int i = 1; i <= n; ++i) {
			scanf("%d", v + i);
			presum[i] = presum[i - 1] + v[i];
		}		
		
		for (register int cur = 0; cur < 2; ++cur)
			for (register int i = 0; i <= n; ++i)
				for (register int t = 0; t < 2; ++t)
					dp[cur][i][t] = INF * sgn[t];
		
		register int cur = 1;
		for (register int k = 200; k; --k) {
			for (register int i = 0; i <= n; ++i)
				for (register int t = 0; t < 2; ++t)
					dp[cur][i][t] = (i + k > n ? 0 : INF * sgn[t]);
			for (register int i = n - k; i >= 0; --i)
				for (register int t = 0; t < 2; ++t) {
					ll tmp = Max(dp[cur][i + k][t ^ 1] + (presum[i + k] - presum[i]) * sgn[t], 
								(i + k + 1 <= n ? dp[cur ^ 1][i + k + 1][t ^ 1] + (presum[i + k + 1] - presum[i]) * sgn[t] : -INF * sgn[t]), t);
					if (dp[cur][i][t] == 0) dp[cur][i][t] = Max(tmp, 0, t);
					else dp[cur][i][t] = tmp;
				}
			cur ^= 1;
		}
		printf("%lld\n", dp[cur ^ 1][0][0]);
	}
	
	return 0;
}
