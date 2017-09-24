#include <bits/stdc++.h>
using namespace std;

const int MOD = 105225319;
const int MAXN = 1010;
const int inv2 = 52612660;

int pw[MAXN * MAXN], c[MAXN][MAXN], f[MAXN], g[MAXN], h[MAXN];
int n, m, testcase;

inline int fpm(int x, int k, int mod) {
	int ret = 1;
	for (; k; k >>= 1) {
		if (k & 1) {
			ret = 1LL * ret * x % mod;
		}
		x = 1LL * x * x % mod;
	}
	return ret;
}

int main() {
//assert(2 * inv2 % MOD == 1);
	for (int i = 0; i < MAXN; ++i) {
		c[i][0] = c[i][i] = 1;
		for (int j = 1; j < i; ++j) {
			c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % MOD;
		}
	}

	scanf("%d", &testcase);
	for (int cs = 1; cs <= testcase; ++cs) {
		scanf("%d%d", &n, &m);
		if (n == 1) {
			printf("Case #%d: %d\n", cs, 0);
			continue;
		}
		pw[0] = 1;
		for (int i = 1; i <= n * n; ++i) {
			pw[i] = 1LL * pw[i - 1] * (m + 1) % MOD;
		}
		f[0] = 1;
		for (int i = 1; i <= n; ++i) {
			f[i] = 0;
			for (int j = 1; j <= i; ++j) {
				f[i] = (f[i] + 2LL * c[i - 1][j - 1] * pw[j * (i - j)]) % MOD;
			}
			//printf("f[%d] = %d\n", i, f[i]);
		}
		
		g[1] = 1;
		for (int i = 2; i <= n; ++i) {
			g[i] = f[i];
			for (int j = 1; j < i; ++j) {
				g[i] = (g[i] - 2LL * c[i - 1][j - 1] * g[j] % MOD * f[i - j]) % MOD;
			}
			//printf("g[%d] = %d\n", i, g[i]);
			g[i] = 1LL * g[i] * inv2 % MOD;
			//printf("g[%d] = %d\n", i, g[i]);
			if (g[i] < 0) {
				g[i] += MOD;
			}
		}
		
		h[0] = h[1] = 1;
		for (int i = 2; i <= n; ++i) {
			h[i] = 0;
			for (int j = 1; j <= i; ++j) {
				h[i] = (h[i] + 1LL * c[i - 1][j - 1] * h[i - j] % MOD * g[j]) % MOD;
			}
		}
		
		printf("Case #%d: %d\n", cs, h[n]);
//puts("");
//puts("");
	}
}


