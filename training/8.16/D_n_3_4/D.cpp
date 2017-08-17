#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 100000;
const int MAXM = 100000;
LL fac[MAXM], g[MAXN], f[MAXN], fc[MAXN], fr[MAXN], gr[MAXN], gc[MAXN];

inline LL fpm(LL x, LL k, LL mod) {
	LL ret = 1;
	for (; k; k >>= 1) {
		if (k & 1) {
			ret = ret * x % mod;
		}
		x = x * x % mod;
	}
	return ret;
}

inline void prep(LL now, LL mod, LL &r, LL &c) {
	if (now == 0) {
		r = 0;
		c = 1;
		return;
	}
	prep(now / mod, mod, r, c);
	r += now / mod;
	c = fpm(fac[mod - 1], now / mod, mod) * c % mod * fac[now % mod] % mod;
}

inline LL get_pow(LL x, LL k, LL mod) {
//cout << "get_pow " << x << " " << k << " " << mod << endl;
	return fpm(x, k, mod);
}

inline LL get_inv(LL x, LL mod) {
	x %= mod;
	return fpm(x, mod - 2, mod);
}

inline int solve(LL n, LL mod) {
	fac[0] = 1;
	for (int i = 1; i < mod; ++i) {
		fac[i] = fac[i - 1] * i % mod;
	}
	LL m = 1;
	for (; m * m <= n; ++m) {
		LL now = n / m;
		prep(now, mod, fr[m], fc[m]);
		f[m] = now - 1;
	}
	for (int i = 1; i < m; ++i) {
		LL now = i;
		prep(now, mod, gr[i], gc[i]);
		g[i] = i - 1;
	}
	
	for (int i = 2; i < m; ++i) {
		if (g[i] == g[i - 1]) {
			continue;
		}
		
		if (i == mod) {
			
			for (int j = 1; j < m && j <= n / i / i; ++j) {
				if (1LL * i * j < m) {
					//f[j] -= f[i * j] - g[i - 1];
					fc[j] = fc[j] * get_inv(fc[i * j], mod) % mod;
					fr[j] -= fr[i * j] + f[i * j];
					fc[j] = fc[j] * gc[i - 1] % mod;
					fr[j] += gr[i - 1] + g[i - 1];
				} else {
					//f[j] -= g[n / i / j] - g[i - 1];
					fc[j] = fc[j] * get_inv(gc[n / i / j], mod) % mod;
					fr[j] -= gr[n / i / j] + g[n / i / j];
					fc[j] = fc[j] * gc[i - 1] % mod;
					fr[j] += gr[i - 1] + g[i - 1];
				}
			}
			for (int j = m - 1; i <= j / i; --j) {
				//g[j] -= g[j / i] - g[i - 1];
				gc[j] = gc[j] * get_inv(gc[j / i], mod) % mod;
				gr[j] -= gr[j / i] + g[j / i];
				gc[j] = gc[j] * gc[i - 1] % mod;
				gr[j] += gr[i - 1] + g[i - 1];
			}
			
		} else {
		
			for (int j = 1; j < m && j <= n / i / i; ++j) {
				if (1LL * i * j < m) {
					//f[j] -= f[i * j] - g[i - 1];
					fc[j] = fc[j] * get_inv(fc[i * j] % mod * get_pow(i, f[i * j], mod) % mod, mod) % mod;
					fr[j] -= fr[i * j];
					fc[j] = fc[j] * gc[i - 1] % mod * get_pow(i, g[i - 1], mod) % mod;
					fr[j] += gr[i - 1];
				} else {
					//f[j] -= g[n / i / j] - g[i - 1];
					fc[j] = fc[j] * get_inv(gc[n / i / j] % mod * get_pow(i, g[n / i / j], mod), mod) % mod;
					fr[j] -= gr[n / i / j];
					fc[j] = fc[j] * gc[i - 1] % mod * get_pow(i, g[i - 1], mod) % mod;
					fr[j] += gr[i - 1];
				}
			}
			for (int j = m - 1; i <= j / i; --j) {
				//g[j] -= g[j / i] - g[i - 1];
				gc[j] = gc[j] * get_inv(gc[j / i] * get_pow(i, g[j / i], mod) % mod, mod) % mod;
				gr[j] -= gr[j / i];
				gc[j] = gc[j] * gc[i - 1] % mod * get_pow(i, g[i - 1], mod) % mod;
				gr[j] += gr[i - 1];
			}
			
		}
		
		for (int j = 1; j < m && j <= n / i / i; ++j) {
			if (1LL * i * j < m) {
				f[j] -= f[i * j] - g[i - 1];
			} else {
				f[j] -= g[n / i / j] - g[i - 1];
			}
		}
		
		for (int j = m - 1; i <= j / i; --j) {
			g[j] -= g[j / i] - g[i - 1];
		}
		
	}
	
	return fc[1];
}

int main() {
//cout << get_pow(2, 3, 3) << endl; return 0;
	int testcase, mod;
	LL n;
	cin >> testcase;
	for (int cs = 1; cs <= testcase; ++cs) {
		cin >> n >> mod;
		printf("Case #%d: %d\n", cs, (int)solve(n, (LL)mod));
	}
}
