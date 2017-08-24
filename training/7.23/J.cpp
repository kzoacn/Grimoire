#include <bits/stdc++.h>

typedef long long ll;

const int Mod = 1e9 + 7;

ll b[205 << 1];

ll linear_recurrence(ll n, int m, ll a[], ll c[], int p) {
	ll v[205] = {1 % p}, u[205 << 1], msk = !!n;
	for (ll i = n; i > 1; i >>= 1)
		msk <<= 1;
	for (ll x = 0; msk; msk >>= 1, x <<= 1) {
		std::fill_n(u, m << 1, 0);
		int b = !!(n & msk);
		x |= b;
		if (x < m)
			u[x] = 1 % p;
		else {
			for (int i = 0; i < m; ++i)
				for (int j = 0, t = i + b; j < m; ++j, ++t)
					u[t] = (u[t] + v[i] * v[j]) % p;
			for (int i = (m << 1) - 1; i >= m; --i)
				for (int j = 0, t = i - m; j < m; ++j, ++t)
					u[t] = (u[t] + c[j] * u[i]) % p;
		}
		std::copy(u, u + m, v);
	}
	// a[n] = v[0] * a[0] + v[1] * a[1] + ... + v[m - 1] * a[m - 1].
	for (int i = m; i < 2 * m; ++i) {
		a[i] = 0;
		for (int j = 0; j < m; ++j)
			a[i] = (a[i] + (ll)c[j] * a[i + j - m]) % p;
	}
	for (int j = 0; j < m; ++j) {
		b[j] = 0;
		for (int i = 0; i < m; ++i)
			b[j] = (b[j] + v[i] * a[i + j]) % p;
	}
	for (int j = 0; j < m; ++j)
		a[j] = b[j];
	
	return a[0];
}

ll n;
bool U[205], D[205];
ll f[205], g[205], gg[205];

int main() {
	int cnt;
	while (~scanf("%lld", &n)) {
		memset(U, 0, sizeof U);
		memset(D, 0, sizeof D);
		
		scanf("%d", &cnt);
		for (int x, i = 1; i <= cnt; ++i) {
			scanf("%d", &x);
			U[x] = 1;
		}
		scanf("%d", &cnt);
		for (int x, i = 1; i <= cnt; ++i) {
			scanf("%d", &x);
			D[x] = 1;
		}
		
		memset(g, 0, sizeof g);
		g[0] = 1;
		for (int i = 1; i <= 200; ++i) {
			for (int j = 1; j <= i; ++j) if (U[j])
				g[i] = (g[i] + g[i - j]) % Mod;
		}
		for (int i = 1; i <= 200; ++i) if (!D[i]) g[i] = 0;
		
		memset(f, 0, sizeof f);
		f[0] = 1;
		for (int i = 1; i <= 200; ++i) {
			for (int j = 1; j <= i; ++j)
				f[i] = (f[i] + f[i - j] * g[j]) % Mod;
		}
		
/*		for (int i = 1; i <= 10; ++i)
			printf("%lld%c", f[i], " \n"[i == 10]);
		for (int i = 1; i <= 10; ++i)
			printf("%lld%c", g[i], " \n"[i == 10]);
*/		
		if (n <= 200) {
			printf("%lld\n", f[n]); continue;
		}
		
		memset(gg, 0, sizeof gg);
		for (int i = 0; i < 200; ++i)
			gg[i] = g[200 - i];
		
		printf("%lld\n", linear_recurrence(n, 200, f, gg, Mod));
	}
	
	return 0;
}
