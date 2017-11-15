#include <bits/stdc++.h>

const int MAXN = 1e5 + 5;

int n, m;

int c[MAXN];

int cc[MAXN], cnt[MAXN], tot;

struct Interval {
	int l, r;
	
	Interval() {}
	Interval(int l, int r): l(l), r(r) {}
	
	void scan() {
		scanf("%d%d", &l, &r);
	}
} inter[MAXN], r_sorted[MAXN];

int l_sorted[MAXN];

namespace SegTree {
	int mx[MAXN << 2], tag[MAXN << 2];
	
	void init() {
		memset(mx, 0, sizeof mx);
		memset(tag, 0, sizeof tag);
	}
	
	void down(int k, int l, int mid, int r) {
		if (tag[k] != 0) {
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
	
	int query(int k, int l, int r, int L, int R) {
		if (L <= l && r <= R) return mx[k];
		int mid = (l + r) >> 1, res = 0;
		down(k, l, mid, r);
		if (L <= mid) res = std::max(res, query(k << 1, l, mid, L, R));
		if (mid < R) res = std::max(res, query(k << 1 | 1, mid + 1, r, L, R));
		return res;
	}
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) {
			inter[i].scan();
			l_sorted[i] = (r_sorted[i] = inter[i]).l;
		}
		for (int i = 1; i <= m; ++i) {
			scanf("%d", c + i);
		}
		
		std::sort(c + 1, c + m + 1);
		
		tot = 0;
		for (int i = 1; i <= m; ++i) {
			if (i > 1 && c[i] == c[i - 1])
				++cnt[tot];
			else {
				cc[++tot] = c[i];
				cnt[tot] = 1;
			}
		}
		
		std::sort(l_sorted + 1, l_sorted + n + 1);
		std::sort(r_sorted + 1, r_sorted + n + 1, [](Interval a, Interval b){return a.r < b.r;});
		SegTree::init();
		
		int ans = 0;
		for (int i = 1, j = 1; i <= tot; ++i) {
			while (j <= n && r_sorted[j].r < cc[i]) {
				int x = std::lower_bound(cc + 1, cc + tot + 1, r_sorted[j].l) - cc - 1;
				SegTree::add(1, 0, tot, 0, x, 1);
				++j;
			}
			int dp = SegTree::query(1, 0, tot, 0, i - 1) + cnt[i];
			ans = std::max(ans, (int)(dp + n - (std::upper_bound(l_sorted + 1, l_sorted + n + 1, cc[i]) - l_sorted - 1)));
			SegTree::add(1, 0, tot, i, i, dp);
		}
		
		printf("Case #%d: ", kase);
		if (ans > n) puts("IMPOSSIBLE!");
		else printf("%d\n", ans);
	}
	
	return 0;
}
