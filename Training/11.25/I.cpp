#include <bits/stdc++.h>

namespace Scanner {
	/*const int L = (1 << 15) + 5;
	char buffer[L], *S, *T;
	
	__inline char getc() {
		if (S == T) {
			T = (S = buffer) + fread(buffer, 1, L, stdin);
			if (S == T)
				return -1;
		}
		return *S++;
	}*/
	
	template <class Type>
	__inline void scan(Type &x) {
		register char ch; x = 0;
		for (ch = getchar(); ~ch && (ch < '0' || ch > '9'); ch = getchar());
		for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
	}
} using Scanner::scan;

const int MAXN = 1e6 + 5;

const int INF = 0x3f3f3f3f;

int n, a[MAXN];
int head[MAXN], nxt[MAXN], to[MAXN], ed;

void AddEdge(int u, int v) {
	nxt[++ed] = head[u]; head[u] = ed; to[ed] = v;
}

int dfn[MAXN], idfn[MAXN], sz[MAXN];

void DFS(int now) {
	sz[now] = 1;
	dfn[now] = ++*dfn; idfn[*dfn] = now;
	
	for (int i = head[now]; i; i = nxt[i]) {
		DFS(to[i]);
		sz[now] += sz[to[i]];
	}
}

namespace SegTree {
	int mx[MAXN << 2], mn[MAXN << 2], tag[MAXN << 2];
	
	inline void update(int k) {
		mx[k] = std::max(mx[k << 1], mx[k << 1 | 1]);
		mn[k] = std::min(mn[k << 1], mn[k << 1 | 1]);
	}
	
	void build(int k, int l, int r) {
		tag[k] = 0;
		if (l == r) {
			mx[k] = mn[k] = a[idfn[l]];
			return;
		}
		int mid = (l + r) >> 1;
		build(k << 1, l, mid);
		build(k << 1 | 1, mid + 1, r);
		update(k);
	}
	
	inline void down(int k) {
		if (tag[k]) {
			mx[k << 1] += tag[k];
			mn[k << 1] += tag[k];
			mx[k << 1 | 1] += tag[k];
			mn[k << 1 | 1] += tag[k];
			tag[k << 1] += tag[k];
			tag[k << 1 | 1] += tag[k];
			tag[k] = 0;
		}
	}
	
	void add(int k, int l, int r, int L, int R, int val) {
		if (L <= l && r <= R) {
			mx[k] += val;
			mn[k] += val;
			tag[k] += val;
			return;
		}
		int mid = (l + r) >> 1;
		down(k);
		if (L <= mid) add(k << 1, l, mid, L, R, val);
		if (mid < R) add(k << 1 | 1, mid + 1, r, L, R, val);
		update(k);
	}
	
	void query(int k, int l, int r, int L, int R, int &Max, int &Min) {
		if (L <= l && r <= R) {
			Max = std::max(Max, mx[k]);
			Min = std::min(Min, mn[k]);
			return;
		}
		int mid = (l + r) >> 1;
		down(k);
		if (L <= mid) query(k << 1, l, mid, L, R, Max, Min);
		if (mid < R) query(k << 1 | 1, mid + 1, r, L, R, Max, Min);
	}
}

int main() {
	int caseCnt; scan(caseCnt);
	while (caseCnt--) {
		scan(n);
		
		for (int i = 1; i <= n; ++i) {
			head[i] = 0;
		}
		ed = 0; *dfn = 0;
		
		for (int i = 2; i <= n; ++i) {
			static int fa;
			
			scan(fa);
			AddEdge(fa, i);
		}
		for (int i = 1; i <= n; ++i)
			scan(a[i]);
		
		DFS(1);
		SegTree::build(1, 1, n);
		
		int q; scan(q);
		while (q--) {
			char opt[2]; int x, y;
			
			scanf("%s", opt);
			
			if (*opt == 'Q') {
				scan(x);
				
				int Max = -INF, Min = INF;
				SegTree::query(1, 1, n, dfn[x], dfn[x] + sz[x] - 1, Max, Min);
				printf("%d\n", Max - Min);
			}
			else {
				scan(x); scan(y);
				
				SegTree::add(1, 1, n, dfn[x], dfn[x] + sz[x] - 1, y);
			}
		}
	}
	
	return 0;
}
/*
register char *_sp __asm__("rsp");

int main() {
	const int size = 16 << 20;
	static char *sys, *mine(new char[size] + size - 4096);
	sys = _sp; _sp = mine; __main__(); _sp = sys;
	
	return 0;
}*/
