#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
const int MAXM = 256;
const int MOD = 998244353;
int cnt, n, m, testcase, adj[MAXN], dp[MAXN][MAXM][2];
int temp[MAXM * 2], f[MAXM * 2], size[MAXN];

struct Edge {
	int v, nxt;
} e[MAXN];

inline void add_edge(int u, int v) {
	e[++cnt].v = v;
	e[cnt].nxt = adj[u];
	adj[u] = cnt;
}

inline void print(int u) {
	cout << "now print dp of " << u << endl;
	cout << "dp[0]:";
	for (int i = 0; i < m; ++i) {
		cout << " " << dp[u][i][0];
	}
	cout << endl;
	
	cout << "dp[1]:";
	for (int i = 0; i < m; ++i) {
		cout << " " << dp[u][i][1];
	}
	cout << endl;
}

int C = 0;

inline void dfs(int u, int fa) {
	for (int p = adj[u]; p; p = e[p].nxt) {
		if (e[p].v != fa) {
			dfs(e[p].v, u);
		}
	}
	size[u] = 1;
	for (int i = 0; i <= m + m; ++i) {
		f[i] = 0;
	}
	f[0] = 1;
	for (int p = adj[u]; p; p = e[p].nxt) {
		int v = e[p].v;
		if (v == fa) {
			continue;
		}
		for (int i = 0; i <= m + m; ++i) {
++C;
			temp[i] = 0;
		}
		for (register int i = 0; i <= min(m - 1, size[v] / 2); ++i) {
			for (register int j = 0; j <= min(m - 1, size[u] / 2); ++j) {
				temp[i + j] = (temp[i + j] + (dp[v][i][0] + dp[v][i][1] * 2LL) * f[j]) % MOD;
++C;
			}
		}
		for (register int i = 0; i < m; ++i) {
++C;
			f[i] = temp[i];
		}
		for (int i = m; i <= m + m; ++i) {
++C;
			f[i - m] = (f[i - m] + temp[i]) % MOD;
			f[i] = 0;
		}
		size[u] += size[v];
	}
	for (int i = 0; i < m; ++i) {
++C;
		dp[u][i][0] = f[i];
	}
		
	size[u] = 1;
	for (int i = 0; i <= m + m; ++i) {
		f[i] = 0;
	}
	f[0] = 1;
	for (int p = adj[u]; p; p = e[p].nxt) {
		int v = e[p].v;
		if (v == fa) {
			continue;
		}
		for (int i = 0; i <= m + m; ++i) {
++C;
			temp[i] = 0;
		}
		for (int i = 0; i <= min(m - 1, size[v] / 2); ++i) {
			for (int j = 0; j <= min(m - 1, size[u] / 2); ++j) {
				temp[i + j] = (temp[i + j] + (dp[v][i][0] * 2LL + dp[v][i][1] * 2LL) * f[j]) % MOD;
++C;
			}
		}
		for (int i = 0; i < m; ++i) {
++C;
			f[i] = temp[i];
		}
		for (int i = m; i <= m + m; ++i) {
++C;
			f[i - m] = (f[i - m] + temp[i]) % MOD;
			f[i] = 0;
		}
		size[u] += size[v];
	}
	for (int i = 0; i < m; ++i) {
++C;
		int j = (i - 1 + m) % m;
		dp[u][i][1] = f[j] - dp[u][j][0];
	}
//print(u);
}

int main() {
	scanf("%d", &testcase);
	for (; testcase; --testcase) {
		scanf("%d%d", &n, &m);
		memset(adj, 0, sizeof(*adj) * (n + 1));
		cnt = 0;
		for (int i = 1; i < n; ++i) {
			int u, v;
			scanf("%d%d", &u, &v);
			add_edge(u, v);
			add_edge(v, u);
		}
		
		dfs(1, 0);
		
		int ans = (dp[1][0][0] + dp[1][0][1]) % MOD;
		ans = (ans + MOD) % MOD;
		printf("%d\n", ans);
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < m; ++j) {
				dp[i][j][0] = dp[i][j][1] = 0;
			}
		}
		cout << C << endl;
	}
}
