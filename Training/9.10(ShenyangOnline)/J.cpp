#include <bits/stdc++.h>

int n;

int head[10005], nxt[10005 << 1], to[10005 << 1], ed;

void AddEdge(int u, int v) {
	nxt[++ed] = head[u]; head[u] = ed; to[ed] = v;
}

namespace HLDecomp {
	int fa[10005], son[10005], depth[10005], top[10005], dfn[10005], sz[10005], tot;
	
	int DFS(int now) {
		son[now] = 0; sz[now] = 1;
		int maxson = 0, tmp;
		for (int i = head[now]; i; i = nxt[i]) {
			if (to[i] == fa[now]) continue;
			fa[to[i]] = now;
			depth[to[i]] = depth[now] + 1;
			tmp = DFS(to[i]);
			sz[now] += tmp;
			if (tmp > maxson) {
				maxson = tmp;
				son[now] = to[i];
			}
		}
		return sz[now];
	}
	
	void DFS2(int now, int tp) {
		dfn[now] = ++tot;
		top[now] = tp;
		if (son[now]) DFS2(son[now], tp);
		for (int i = head[now]; i; i = nxt[i]) {
			if (to[i] == fa[now] || to[i] == son[now]) continue;
			DFS2(to[i], to[i]);
		}
	}
	
	void init() {
		tot = 0;
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

struct Query {
	int u, v, lca;
	
	bool operator < (const Query &rhs) const {
		using HLDecomp::depth;
		
		return depth[lca] < depth[rhs.lca];
	}
	
	void scan() {
		scanf("%d%d", &u, &v); ++u; ++v;
		lca = HLDecomp::LCA(u, v);
	}
} qry[50005];

namespace BIT {
	int c[10005];
	
	void init() { memset(c, 0, sizeof c); }
	
#define lowbit(x) ((x) & -(x))
	
	void add(int x, int y) {
		for (int i = x; i <= n; i += lowbit(i))
			c[i] += y;
	}
	
	int query(int x) {
		int res = 0;
		for (int i = x; i > 0; i -= lowbit(i))
			res += c[i];
		return res;
	}
}

int main() {
	while (~scanf("%d", &n)) {
		memset(head, 0, sizeof head); ed = 0;
		BIT::init();
		
		++n;
		
		for (int u, v, i = 1; i < n; ++i) {
			scanf("%d%d", &u, &v); ++u, ++v;
			AddEdge(u, v);
			AddEdge(v, u);
		}
		
		HLDecomp::init();
		
		int m; scanf("%d", &m);
		for (int i = 1; i <= m; ++i) qry[i].scan();
		
		std::sort(qry + 1, qry + m + 1);
		
		int ans = 0;
		
		for (int i = m; i; --i) {
			using HLDecomp::dfn;
			using HLDecomp::sz;
			using HLDecomp::fa;
			
			int u = qry[i].u, v = qry[i].v, lca = qry[i].lca;
			
			int cnt = BIT::query(dfn[u]) + BIT::query(dfn[v]) - BIT::query(dfn[fa[lca]]) * 2;
			
//			std::cerr << u << " " << v << " " << cnt << std::endl;
			
			if (!cnt) {
				++ans;
				BIT::add(dfn[lca], 1);
				BIT::add(dfn[lca] + sz[lca], -1);
			}
		}
		
		printf("%d\n", ans);
	}
	
	return 0;
}
