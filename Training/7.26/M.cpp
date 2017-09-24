#include <bits/stdc++.h>
using namespace std;

const int MAXN = 111111;
const int MAXH = 20;
int fa[MAXN][MAXH], dep[MAXN], node[MAXN], n, Q, testcase;
double f[MAXN], g[MAXN], tot_f[MAXN], tot_g[MAXN];
vector<int> to[MAXN];

inline void dfs1(int u, int par) {
	fa[u][0] = par;
	for (int h = 1; h < MAXH; ++h) {
		fa[u][h] = fa[fa[u][h - 1]][h - 1];
	}
	dep[u] = dep[par] + 1;
	bool flag = false;
	double tmp = 1.0;
	for (auto v : to[u]) {
		if (v == par) {
			continue;
		}
		flag = true;
		dfs1(v, u);
		tmp += 1.0 + f[v];
	}
	if (par == 0) {
		return;
	}
	if (!flag) {
		f[u] = 1;
		return;
	} else {
		f[u] = tmp;
	}
}

inline void dfs2(int u, int par) {
	//int d = to[u].size();
	double total = 0.0;
	for (auto v : to[u]) {
		if (v == par) {
			continue;
		}
		total += 1 + f[v];
	}
	if (u == 1) {
		for (auto v : to[u]) {
			g[v] = 1 + total - 1 - f[v];
		}
	} else {
		for (auto v : to[u]) {
			g[v] = 2 + g[u] + total - 1 - f[v];
		}
	}
	for (auto v : to[u]) {
		if (v != par) {
			dfs2(v, u);
		}
	}
}

inline int get_lca(int u, int v) {
	if (dep[u] > dep[v]) {
		swap(u, v);
	}
	for (int i = 0; i < MAXH; ++i) {
		if ((dep[v] - dep[u]) & (1 << i)) {
			v = fa[v][i];
		}
	}
	for (int i = MAXH - 1; i >= 0; --i) {
		if (fa[u][i] != fa[v][i]) {
			u = fa[u][i];
			v = fa[v][i];
		}
	}
	return u == v ? u : fa[u][0];
}

inline void dfs3(int u, int par) {
	tot_f[u] = tot_f[par] + f[u];
	tot_g[u] = tot_g[par] + g[u];
	for (auto v : to[u]) {
		if (v != par) {
			dfs3(v, u);
		}
	}
}

inline double get_ans(int u, int v) {
	int lca = get_lca(u, v);
	return tot_f[u] - tot_f[lca] + tot_g[v] - tot_g[lca];
}

int main() {
	scanf("%d", &testcase);
	for (int cs = 1; cs <= testcase; ++cs) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			to[i].clear();
		}
		for (int i = 1; i < n; ++i) {
			int u, v;
			scanf("%d%d", &u, &v);
			++u;
			++v;
			to[u].push_back(v);
			to[v].push_back(u);
		}
		
		dfs1(1, 0);
		g[0] = g[1] = 0;
		dfs2(1, 0);
		dfs3(1, 0);
		scanf("%d", &Q);
		if (cs > 1) {
			puts("");
		}
		for (; Q; --Q) {
			int cnt;
			scanf("%d", &cnt);
			scanf("%d", &node[0]);
			++node[0];
			double ans = 0.0;
			for (int i = 1; i <= cnt; ++i) {
				scanf("%d", &node[i]);
				++node[i];
				ans += get_ans(node[i - 1], node[i]);
			}
			printf("%.4f\n", ans);
		}
	}
}
