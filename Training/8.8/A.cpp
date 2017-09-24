#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MOD = 152076289;
const int MAXN = 10010;
int fac[MAXN], inv[MAXN], f[MAXN], pw[MAXN];
int testcase, n, m;

inline LL fpw(int x, int k, int mod) {
//cout << x << " " << k << " " << mod << endl;
	LL ret = 1;
	for (; k; k >>= 1) {
		if (k & 1) {
			ret = ret * x % mod;
		}
		x = 1LL * x * x % mod;
	}
//cout << ret << endl;
	return ret;
}

inline LL C(int n, int m) {
	if (n < m) {
		return 0;
	} else {
		return 1LL * fac[n] * inv[m] % MOD * inv[n - m] % MOD;
	}
}

int main() {
	fac[0] = 1;
	inv[0] = 1;
	for (int i = 1; i < MAXN; ++i) {
		fac[i] = 1LL * fac[i - 1] * i % MOD;
		inv[i] = fpw(fac[i], MOD - 2, MOD);
	}

	scanf("%d", &testcase);
	for (int cs = 1; cs <= testcase; ++cs) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i <= n; ++i) {
			int c = i * (i - 1) / 2;
			pw[i] = fpw(m + 1, c, MOD);
		}
		
		f[0] = 1;
		for (int i = 1; i <= n; ++i) {
			f[i] = pw[i];
			for (int j = 1; j < i; ++j) {
				f[i] = (1LL * f[i] - 1LL * C(i - 1, j - 1) * f[j] % MOD * pw[i - j]) % MOD;
			}
		}
		LL ans = (1LL * f[n] - fpw(n, n - 2, MOD) * fpw(m, n - 1, MOD)) % MOD;
		if (ans < 0) {
			ans += MOD;
		}
		printf("Case #%d: %d\n", cs, (int)ans);
	}
}
