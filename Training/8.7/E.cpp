#include <bits/stdc++.h>

typedef long long ll;

const ll LNF = ~0ull >> 1;

int d[4];

bool skip[4];

ll calc(ll k) {
	static bool dp[500005];
	static const int MAXK = 500000;
	
	if (k <= 0) return 0;
	
	memset(dp, 0, sizeof dp);
	dp[0] = 1;
	
	for (int i = 0; i < 4; ++i) if (!skip[i])
		for (int j = d[i]; j <= MAXK; ++j)
			dp[j] |= dp[j - d[i]];
	
	ll res = LNF;
	for (int i = 0; i < 4; ++i) if (!skip[i]) {
		for (ll kk = k; kk <= k + 30000; ++kk) {
			ll t = std::max((kk - MAXK + d[i] - 1) / d[i], 0ll);
			if (dp[kk - d[i] * t]) {
				res = std::min(res, kk); break;
			}
		}
	}
	return res;
}

int main() {
	ll k;
	
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		int sum = 0;
		
		scanf("%lld", &k);
		for (int i = 0; i < 4; ++i) {
			scanf("%d", d + i); sum += d[i];
		}
		
		memset(skip, 0, sizeof skip);
		ll ans = std::min(calc((k - sum + 1) / 2) * 2 + sum, calc((k - sum * 2 + 1) / 2) * 2 + sum * 2);
		
		for (int i = 1; i <= 4; ++i)
			for (int j = i; j <= 4; ++j) {
				if (i == 1 && j == 4) continue;
				memset(skip, 0, sizeof skip);
				for (int t = i; t <= j; ++t) skip[t % 4] = 1;
				
				sum = 0;
				for (int t = 0; t < 4; ++t) if (!skip[t]) sum += d[t];
				
				ans = std::min(ans, calc((k - sum * 2 + 1) / 2) * 2 + sum * 2);
			}
		
		printf("%lld\n", ans);
	}
	
	return 0;
}
