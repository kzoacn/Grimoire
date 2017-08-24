#include <bits/stdc++.h>

int n, W, H;
int sorted[100005], cntx[100005], valx[100005];
int wpre[100005], wsuf[100005];

namespace SegTree {
	int mx[100005 << 2], tag[100005 << 2];
	
	void build(int k, int l, int r) {
		tag[k] = 0;
		if (l == r) {
			mx[k] = valx[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(k << 1, l, mid);
		build(k << 1 | 1, mid + 1, r);
		mx[k] = std::max(mx[k << 1], mx[k << 1 | 1]);
	}
	
	void init() {
		build(1, 1, *sorted);
	}
	
	void modify(int k, int l, int r, int L, int R, int val) {
		if (L <= l && r <= R) {
			tag[k] += val;
			if (!tag[k]) {
				if (l == r) mx[k] = valx[l];
				else mx[k] = std::max(mx[k << 1], mx[k << 1 | 1]);
			}
			else mx[k] = 0;
			return;
		}
		int mid = (l + r) >> 1;
		if (L <= mid) modify(k << 1, l, mid, L, R, val);
		if (mid < R) modify(k << 1 | 1, mid + 1, r, L, R, val);
		mx[k] = (tag[k] ? 0 : std::max(mx[k << 1], mx[k << 1 | 1]));
	}
	
	int query() {
		return mx[1];
	}
}

struct Event {
	int x, y, tp;
	
	bool operator < (const Event &rhs) const {
		return y < rhs.y;
	}
	
	void scan() {
		scanf("%d%d", &x, &y); tp = 1;
	}
} pawn[200005];

int hsh(int x) {
	return std::lower_bound(sorted + 1, sorted + *sorted + 1, x) - sorted;
}

void two_pointer() {
	for (int l = 1, r = 1; r <= *sorted; ++r) {
		while (sorted[r] - sorted[l] >= W) ++l;
		wpre[r] = l;
	}
	for (int l = *sorted, r = *sorted; l; --l) {
		while (sorted[r] - sorted[l] >= W) --r;
		wsuf[l] = r;
	}
	int tmp = 0;
	for (int l = 1; l <= *sorted; ++l) {
		for (int r = wsuf[l - 1] + 1; r <= wsuf[l]; ++r)
			tmp += cntx[r];
		valx[l] = tmp;
		tmp -= cntx[l];
	}
}

int calc() {
	SegTree::init();
	
	int res = SegTree::query(), tmp = 0;
	
	for (int i = 1; i <= n * 2; ) {
		do {
			SegTree::modify(1, 1, *sorted, wpre[pawn[i].x], pawn[i].x, pawn[i].tp);
			tmp += pawn[i].tp;
			++i;
		} while (i <= n * 2 && pawn[i].y == pawn[i - 1].y);
		
		res = std::max(res, tmp + SegTree::query());
		
//		fprintf(stderr, "res = %d, (%d, %d), tp = %d\n", res, pawn[i].x, pawn[i].y, pawn[i].tp);
	}
	return res;
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		memset(cntx, 0, sizeof cntx);
		memset(valx, 0, sizeof valx);
		memset(wpre, 0, sizeof wpre);
		memset(wsuf, 0, sizeof wsuf);
		
		// init
		
		scanf("%d%d%d", &n, &W, &H);
		for (int i = 1; i <= n; ++i) {
			pawn[i].scan();
			pawn[i + n] = pawn[i]; pawn[i + n].y += H; pawn[i + n].tp = -1;
			sorted[i] = pawn[i].x;
		}
		
		std::sort(sorted + 1, sorted + n + 1);
		*sorted = std::unique(sorted + 1, sorted + n + 1) - sorted - 1;
		std::sort(pawn + 1, pawn + n * 2 + 1);
		
		for (int i = 1; i <= n * 2; ++i) {
			pawn[i].x = hsh(pawn[i].x);
			if (pawn[i].tp == 1) ++cntx[pawn[i].x];
		}
		two_pointer();
		
		printf("Case #%d: %d\n", kase, calc());
	}
	
	return 0;
}
