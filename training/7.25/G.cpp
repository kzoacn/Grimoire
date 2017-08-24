#include <bits/stdc++.h>
using namespace std;

const int MAXN = 111111;
const int MAXH = 20;
int fa[MAXN][MAXH];
int dep[MAXN], down[MAXN], up[MAXN], n, Q;
int cnt = 0, adj[MAXN];

struct Edge {
	int v, nxt, tp;
} e[MAXN << 1];

inline void addedge(int u, int v, int tp) {
	e[++cnt].v = v;
	e[cnt].tp = tp;
	e[cnt].nxt = adj[u];
	adj[u] = cnt;
}

inline void dfs(int u, int par, int tp) {
	fa[u][0] = par;
	dep[u] = dep[par] + 1;
	up[u] = up[par];
	down[u] = down[par];
	if (tp == 1) {
		down[u]++;
	}
	if (tp == -1) {
		up[u]++;
	}
	for (int h = 1; h < MAXH; ++h) {
		fa[u][h] = fa[fa[u][h - 1]][h - 1];
	}
	for (int p = adj[u]; p; p = e[p].nxt) {
		int v = e[p].v;
		if (v != par) {
			dfs(v, u, e[p].tp);
		}
	}
}

inline int get_lca(int u, int v) {
	if (dep[u] > dep[v]) {
		swap(u, v);
	}
	for (int h = 0; h < MAXH; ++h) {
		if ((dep[v] - dep[u]) & (1 << h)) {
			v = fa[v][h];
		}
	}
	for (int h = MAXH - 1; h >= 0; --h) {
		if (fa[u][h] != fa[v][h]) {
			u = fa[u][h];
			v = fa[v][h];
		}
	}
	return u == v ? u : fa[u][0];
}

int main() {
	cin >> n;
	for (int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		addedge(u, v, 1);
		addedge(v, u, -1);
	}
	
	dfs(1, 0, 0);
//for (int i = 1; i <= n; ++i) cout << i << ": " << dep[i] << " " << up[i] << " " << down[i] << endl;
	cin >> Q;
	
	for (; Q; --Q) {
		int u, v;
		scanf("%d%d", &u, &v);
		int lca = get_lca(u, v);
//cout << lca << " "<< dep[u] - dep[lca] << " " << up[u] - up[lca] << endl;
		if (dep[u] - dep[lca] == up[u] - up[lca] && dep[v] - dep[lca] == down[v] - down[lca]) {
			puts("Yes");
		} else {
			puts("No");
		}
	}
}
