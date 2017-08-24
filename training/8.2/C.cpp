#include <bits/stdc++.h>

typedef long long ll;

template <class T>
void scan(T &x) {
	register char ch; x = 0;
	for (ch = getchar(); ~ch && (ch < '0' || ch > '9'); ch = getchar());
	for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
}

int n, m, R, K, P;
ll *a[1000005];

namespace SegTree {
// private
	struct Node *pool_pointer;
	struct Node {
		Node *ch[2];
		int mx;
		
		Node() {
			ch[0] = ch[1] = 0;
			mx = 0;
		}
		
		void *operator new (size_t) {
			return pool_pointer++;
		}
	} pool[1000005 << 3], *root_x[1000005], *root_y[1000005];
	
	void build_x(Node *&k, int l, int r, int x) {
		k = new Node();
		if (l == r) {
			k->mx = a[x][l];
			return;
		}
		int mid = (l + r) >> 1;
		build_x(k->ch[0], l, mid, x);
		build_x(k->ch[1], mid + 1, r, x);
		k->mx = std::max(k->ch[0]->mx, k->ch[1]->mx);
	}
	
	void build_y(Node *&k, int l, int r, int y) {
		k = new Node();
		if (l == r) {
			k->mx = a[l][y];
			return;
		}
		int mid = (l + r) >> 1;
		build_y(k->ch[0], l, mid, y);
		build_y(k->ch[1], mid + 1, r, y);
		k->mx = std::max(k->ch[0]->mx, k->ch[1]->mx);
	}
	
	void add(Node *k, int l, int r, int pos, int val) {
		if (l == r) {
			k->mx += val;
			return;
		}
		int mid = (l + r) >> 1;
		if (pos <= mid) add(k->ch[0], l, mid, pos, val);
		else add(k->ch[1], mid + 1, r, pos, val);
		k->mx = std::max(k->ch[0]->mx, k->ch[1]->mx);
	}
	
	int pre(Node *k, int l, int r, int L, int R, int val) {
		if (k->mx < val) return -1;
		if (l == r) return l;
		int mid = (l + r) >> 1;
		if (R <= mid) return pre(k->ch[0], l, mid, L, R, val);
		else if (mid < L) return pre(k->ch[1], mid + 1, r, L, R, val);
		else {
			int tmp = pre(k->ch[0], l, mid, L, R, val);
			if (tmp != -1) return tmp;
			return pre(k->ch[1], mid + 1, r, L, R, val);
		}
	}
	
	int suf(Node *k, int l, int r, int L, int R, int val) {
		if (k->mx < val) return -1;
		if (l == r) return l;
		int mid = (l + r) >> 1;
		if (R <= mid) return suf(k->ch[0], l, mid, L, R, val);
		else if (mid < L) return suf(k->ch[1], mid + 1, r, L, R, val);
		else {
			int tmp = suf(k->ch[1], mid + 1, r, L, R, val);
			if (tmp != -1) return tmp;
			return suf(k->ch[0], l, mid, L, R, val);
		}
	}
	
	void output(Node *k, int l, int r, int x) {
		if (l == r) {
			a[x][l] = k->mx; return;
		}
		int mid = (l + r) >> 1;
		output(k->ch[0], l, mid, x);
		output(k->ch[1], mid + 1, r, x);
	}
	
// public
	void init() {
		pool_pointer = pool;
		for (int i = 1; i <= n; ++i)
			build_x(root_x[i], 1, m, i);
		for (int i = 1; i <= m; ++i)
			build_y(root_y[i], 1, n, i);
	}
	
	void add(int x, int y, int val) { // tree_type - 0: tree_x, 1: tree_y
		add(root_x[x], 1, m, y, val);
		add(root_y[y], 1, n, x, val);
	}
	
	int pre(int tree_type, int t, int L, int R, int val) { // tree_type - 0: tree_x, 1: tree_y
		if (L > R) return -1;
		if (tree_type == 0)
			return pre(root_x[t], 1, m, L, R, val);
		return pre(root_y[t], 1, n, L, R, val);
	}
	
	int suf(int tree_type, int t, int L, int R, int val) { // tree_type - 0: tree_x, 1: tree_y
		if (L > R) return -1;
		if (tree_type == 0)
			return suf(root_x[t], 1, m, L, R, val);
		return suf(root_y[t], 1, n, L, R, val);
	}
	
	void output() {
		for (int i = 1; i <= n; ++i)
			output(root_x[i], 1, m, i);
	}
}

int main() {
	freopen("C.in", "r", stdin);
	
	scan(n); scan(m); scan(R); scan(K); scan(P);
	a[0] = new ll[m + 5];
	for (int i = 1; i <= n; ++i) {
		a[i] = new ll[m + 5];
		for (int j = 1; j <= m; ++j)
			scan(a[i][j]);
	}
	
	for (int i = 0; i <= n; ++i)
		a[i][0] = 0;
	for (int j = 0; j <= m; ++j)
		a[0][j] = 0;
	
	SegTree::init();
	
	char opt[2]; int x, h, tmp;
	while (K--) {
		scanf("%s", opt); scan(x); scan(h);
		if (h <= 0) continue;
		switch (*opt) {
			case 'W':
				tmp = 0;
				for (int i = 1; i <= R; ++i) {
					tmp = SegTree::pre(0, x, tmp + 1, m, h);
					if (tmp == -1) break;
					SegTree::add(x, tmp, -1);
				}
				break;
			case 'N':
				tmp = 0;
				for (int i = 1; i <= R; ++i) {
					tmp = SegTree::pre(1, x, tmp + 1, n, h);
					if (tmp == -1) break;
					SegTree::add(tmp, x, -1);
				}
				break;
			case 'S':
				tmp = n + 1;
				for (int i = 1; i <= R; ++i) {
					tmp = SegTree::suf(1, x, 1, tmp - 1, h);
					if (tmp == -1) break;
					SegTree::add(tmp, x, -1);
				}
				break;
			case 'E':
				tmp = m + 1;
				for (int i = 1; i <= R; ++i) {
					tmp = SegTree::suf(0, x, 1, tmp - 1, h);
					if (tmp == -1) break;
					SegTree::add(x, tmp, -1);
				}
				break;
		}
	}
	
	SegTree::output();
/*	
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			printf("%lld%c", a[i][j], " \n"[j == m]);
*/	
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			a[i][j] = a[i][j] + a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
	
	ll ans = 0;
	for (int i = P; i <= n; ++i)
		for (int j = P; j <= m; ++j)
			ans = std::max(ans, a[i][j] - a[i - P][j] - a[i][j - P] + a[i - P][j - P]);
	
	std::cout << ans << std::endl;
	
	return 0;
}
