#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MOD = 1e9 + 7;
int testcase, a1, b1, d, q, n, m;
int inv[111111];

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

inline LL get_a(int n, int m) {
	LL c = 1, ans = 0;
	for (int i = 1; i <= n; ++i) {
		ans = (ans + (a1 + 1LL * (n - i) * d % MOD) % MOD * c) % MOD;
		c = c * (m + i - 1) % MOD * inv[i] % MOD;
	}
	return ans;
}

inline LL get_b_1(int n, int m) {
	LL c = 1;
	for (int i = 1; i <= n; ++i) {
		c = c * (m + i - 1) % MOD * inv[i] % MOD;
	}
	return c * b1 % MOD;
}

inline LL get_b(int n, int m) {
	if (q % MOD == 1) {
		return get_b_1(n, m);
	}
	if (m == 0) {
		return 0;
	}
	LL inv_q = fpm(q - 1, MOD - 2, MOD), sum = fpm(q, m - 1, MOD), c = 1;
	for (int i = 1; i <= n; ++i) {
		sum = (1LL * q * inv_q % MOD * sum - inv_q * c) % MOD;
		c = c * (i + m - 1) % MOD * inv[i] % MOD;
	}
	return b1 * sum;
}

int main() {
	for (int i = 1; i <= 10010; ++i) {
		inv[i] = fpm(i, MOD - 2, MOD);
	}
	scanf("%d", &testcase);
	for (int cs = 1; cs <= testcase; ++cs) {
		scanf("%d%d%d%d%d%d", &b1, &q, &a1, &d, &n, &m);
		int ans = (get_a(n, m) + get_b(n, m)) % MOD;
		if (ans < 0) ans += MOD;
		printf("Case #%d: %d\n", cs, ans);
	}
}
