#include <bits/stdc++.h>

int n, q;
int head[200005], nxt[200005 << 1], to[200005 << 1], d[200005 << 1], ed;

void AddEdge(int u, int v, int w) {
	nxt[++ed] = head[u]; head[u] = ed; to[ed] = v; d[ed] = w;
}

int sorted[200005 << 1];

int hsh(int x) {
	return std::lower_bound(sorted + 1, sorted + *sorted + 1, x) - sorted;
}

int fa[200005], son[200005], depth[200005], top[200005], dfn_st[200005], dfn_ed[200005], inv[200005 << 1], tot;

int val[200005], hshval[200005];
bool vis[200005];

int DFS(int now) {
	son[now] = 0;
	int res = 1, tmp, maxson = 0;
	for (int i = head[now]; i; i = nxt[i]) {
		if (to[i] == fa[now]) continue;
		fa[to[i]] = now;
		depth[to[i]] = depth[now] + 1;
		val[to[i]] = d[i];
		hshval[to[i]] = hsh(d[i]);
		tmp = DFS(to[i]);
		res += tmp;
		if (tmp > maxson) {
			maxson = tmp; son[now] = to[i];
		}
	}
	return res;
}

void DFS2(int now, int tp) {
	dfn_st[now] = ++tot; inv[tot] = now;
	if (son[now]) DFS2(son[now], tp);
	for (int i = head[now]; i; i = nxt[i]) {
		if (to[i] == fa[now] || to[i] == son[now]) continue;
		DFS2(to[i], to[i]);
	}
	dfn_ed[now] = ++tot; inv[tot] = now;
}

int LCA(int u, int v) {
	while (top[u] != top[v]) {
		if (depth[top[u]] < depth[top[v]]) std::swap(u, v);
		u = fa[top[u]];
	}
	return depth[u] < depth[v] ? u : v;
}

const int BLK = 650;
int pos[200005 << 1], cnt[200005 << 1];

int Cnt[BLK], maxb;

void modify(int x) {
	if (vis[x]) {
		--cnt[hshval[x]];
		if (cnt[hshval[x]] == 0) ++Cnt[pos[hshval[x]]];
		vis[x] = 0;
	}
	else {
		++cnt[hshval[x]];
		if (cnt[hshval[x]] == 1) --Cnt[pos[hshval[x]]];
		vis[x] = 1;
	}
}

int query_mex() {
	for (int i = 1; i <= maxb; ++i) {
		if (Cnt[i]) {
			for (int j = (i - 1) * BLK + 1; j <= i * BLK; ++j) if (!cnt[j])
				return sorted[j];
		}
	}
	assert(0);
	return -1;
}

struct Query {
	int u, v, lca, id;
	
	void scan(int ID) {
		scanf("%d%d", &u, &v);
		if (dfn_st[u] > dfn_st[v]) std::swap(u, v);
		id = ID;
		int __lca = LCA(u, v);
		if (__lca == u) {
			lca = u;
			u = dfn_st[u];
			v = dfn_st[v];
		}
		else {
			lca = 0;
			u = dfn_ed[u];
			v = dfn_st[v];
		}
	}
	
	bool operator < (const Query &rhs) const {
		return pos[u] == pos[rhs.u] ? v < rhs.v : pos[u] < pos[rhs.u];
	}
} qry[100005];

int ans[100005];

int main() {
	sorted[++*sorted] = 0;
	
	scanf("%d%d", &n, &q);
	for (int i = 1; i < n; ++i) {
		static int u, v, w;
		
		scanf("%d%d%d", &u, &v, &w);
		AddEdge(u, v, w);
		AddEdge(v, u, w);
		
		sorted[++*sorted] = w;
		sorted[++*sorted] = w + 1;
	}
	
	std::sort(sorted + 1, sorted + *sorted + 1);
	*sorted = std::unique(sorted + 1, sorted + *sorted + 1) - sorted - 1;
	
	DFS(1);
	DFS2(1, 1);
	
	for (int i = 1; i <= q; ++i)
		qry[i].scan(i);
	
	for (int i = 1; i <= n * 2 || i <= *sorted; ++i) {
		pos[i] = (i - 1) / BLK + 1;
		++Cnt[pos[i]];
	}
	maxb = (*sorted - 1) / BLK + 1;
	
	std::sort(qry + 1, qry + q + 1);
	
	int L = 1, R = 0;
	for (int i = 1; i <= q; ++i) {
		int x = qry[i].u, y = qry[i].v;
		while (R < y) {
			++R; modify(inv[R]);
		}
		while (R > y) {
			modify(inv[R]); --R;
		}
		while (L > x) {
			--L; modify(inv[L]);
		}
		while (L < x) {
			modify(inv[L]); ++L;
		}
		
		if (qry[i].lca) modify(qry[i].lca);
		
		ans[qry[i].id] = query_mex();
		
		if (qry[i].lca) modify(qry[i].lca);
	}
	
	for (int i = 1; i <= q; ++i)
		printf("%d\n", ans[i]);
	
	return 0;
}
