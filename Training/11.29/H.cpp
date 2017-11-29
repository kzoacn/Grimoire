#include <bits/stdc++.h>

const int MAXN = 1e5 + 5;

int F, sg[MAXN];

int vis[MAXN];

inline int calc(int n, int m) {
	int x = n / m;
	int b = n - m * x, a = m - b;
	int res = 0;
	if (a & 1) res ^= sg[x];
	if (b & 1) res ^= sg[x + 1];
	return res;
}

void pretreatment() {
	const int Lim = 1e5;
	
	for (int i = 0; i < F; ++i)
		sg[i] = 0;
	
	for (int i = F; i <= Lim; ++i) {
		for (int L = 1, R; L <= i; L = R + 1) {
			static int t;
			
			R = i / (i / L);
			t = calc(i, L);
			if (t <= Lim) vis[t] = i;
			if (R > L) {
				t = calc(i, L + 1);
				if (t) vis[t] = i;
			}
//			std::cerr << i << " " << L << " " << R << std::endl;
		}
		for (int j = 0; j <= Lim; ++j) if (vis[j] != i) {
			sg[i] = j; break;
		}
	}
}

int main() {
#ifndef LOCAL
	freopen("nimg.in", "r", stdin);
	freopen("nimg.out", "w", stdout);
#endif
	int R;
	
	scanf("%d%d", &R, &F);
	pretreatment();
	while (R--) {
		static int g, x;
		scanf("%d", &g);
		int SG = 0;
		while (g--) {
			scanf("%d", &x);
			SG ^= sg[x];
		}
		printf("%d%c", (bool)SG, " \n"[R == 0]);
	}
	
	return 0;
}
