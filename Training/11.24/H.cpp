#include <bits/stdc++.h>

namespace Scanner {
	const int L = (1 << 15) + 5;
	char buffer[L], *S, *T;
	
	__inline char getc() {
		if (S == T) {
			T = (S = buffer) + fread(buffer, 1, L, stdin);
			if (S == T)
				return -1;
		}
		return *S++;
	}
	
	template <class Type>
	__inline void scan(Type &x) {
		register char ch; x = 0;
		for (ch = getc(); ~ch && (ch < '0' || ch > '9'); ch = getc());
		for (; ch >= '0' && ch <= '9'; ch = getc()) x = x * 10 + ch - '0';
	}
} using Scanner::scan;

typedef long long LL;

const int MAXN = 1e6 + 5;

int n, m, a[MAXN];

namespace SegTree {
	int mx[MAXN << 2], sec[MAXN << 2], mxCnt[MAXN << 2], tag[MAXN << 2];
	LL sum[MAXN << 2];
	
	void update(int k) {
		sum[k] = sum[k << 1] + sum[k << 1 | 1];
		if (mx[k << 1] == mx[k << 1 | 1]) {
			mx[k] = mx[k << 1];
			mxCnt[k] = mxCnt[k << 1] + mxCnt[k << 1 | 1];
			sec[k] = std::max(sec[k << 1], sec[k << 1 | 1]);
		}
		else if (mx[k << 1] > mx[k << 1 | 1]) {
			mx[k] = mx[k << 1];
			mxCnt[k] = mxCnt[k << 1];
			sec[k] = std::max(sec[k << 1], mx[k << 1 | 1]);
		}
		else {
			mx[k] = mx[k << 1 | 1];
			mxCnt[k] = mxCnt[k << 1 | 1];
			sec[k] = std::max(mx[k << 1], sec[k << 1 | 1]);
		}
	}
	
	void build(int k, int l, int r) {
		tag[k] = -1;
		if (l == r) {
			mx[k] = a[l];
			sec[k] = -1;
			mxCnt[k] = 1;
			sum[k] = a[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(k << 1, l, mid);
		build(k << 1 | 1, mid + 1, r);
		update(k);
	}
	
	void modi(int k, int l, int r, int val) {
		if (val >= mx[k]) return;
		if (val > sec[k]) {
			tag[k] = val;
			sum[k] -= 1LL * (mx[k] - val) * mxCnt[k];
			mx[k] = val;
			return;
		}
		int mid = (l + r) >> 1;
		modi(k << 1, l, mid, val);
		modi(k << 1 | 1, mid + 1, r, val);
		update(k);
	}
	
	void down(int k, int l, int mid, int r) {
		if (tag[k] == -1) return;
		modi(k << 1, l, mid, tag[k]);
		modi(k << 1 | 1, mid + 1, r, tag[k]);
		tag[k] = -1;
	}
	
	void modify(int k, int l, int r, int L, int R, int val) {
		if (L <= l && r <= R) {
			modi(k, l, r, val);
			return;
		}
		int mid = (l + r) >> 1;
		down(k, l, mid, r);
		if (L <= mid) modify(k << 1, l, mid, L, R, val);
		if (mid < R) modify(k << 1 | 1, mid + 1, r, L, R, val);
		update(k);
	}
	
	int queryMax(int k, int l, int r, int L, int R) {
		if (L <= l && r <= R) return mx[k];
		int mid = (l + r) >> 1, res = 0;
		down(k, l, mid, r);
		if (L <= mid) res = std::max(res, queryMax(k << 1, l, mid, L, R));
		if (mid < R) res = std::max(res, queryMax(k << 1 | 1, mid + 1, r, L, R));
		return res;
	}
	
	LL querySum(int k, int l, int r, int L, int R) {
		if (L <= l && r <= R) return sum[k];
		int mid = (l + r) >> 1; LL res = 0;
		down(k, l, mid, r);
		if (L <= mid) res += querySum(k << 1, l, mid, L, R);
		if (mid < R) res += querySum(k << 1 | 1, mid + 1, r, L, R);
		return res;
	}
}

int main() {
	int caseCnt; scan(caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scan(n); scan(m);
		for (int i = 1; i <= n; ++i)
			scan(a[i]);
		
		SegTree::build(1, 1, n);
		while (m--) {
			static int opt, x, y, t;
			
			scan(opt);
			if (opt == 0) {
				scan(x); scan(y); scan(t);
				SegTree::modify(1, 1, n, x, y, t);
			}
			else if (opt == 1) {
				scan(x); scan(y);
				printf("%d\n", SegTree::queryMax(1, 1, n, x, y));
			}
			else {
				scan(x); scan(y);
				printf("%lld\n", SegTree::querySum(1, 1, n, x, y));
			}
		}
	}
	
	return 0;
}
