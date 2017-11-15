#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int MAXD = 20;
const int MAXN = 111111;
const int MAXK = 6;
const LL MOD = 1e9 + 7;
LL f[MAXN][MAXD], h1[MAXN][MAXK], h2[MAXN][MAXK], g[MAXN][MAXD], tmp[MAXN];
int n, m, son[MAXN], pos[MAXN];
LL ans;
vector<int> to[MAXN];

inline void dfs(int u, int fa) {
	f[u][0] = 1;
	for (int v : to[u]) {
		if (v == fa) {
			continue;
		}
		dfs(v, u);
	}
	for (int d = 1; d < MAXD; ++d) {
		for (int i = 0; i <= (int)to[u].size(); ++i) {
			memset(h1[i], 0, sizeof(h1[i]));
		}
		h1[0][0] = 1;
		int tot = 0;
		for (auto v : to[u]) {
			if (v == fa) {
				continue;
			}
			++tot;
			h1[tot][0] = 1;
			for (int i = 1; i <= m; ++i) {
				h1[tot][i] = (h1[tot - 1][i] + h1[tot - 1][i - 1] * f[v][d - 1]) % MOD;
			}
		}
		f[u][d] = h1[tot][m];
	}
}

inline void dfs2(int u, int fa) {
	for (auto v : to[u]) {
		if (v == fa) {
			continue;
		}
		g[v][0] = 1;
	}
	for (int d = 1; d < MAXD; ++d) {
		int tot = 0;
		tmp[++tot] = g[u][d - 1];
		for (auto v : to[u]) {
			if (v == fa) {
				continue;
			}
			son[++tot] = v;
			pos[v] = tot;
			tmp[tot] = f[v][d - 1];
		}
		for (int i = 0; i <= tot + 1; ++i) {
			memset(h1[i], 0, sizeof(h1[i]));
			memset(h2[i], 0, sizeof(h2[i]));
		}
		h1[0][0] = h2[0][0] = 1LL;
		for (int i = 1; i <= tot; ++i) {
			h1[i][0] = h2[i][0] = 1LL;
			for (int j = 1; j <= m; ++j) {
				h1[i][j] = (h1[i - 1][j] + h1[i - 1][j - 1] * tmp[i]) % MOD;
				h2[i][j] = (h2[i - 1][j] + h2[i - 1][j - 1] * tmp[tot - i + 1]) % MOD;
			}
		}
		for (int i = 1; i <= tot; ++i) {
			for (int j = 0; j <= m; ++j) {
				g[son[i]][d] = (g[son[i]][d] + h1[i - 1][j] * h2[tot - i][m - j]) % MOD;
			}
		}
	}
	for (auto v : to[u]) {
		if (v == fa) {
			continue;
		}
		dfs2(v, u);
	}
}

inline void solve(int u, int fa) {
	for (auto v : to[u]) {
		if (v != fa) {
			solve(v, u);
		}
	}
	ans = (ans + 1) % MOD;
	for (int d = 1; d < MAXD; ++d) {
		int tot = 0;
		tmp[++tot] = g[u][d - 1];
		for (auto v : to[u]) {
			if (v == fa) {
				continue;
			}
			tmp[++tot] = f[v][d - 1];
		}
		for (int i = 0; i <= tot; ++i) {
			memset(h1[i], 0, sizeof(h1[i]));
		}
		h1[0][0] = 1;
		for (int i = 1; i <= tot; ++i) {
			h1[i][0] = 1LL;
			for (int j = 1; j <= m; ++j) {
				h1[i][j] = (h1[i - 1][j] + h1[i - 1][j - 1] * tmp[i]) % MOD;
			}
		}
		ans = (ans + h1[tot][m]) % MOD;
	}
}

int main() {
	cin >> n >> m;
	for (int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		to[u].push_back(v);
		to[v].push_back(u);
	}
	
	dfs(1, 0);
	dfs2(1, 0);
	
	ans = 0;
	solve(1, 0);
	cout << ans << endl;
}
