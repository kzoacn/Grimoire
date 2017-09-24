#include <bits/stdc++.h>

const double eps = 1e-7;

int n, a[60005], pre[60005], last[60005];

namespace SegTree {
	double mn[60005 << 2], tag[60005 << 2];
	
	void init() {
		for (int i = 1; i <= (n << 2); ++i) mn[i] = 1e20, tag[i] = 0;
	}

	void down(int k) {
		if (tag[k]) {
			mn[k << 1] += tag[k];
			mn[k << 1 | 1] += tag[k];
			tag[k << 1] += tag[k];
			tag[k << 1 | 1] += tag[k];
			tag[k] = 0;
		}
	}
	
	void modify(int k, int l, int r, int pos, double val) {
		if (l == r) {
			mn[k] = val; return;
		}
		down(k);
		int mid = (l + r) >> 1;
		if (pos <= mid) modify(k << 1, l, mid, pos, val);
		else modify(k << 1 | 1, mid + 1, r, pos, val);
		mn[k] = std::min(mn[k << 1], mn[k << 1 | 1]);
	}
	
	void add(int k, int l, int r, int L, int R, double val) {
		if (L <= l && r <= R) {
			mn[k] += val;
			tag[k] += val;
			return;
		}
		down(k);
		int mid = (l + r) >> 1;
		if (L <= mid) add(k << 1, l, mid, L, R, val);
		if (mid < R) add(k << 1 | 1, mid + 1, r, L, R, val);
		mn[k] = std::min(mn[k << 1], mn[k << 1 | 1]);
	}
	
	double query(int k, int l, int r, int L, int R) {
		if (L > R) return 1e20;
		if (L <= l && r <= R) return mn[k];
		down(k);
		int mid = (l + r) >> 1;
		double res = 1e20;
		if (L <= mid) res = std::min(res, query(k << 1, l, mid, L, R));
		if (mid < R) res = std::min(res, query(k << 1 | 1, mid + 1, r, L, R));
		return res;
	}
}

bool check(double mid) {
	SegTree::init();
	for (int i = 1; i <= n; ++i) {
		SegTree::modify(1, 1, n, i, i * mid);
		SegTree::add(1, 1, n, pre[i] + 1, i, 1);
		double tmp = SegTree::query(1, 1, n, 1, i - 1);
//		std::cerr << "tmp = " << tmp << std::endl;
		if (tmp < i * mid + mid) return 1;
	}
	return 0;
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		memset(last, 0, sizeof last);
		
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			pre[i] = last[a[i]];
			last[a[i]] = i;
		}
		
		double l = 0, r = 1;
		while (r - l > eps) {
			double mid = (l + r) / 2;
			if (check(mid)) r = mid;
			else l = mid;
		}
		
		printf("%.6f\n", l);
	}
	
	return 0;
}
