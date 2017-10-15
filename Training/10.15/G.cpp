#include <bits/stdc++.h>

typedef long long ll;

const int Mod = 1e9 + 7;

int inv[2005];

int qpow(int a, int x) {
	int res = 1;
	for (; x; x >>= 1) {
		if (x & 1) res = 1ll * res * a % Mod;
		a = 1ll * a * a % Mod;
	}
	return res;
}

void pretreatment() {
	for (int i = 1; i <= 2000; ++i)
		inv[i] = qpow(i, Mod - 2);
}

int dp[2][2005];

ll C(ll n, int k) {
	ll res = 1;
	for (int i = 0; i < k; ++i)
		res = res * ((n - i) % Mod) % Mod;
	for (int i = 1; i <= k; ++i)
		res = res * inv[i] % Mod;
	return res;
}

int main() {
	pretreatment();
	
	int n, X;
	ll D;
	
	while (std::cin >> n >> D >> X && (n || D || X)) {
		memset(dp, 0, sizeof dp);
		--X;
		
		int cur = 1, day = std::min(D, (ll)n);
		dp[0][0] = 1;
		int ans = 0;
		for (int i = 1; i <= day; ++i) {
			memset(dp[cur], 0, sizeof dp[cur]);
			int presum = dp[cur ^ 1][0];
			for (int L = 0, R = 1; R <= n; ++R) {
				while (R - L > X)
					presum = (1ll * presum - dp[cur ^ 1][L++] + Mod) % Mod;
				dp[cur][R] = presum;
				presum = (1ll * presum + dp[cur ^ 1][R]) % Mod;
			}
//			std::cerr << i << " " << dp[cur][n] << std::endl;
			ans = (ans + 1ll * dp[cur][n] * C(D, i) % Mod) % Mod;
			cur ^= 1;
		}
		
		std::cout << ans << std::endl;
	}
	
	return 0;
}
