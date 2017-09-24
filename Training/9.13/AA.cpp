#include <bits/stdc++.h>

typedef long long ll;

int n, a[100005];

int head[100005], nxt[100005 << 1], to[100005 << 1], ed;

void AddEdge(int u, int v) {
	nxt[++ed] = head[u]; head[u] = ed; to[ed] = v;
}

namespace SegTree { // suffix sum
	int ch[100005 << 2];
	ll sum[100005 << 2];
	
	void init() { memset(sum, 0, sizeof sum); }
	
	void modify(int k, int l, int r, int pos, ll val) {
		if (l == r) {
			sum[k] = val;
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) modify(k << 1, l, mid, pos, val);
		else modify(k << 1 | 1, mid + 1, r, pos, val);
		sum[k] = sum[k << 1] + sum[k << 1 | 1];
	}
	
	ll query(int k, int l, int r, int L, int R) {
		if (L <= l && r <= R) return sum[k];
		int mid = (l + r) >> 1;
		ll res = 0;
		if (L <= mid) res += query(k << 1, l, mid, L, R);
		if (mid < R) res += query(k << 1 | 1, mid + 1, r, L, R);
		return res;
	}
}

int sorted[100005];

int hsh(int x) {
	return std::lower_bound(sorted + 1, sorted + *sorted + 1, x) - sorted;
}

ll ans[100005];

void DFS(int now, int fa) {
	int ch[2], ch_cnt = 0;
	for (int i = head[now]; i; i = nxt[i]) {
		if (to[i] == fa) continue;
		ch[ch_cnt++] = to[i];
		DFS(to[i], now);
	}
	
	assert(ch_cnt <= 2);
	
	
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		memset(head, 0, sizeof head); ed = 0;
		
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			st[i].clear();
			
			scanf("%d", a + i);
			sorted[i] = a[i];
		}
		for (int u, v, i = 1; i < n; ++i) {
			scanf("%d%d", &u, &v);
			AddEdge(u, v);
			AddEdge(v, u);
		}
		
		std::sort(sorted + 1, sorted + n + 1);
		*sorted = std::unique(sorted + 1, sorted + n + 1) - sorted - 1;
		
		SegTree::init();
		
		DFS(1, 0);
		
		for (int i = 1; i <= n; ++i)
			printf("%lld%c", ans[i], " \n"[i == n]);
	}
	
	return 0;
}
