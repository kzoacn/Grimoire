#include <bits/stdc++.h>

struct SegTree {
	int mx[500005 << 2], tag[500005 << 2];
	
	SegTree() {
		memset(tag, 0, sizeof tag);
	}
	
	void down(int k, int l, int mid, int r) {
		if (tag[k]) {
			mx[k << 1] += tag[k];
			mx[k << 1 | 1] += tag[k];
			tag[k << 1] += tag[k];
			tag[k << 1 | 1] += tag[k];
			tag[k] = 0;
		}
	}
	
	void add(int k, int l, int r, int L, int R, int val) {
		if (L <= l && r <= R) {
			mx[k] += val;
			tag[k] += val;
			return;
		}
		int mid = (l + r) >> 1;
		down(k, l, mid, r);
		if (L <= mid) add(k << 1, l, mid, L, R, val);
		if (mid < R) add(k << 1 | 1, mid + 1, r, L, R, val);
		mx[k] = std::max(mx[k << 1], mx[k << 1 | 1]);
	}
	
	void modify(int k, int l, int r, int pos, int val) {
		if (l == r) {
			mx[k] = val;
			return;
		}
		int mid = (l + r) >> 1;
		down(k, l, mid, r);
		if (pos <= mid) modify(k << 1, l, mid, pos, val);
		else modify(k << 1 | 1, mid + 1, r, pos, val);
		mx[k] = std::max(mx[k << 1], mx[k << 1 | 1]);
	}
	
	int query(int k, int l, int r, int L, int R) {
		if (L <= l && r <= R) return mx[k];
		int mid = (l + r) >> 1, res = 0;
		down(k, l, mid, r);
		if (L <= mid) res = std::max(res, query(k << 1, l, mid, L, R));
		if (mid < R) res = std::max(res, query(k << 1 | 1, mid + 1, r, L, R));
		return res;
	}
} SegT, T_stk;

int n, m;
int a[500005];

struct Query {
	int l, r, id;
	
	bool operator < (const Query &rhs) const {
		return r < rhs.r;
	}
	
	void scan(int ID) {
		scanf("%d%d", &l, &r);
		id = ID;
	}
} qry[500005];

int ans[500005];

int stk[500005], from[500005], top;

int Find(int x) {
	return std::lower_bound(stk + 1, stk + top + 1, x) - stk;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%d", a + i);
	for (int i = 1; i <= m; ++i)
		qry[i].scan(i);
	
	std::sort(qry + 1, qry + m + 1);
	
	for (int i = 1, R = 1; i <= m; ++i) {
		while (R <= qry[i].r) {
			while (top && a[R] > a[stk[top]]) {
				SegT.modify(1, 1, n, stk[top], T_stk.query(1, 1, n, top, top));
				T_stk.modify(1, 1, n, top, 0);
				--top;
			}
			stk[++top] = R;
			if (a[R] == a[stk[top - 1]]) {
				from[top] = from[top - 1];
				T_stk.add(1, 1, n, from[top], top - 1, R - stk[top - 1]);
			}
			else from[top] = top;
			++R;
		}
		
		ans[qry[i].id] = std::max(SegT.query(1, 1, n, qry[i].l, qry[i].r), 
								  T_stk.query(1, 1, n, Find(qry[i].l), top));
	}
	
	for (int i = 1; i <= m; ++i)
		printf("%d\n", ans[i]);
	
	return 0;
}
