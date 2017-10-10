#include <stdio.h>
#include <string.h>
#include <algorithm>

int mpd[200005];

void pretreatment() {
	const int lim = 2e5;
	
	for (int i = 1; i <= lim; ++i) mpd[i] = i;
	
	for (int i = 2; i <= lim; ++i) {
		if (mpd[i] != i) continue;
		for (int j = i + i; j <= lim; j += i)
			mpd[j] = std::min(mpd[j], i);
	}
}

namespace SegTree {
	int tag[200005 << 2];
	
	void init() {
		memset(tag, 0, sizeof tag);
	}
	
	void modify(int k, int l, int r, int L, int R, int val) {
		if (L <= l && r <= R) {
			tag[k] += val;
			return;
		}
		int mid = (l + r) >> 1;
		if (L <= mid) modify(k << 1, l, mid, L, R, val);
		if (mid < R) modify(k << 1 | 1, mid + 1, r, L, R, val);
	}
	
	int query(int k, int l, int r, int pos) {
		if (l == r) return tag[k];
		int mid = (l + r) >> 1;
		if (pos <= mid) return query(k << 1, l, mid, pos) + tag[k];
		else return query(k << 1 | 1, mid + 1, r, pos) + tag[k];
	}
}

int n, m, w[200005];

int *divi[200005];

int ans[200005];

struct Event {
	int pos, L, R, val;
	
	Event() {}
	Event(int pos, int L, int R, int val): pos(pos), L(L), R(R), val(val) {}
	
	bool operator < (const Event &rhs) const {
		return pos == rhs.pos ? val < rhs.val : pos < rhs.pos;
	}
} event[600005]; int event_tot;

int main() {
	pretreatment();
	
	while (~scanf("%d%d", &n, &m) && (n || m)) {
		for (int i = 1; i <= 200000; ++i) {
			if (divi[i]) {
				delete[] divi[i];
				divi[i] = 0;
			}
			divi[i] = new int[1];
			*divi[i] = 0;
		}
		
		for (int i = 1; i <= n; ++i) {
			scanf("%d", w + i);
			for (int t = w[i], d = mpd[t]; t > 1; d = mpd[t]) {
				++*divi[d];
				while (t % d == 0) t /= d;
			}
		}
		
		for (int i = 1; i <= 200000; ++i) {
			int cnt = divi[i][0];
			delete[] divi[i];
			divi[i] = 0;
			if (cnt == 0) continue;
			divi[i] = new int[cnt + 1];
			*divi[i] = 0;
		}
		
		for (int i = 1; i <= n; ++i) {
			for (int t = w[i], d = mpd[t]; t > 1; d = mpd[t]) {
				divi[d][++*divi[d]] = i;
				while (t % d == 0) t /= d;
			}
		}
		
		for (int d = 1; d <= 200000; ++d) if (divi[d]) {
			std::sort(divi[d] + 1, divi[d] + *divi[d] + 1);
		}
		
		event_tot = 0;
		for (int i = 1; i <= n; ++i) {
			int L = 1, R = n;
			for (int t = w[i], d = mpd[t]; t > 1; d = mpd[t]) {
				int it = std::lower_bound(divi[d] + 1, divi[d] + *divi[d] + 1, i) - divi[d];
				
				if (it != 1) {
					--it;
					L = std::max(L, divi[d][it] + 1);
					++it;
				}
				if (it != *divi[d]) {
					++it;
					R = std::min(R, divi[d][it] - 1);
					--it;
				}
				while (t % d == 0) t /= d;
			}
			event[++event_tot] = Event(i, L, i, -1);
			event[++event_tot] = Event(R + 1, L, i, -3);
		}
		
		for (int L, R, i = 1; i <= m; ++i) {
			scanf("%d%d", &L, &R);
			event[++event_tot] = Event(R, L, L, i);
		}
		
		std::sort(event + 1, event + event_tot + 1);
		
		SegTree::init();
		
		for (int i = 1; i <= event_tot; ++i) {
			if (event[i].val < 0)
				SegTree::modify(1, 1, n, event[i].L, event[i].R, event[i].val + 2);
			else
				ans[event[i].val] = SegTree::query(1, 1, n, event[i].L);
		}
		
		for (int i = 1; i <= m; ++i)
			printf("%d\n", ans[i]);
	}
	
	return 0;
}
