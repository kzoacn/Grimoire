#include <bits/stdc++.h>

typedef long long ll;

int sorted[100005];

int hsh(int x) {
	return std::lower_bound(sorted + 1, sorted + *sorted + 1, x) - sorted;
} 

namespace PST {
	const int LIM = 100005 * 20;
	
	int ch[LIM][2], tot;
	ll sum[LIM];
	int root[100005];
	
	int newnode() {
		++tot;
		assert(tot < LIM);
		ch[tot][0] = ch[tot][1] = sum[tot] = 0;
		return tot;
	}
	
	int newcopy(int k) {
		++tot;
		assert(tot < LIM);
		ch[tot][0] = ch[k][0];
		ch[tot][1] = ch[k][1];
		sum[tot] = sum[k];
		return tot;
	}
	
	void build(int &k, int l, int r) {
		k = newnode();
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(ch[k][0], l, mid);
		build(ch[k][1], mid + 1, r);
	}
	
	void init() {
		tot = 0;
		root[0] = 0;
		build(root[0], 1, *sorted);
	}
	
	void add(int &k, int l, int r, int pos, int val) {
		k = newcopy(k);
		sum[k] += val;
		if (l == r) return;
		int mid = (l + r) >> 1;
		if (pos <= mid) add(ch[k][0], l, mid, pos, val);
		else add(ch[k][1], mid + 1, r, pos, val);
	}
	
	ll query(int k, int l, int r, int L, int R) {
		if (L <= l && r <= R) return sum[k];
		int mid = (l + r) >> 1;
		ll res = 0;
		if (L <= mid) res += query(ch[k][0], l, mid, L, R);
		if (mid < R) res += query(ch[k][1], mid + 1, r, L, R);
		return res;
	}
}

int n, m;
int c[100005];

int head[100005], nxt[100005 << 1], to[100005 << 1], ed;

void AddEdge(int u, int v) {
	nxt[++ed] = head[u]; head[u] = ed; to[ed] = v;
}

namespace HLD {
	int fa[100005], son[100005], depth[100005], top[100005];
	
	int DFS(int now) {
		PST::root[now] = PST::root[fa[now]];
		PST::add(PST::root[now], 1, *sorted, hsh(c[now]), c[now]);
		
		int res = 1, tmp, maxson = 0;
		son[now] = 0;
		for (int i = head[now]; i; i = nxt[i]) {
			if (to[i] == fa[now]) continue;
			fa[to[i]] = now;
			depth[to[i]] = depth[now] + 1;
			res += (tmp = DFS(to[i]));
			if (tmp > maxson) {
				maxson = tmp; son[now] = to[i];
			}
		}
		return res;
	}
	
	void DFS2(int now, int tp) {
		top[now] = tp;
		if (son[now]) DFS2(son[now], tp);
		for (int i = head[now]; i; i = nxt[i]) {
			if (to[i] == fa[now] || to[i] == son[now]) continue;
			DFS2(to[i], to[i]);
		}
	}
	
	void init() {
		fa[1] = 0;
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

int main() {
	while (~scanf("%d%d", &n, &m)) {
		memset(head, 0, sizeof head); ed = 0;
		
		for (int i = 1; i <= n; ++i) {
			scanf("%d", c + i);
			sorted[i] = c[i];
		}
		
		std::sort(sorted + 1, sorted + n + 1);
		*sorted = std::unique(sorted + 1, sorted + n + 1) - sorted - 1;
		
		for (int u, v, i = 1; i < n; ++i) {
			scanf("%d%d", &u, &v);
			AddEdge(u, v); AddEdge(v, u);
		}
		
		PST::init();
		HLD::init();
		
		for (int u, v, l, r, q = 1; q <= m; ++q) {
			scanf("%d%d%d%d", &u, &v, &l, &r);
			int lca = HLD::LCA(u, v);
			
			l = std::lower_bound(sorted + 1, sorted + *sorted + 1, l) - sorted;
			r = std::upper_bound(sorted + 1, sorted + *sorted + 1, r) - sorted - 1;
			
			ll ans = PST::query(PST::root[u], 1, *sorted, l, r) + PST::query(PST::root[v], 1, *sorted, l, r) - 
					 PST::query(PST::root[lca], 1, *sorted, l, r) - PST::query(PST::root[HLD::fa[lca]], 1, *sorted, l, r);
			printf("%lld%c", ans, " \n"[q == m]);
		}
	}
	
	return 0;
}
