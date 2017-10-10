#include <bits/stdc++.h>

const int Mod = 1e9 + 7;

int qpow(int a, int x) {
	int res = 1;
	for (; x; x >>= 1) {
		if (x & 1) res = 1ll * res * a % Mod;
		a = 1ll * a * a % Mod;
	}
	return res;
}

int inv2, inv3;

int g[100005], h[100005];

inline int C2(int x) {
	return 1ll * x * (x - 1) % Mod * inv2 % Mod;
}

inline int C3(int x) {
	return 1ll * x * (x - 1) % Mod * (x - 2) % Mod * inv3 % Mod * inv2 % Mod;
}

void pretreatment() {
	const int lim = 1e5;
	
	g[0] = g[1] = 1;
	h[0] = 1, h[1] = 2;
	
	for (int i = 2; i <= lim; ++i) {
		g[i] = (1ll * g[i - 1] * h[i - 2] + C2(g[i - 1] + 1)) % Mod;
		h[i] = (h[i - 1] + g[i]) % Mod;
	}
}

int main() {
	inv2 = qpow(2, Mod - 2);
	inv3 = qpow(3, Mod - 2);
	pretreatment();
	
	for (int k; ~scanf("%d", &k) && k; ) {
		if (k & 1) {
			int ans = (1ll * C2(g[k >> 1] + 1) * h[(k >> 1) - 1] + C3(g[k >> 1] + 2)) % Mod;
			printf("%d\n", ans);
		}
		else printf("%d\n", C2(g[k >> 1] + 1));
	}
	
	return 0;
}
