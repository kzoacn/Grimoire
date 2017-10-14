#include <bits/stdc++.h>

typedef long long ll;

const int Lim = 1e5;

namespace PST {
	struct Node {
		Node *ch[2];
		ll sum;
		
		Node() {
			ch[0] = ch[1] = 0;
			sum = 0;
		}
	} *root[100005];
	
	void build(Node *&k, int l, int r) {
		k = new Node();
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(k->ch[0], l, mid);
		build(k->ch[1], mid + 1, r);
	}
	
	void add(Node *&k, int l, int r, int pos, ll val) {
		k = new Node(*k);
		k->sum += val;
		if (l == r) return;
		int mid = (l + r) >> 1;
		if (pos <= mid) add(k->ch[0], l, mid, pos, val);
		else add(k->ch[1], mid + 1, r, pos, val);
	}
	
	ll query(Node *k, int l, int r, int L, int R) {
		if (L <= l && r <= R) return k->sum;
		int mid = (l + r) >> 1;
		ll res = 0;
		if (L <= mid) res += query(k->ch[0], l, mid, L, R);
		if (mid < R) res += query(k->ch[1], mid + 1, r, L, R);
		return res;
	}
	
	//
	
	void init() {
		build(root[0], 1, Lim);
	}
	
	void Insert(int T, int r, int t) {
		root[T] = root[T - 1];
		add(root[T], 1, Lim, r, t);
	}
	
	ll Query(int L, int R, int r) {
		if (r == 1) return 0;
		return query(root[R], 1, Lim, 1, r - 1) - query(root[L - 1], 1, Lim, 1, r - 1);
	}
}

int n, r[100005], t[100005];
int head[100005], nxt[100005], to[100005], ed;

void AddEdge(int u, int v) {
	nxt[++ed] = head[u]; head[u] = ed; to[ed] = v;
}

int dfn[100005];
ll ans[100005];

void DFS(int now) {
	dfn[now] = ++*dfn;
	PST::Insert(dfn[now], r[now], t[now]);
	
	for (int i = head[now]; i; i = nxt[i])
		DFS(to[i]);
	
	ans[now] = PST::Query(dfn[now], *dfn, r[now]);
}

int main() {
	int root;
	
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		static int fa;
		
		scanf("%d%d%d", &fa, r + i, t + i);
		
		if (fa == -1) root = i;
		else AddEdge(fa, i);
	}
	
	PST::init();
	DFS(root);
	
	for (int i = 1; i <= n; ++i)
		printf("%lld\n", ans[i]);
	
	return 0;
}
