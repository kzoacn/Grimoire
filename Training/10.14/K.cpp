#include <bits/stdc++.h>

typedef long long ll;

int n, m;

int head[200005], nxt[200005 << 1], to[200005 << 1], ed;

void AddEdge(int u, int v) {
	nxt[++ed] = head[u]; head[u] = ed; to[ed] = v;
}

namespace HLD {
	int fa[200005], son[200005], depth[200005], top[200005], dfn[200005];

	int DFS(int now) {
		son[now] = 0;
		int res = 1, tmp, maxson = 0;
		for (int i = head[now]; i; i = nxt[i]) {
			if (to[i] == fa[now]) continue;
			fa[to[i]] = now;
			depth[to[i]] = depth[now] + 1;
			tmp = DFS(to[i]);
			res += tmp;
			if (tmp > maxson) {
				maxson = tmp; son[now] = to[i];
			}
		}
		return res;
	}

	void DFS2(int now, int tp) {
		dfn[now] = ++*dfn;
		if (son[now]) DFS2(son[now], tp);
		for (int i = head[now]; i; i = nxt[i]) {
			if (to[i] == fa[now] || to[i] == son[now]) continue;
			DFS2(to[i], to[i]);
		}
	}
	
	void init() {
		DFS(1);
		DFS2(1, 1);
	}
	
	int LCA(int u, int v) {
		while (top[u] != top[v]) {
			if (depth[top[u]] < depth[top[v]]) std::swap(u, v);
			u = fa[top[u]];
		}
		return depth[u] < depth[v] ? u : v;
	}
}

int ff[200005];

int Fa(int x) {
	return ff[x] == x ? x : ff[x] = Fa(ff[x]);
}

struct Edge {
	int u, v;
	
	Edge() {}
	Edge(int u, int v): u(u), v(v) {}
} edge[500005];

bool added[500005];

std::vector<int> ans;

int val[200005];

int DFS3(int now) {
	int res = val[now];
	for (int i = head[now]; i; i = nxt[i]) {
		if (to[i] == HLD::fa[now]) continue;
		res += DFS3(to[i]);
	}
	
//	std::cerr << now << " " << res << std::endl;
	
	if (res == m - n + 1) ans.push_back(now);
	return res;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) ff[i] = i;
	
	for (int i = 1; i <= m; ++i) {
		static int u, v;
		
		scanf("%d%d", &u, &v);
		edge[i] = Edge(u, v);
		if (Fa(u) != Fa(v)) {
//			std::cerr << u << " " << v << std::endl;
			
			AddEdge(u, v);
			AddEdge(v, u);
			added[i] = 1;
			ff[ff[u]] = ff[v];
		}
	}
	
	HLD::init();
	
	for (int i = 1; i <= m; ++i) if (!added[i]) {
		int u = edge[i].u, v = edge[i].v;
		
		int lca = HLD::LCA(u, v);
		
		std::cerr << u << " " << v << " " << lca << std::endl;
		
		++val[u];
		++val[v];
		--val[lca];
		if (lca != 1) --val[HLD::fa[lca]];
	}
	
	DFS3(1);
	
	std::sort(ans.begin(), ans.end());
	
	printf("%d\n", (int)ans.size());
	for (int i = 0; i < (int)ans.size(); ++i)
		printf("%d%c", ans[i], " \n"[i == (int)ans.size() - 1]);
	
	return 0;
}
