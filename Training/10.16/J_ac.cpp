#include <bits/stdc++.h>
using namespace std;

const int MAXN = 333;
const int MOD = 1e9 + 7;
const int MAXS = MAXN * MAXN;
int n, s, x[MAXN], f[MAXS], g[MAXS];

inline int fpm(int x, int k, int mod) {
	int ret = 1;
	for (; k; k >>= 1) {
		if (k & 1) {
			ret = 1LL * ret * x % MOD;
		}
		x = 1LL * x * x % MOD;
	}
	return ret;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &x[i]);
	}
	scanf("%d", &s);
	
	f[s] = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= s; ++j) {
			g[j] = 0;
		}
		for (int j = 0; j <= s; ++j) {
			g[j] = f[j];
			if (j + x[i] <= s) {
				g[j] -= f[j + x[i]];
			}
			g[j] %= MOD;
		}
		for (int j = 0; j <= s; ++j) {
			f[j] = (g[j] + MOD) % MOD;
		}
	}
	
	int ans = 0;
	for (int i = 1; i <= s; ++i) {
		ans = (ans + 1LL * fpm(i, n, MOD) * f[i]) % MOD;
	}
	cout << ans << endl;
}
