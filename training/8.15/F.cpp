#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MOD = 1e9 + 7;
const int MAXN = 111111;
int s[1111], c[1111], dp[1111], g[1111], f[20][200];
int fac[MAXN], inv[MAXN];
int n, m, K, testcase;

inline int fpm(int x, int k, int mod) {
	LL ret = 1;
	for (; k; k >>= 1) {
		if (k & 1) {
			ret = 1LL * ret * x % mod;
		}
		x = 1LL * x * x % mod;
	}
	return ret;
}

inline int C(int n, int m) {
	if (m < 0 || m > n || n < 0) {
		return 0;
	}
	return 1LL * fac[n] * inv[m] % MOD * inv[n - m] % MOD;
}

int main() {
	fac[0] = 1;
	for (int i = 1; i < MAXN; ++i) {
		fac[i] = 1LL * fac[i - 1] * i % MOD;
	}
	for (int i = 0; i < MAXN; ++i) {
		inv[i] = fpm(fac[i], MOD - 2, MOD);
	}
	
	cin >> testcase;
	for (int cs = 1; cs <= testcase; ++cs) {
		cin >> n >> m >> K;
		s[0] = 0;
		for (int i = 1; i <= m; ++i) {
			scanf("%d", &c[i]);
			s[i] = s[i - 1] + c[i];
		}
		for (int k = 0; k <= K; ++k) {
		//for (int k = 1; k <= 1; ++k) {
			for (int i = 0; i <= m; ++i) {
				for (int j = 0; j <= k; ++j) {
					f[i][j] = 0;
				}
			}
			f[0][k] = C(K, k);
			for (int i = 0; i < m; ++i) {
				for (int j = 0; j <= k; ++j) {
					if (!f[i][j]) {
						continue;
					}
					for (int l = 0; l <= j; ++l) {
						f[i + 1][j - l] = (f[i + 1][j - l] + 1LL * f[i][j] * C(j, l) % MOD * C(n - s[i] - j * 2, c[i + 1] - l * 2)) % MOD;
//if (i + 1 == 1 && j - l == 1)
					}
				}
			}
/*for (int i = 1; i <= m; ++i) {
	for (int j = 0; j <= k; ++j) {
		cout << i << " " << j << " -> " << f[i][j] << endl;
	}
}*/
			g[k] = f[m][0];
			//cout << k << ": " << g[k] << endl;
		}
		
		for (int i = K; i >= 0; --i) {
			dp[i] = g[i];
			for (int j = i + 1; j <= K; ++j) {
				dp[i] = (dp[i] - 1LL * dp[j] * C(j, i)) % MOD;
			}
		}
		LL ans = 0;
		for (int i = 0; i <= K; ++i) {
			LL temp = 1LL * dp[i] * fpm(fpm(2, K - i, MOD), MOD - 2, MOD) % MOD;
			ans = (ans + temp) % MOD;
		}
		ans = (ans + MOD) % MOD;
		printf("Case #%d: %d\n", cs, (int)ans);
	}
}
