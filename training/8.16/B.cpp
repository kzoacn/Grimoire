#include <bits/stdc++.h>

int f[100005];

int calc(int Mod) {
	f[0] = 2 % Mod, f[1] = 10 % Mod;
	
	for (int i = 2; ; ++i) {
		f[i] = (f[i - 1] * 10 - f[i - 2] + Mod) % Mod;
		if (f[i - 1] == f[0] && f[i] == f[1]) return i - 1;
	}
	return -1;
}

int qpow(int a, int x, int Mod) {
	int res = 1;
	for (; x; x >>= 1) {
		if (x & 1) res = 1ll * res * a % Mod;
		a = 1ll * a * a % Mod;
	}
	return res;
}

int n, m;

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d%d", &n, &m);
		
		int cir = calc(m);
		
		printf("Case #%d: %d\n", kase, f[(qpow(2, n, cir) + 1) % cir] - 1);
	}
	
	return 0;
}
