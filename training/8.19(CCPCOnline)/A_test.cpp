#include <bits/stdc++.h>

const int n = 500;

int e[505][505];

int gomi() {
	static int deg[505];
	static bool use[505];
	
	memset(deg, 0, sizeof(deg));
	memset(use, 0, sizeof(use));
	
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) if (j != i)
			deg[i] += e[i][j];
	
	int ans = 0;
	while (1) {
		int mx = -1, u;
		for (int i = 1; i <= n; ++i) {
			if (use[i]) continue;
			if (deg[i] >= mx) {
				mx = deg[i]; u = i;
			}
		}
		if (mx <= 0) break;
		++ans;
		use[u] = 1;
		for (int i = 1; i <= n; ++i) if (e[u][i]) {
			e[u][i] = e[i][u] = 0;
			--deg[i];
		}
	}
	return ans;
}

int check(int x) {
	memset(e, 0, sizeof(e));
	for (int i = n - x + 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) if (j != i)
			e[i][j] = e[j][i] = 1;
	
	return gomi();
}

const char s[2][100] = {"NO", "YES!!!!!!!!!!!!!!"};

int main() {
	for (int i = 1; i <= 150; ++i) {
		int t = check(i);
		printf("%d: %d, %s\n", i, t, s[t >= i * 3]);
	}
	
	return 0;
}
