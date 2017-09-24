#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 200000;
const int MOD = 1e9 + 7;
LL fac[MAXN], inv[MAXN], pw[MAXN], pw1[MAXN];
int testcase, n;

inline int fpm(int x, int k, int mod) {
	int ret = 1;
	for (; k; k >>= 1) {
		if (k & 1) {
			ret = 1LL * ret * x % mod;
		}
		x = 1LL * x * x % mod;
	}
	//cout << x << " " << ret << endl;
	return ret;
}

inline LL C(int n, int m) {
	if (m > n || m < 0) {
		return 0LL;
	}
	return fac[n] * inv[m] % MOD * inv[n - m] % MOD;
}

int main() {
	fac[0] = inv[0] = 1;
	for (int i = 1; i < MAXN; ++i) {
		fac[i] = fac[i - 1] * i % MOD;
		inv[i] = fpm(fac[i], MOD - 2, MOD);
		//cout << i << " " << fac[i] << " " << inv[i] << endl;
	}
//cout << fac[2] << "  " << inv[2] << " " << inv[0] << endl;
//cout << C(2, 2) << endl; return 0;
	scanf("%d", &testcase);
	for (int cs = 1; cs <= testcase; ++cs) {
		scanf("%d", &n);
		if (n == 1) {
			printf("Case #%d: %d\n", cs, 0);
			continue;
		}
		LL ans = 0;
		pw[0] = 1;
		pw1[0] = 1;
		for (int i = 1; i <= n; ++i) {
			pw[i] = pw[i - 1] * n % MOD;
			pw1[i] = pw1[i - 1] * (n - 1) % MOD;
		}
		for (int k = 2; k <= n; ++k) {
			//LL tmp = fac[n - 1] * inv[n - k] % MOD * (fpm(n, n - k, MOD) - fpm(n - 1, n - k, MOD)) % MOD;
			LL tmp = fac[n - 1] * inv[n - k] % MOD * (pw[n - k] - pw1[n - k]) % MOD;
			ans = (ans + tmp) % MOD;
			//cout << k << " " << tmp << " " << fac[n - 1] * inv[n - k] << " " << fpm(n, n - k, MOD) << " " << fpm(n - 1, n - k, MOD) << endl;
		}
		ans = (ans + fpm(n, n - 1, MOD) - fpm(n - 1, n - 1, MOD) - 1LL * (n - 1) * fpm(n - 1, n - 2, MOD)) % MOD;
		//cout << fpm(n, n - 1, MOD) - fpm(n - 1, n - 1, MOD) - 1LL * (n - 1) * fpm(n - 1, n - 2, MOD) << endl;
		for (int k = 1; k < n; ++k) {
			//LL tmp = fpm(n - 1, n - k, MOD) * C(n - 1, k);
			LL tmp = pw1[n - k] * C(n - 1, k);
			ans = (ans + tmp) % MOD;
			//cout << k << " " << C(n - 1, k) << " " << tmp << endl;
		}
		for (int k = 2; k <= n; ++k) {
			//LL tmp = fac[n - 1] * inv[n - k] % MOD * fpm(n, n - k, MOD) % MOD;
			LL tmp = fac[n - 1] * inv[n - k] % MOD * pw[n - k] % MOD;
			ans = (ans - tmp) % MOD;
		}
		ans = (ans + MOD) % MOD;
		ans = ans * n % MOD;
		printf("Case #%d: %d\n", cs, (int)ans);
	}
}
