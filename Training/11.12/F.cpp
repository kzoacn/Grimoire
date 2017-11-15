#include <bits/stdc++.h>

const int MAXN = 250 + 5, MAXQ = 2.5e5 + 5;

int n, q, nn, sorted[MAXN * MAXN];

struct Grid {
	int val, x, y;
	
	Grid() {}
	Grid(int val, int x, int y): val(val), x(x), y(y) {}
	
	bool operator < (const Grid &rhs) const {
		return val < rhs.val;
	}
} grids[MAXN * MAXN], tmpGrids[MAXN * MAXN];

struct Query {
	int x, y, a, kth, id;
	
	void scan(int ID) {
		scanf("%d%d%d%d", &x, &y, &a, &kth);
		id = ID;
	}
} qry[MAXQ];

namespace BIT {
	int c[MAXN];
	
#define lowbit(x) ((x) & -(x))
	
	void add(int a, int x) {
		for (int i = a; i <= n; i += lowbit(i))
			c[i] += x;
	}
	
	int query(int a) {
		int res = 0;
		for (int i = a; i > 0; i -= lowbit(i))
			res += c[i];
		return res;
	}
}

int ans[MAXQ], tmp[MAXQ];

struct Event {
	int label, x, l, r, id;
	
	Event() {}
	Event(int label, int x, int l, int r, int id): label(label), x(x), l(l), r(r), id(id) {}
} event[MAXQ << 1]; int etot;

void DAC(int vl, int vr, int ql, int qr) {
	if (ql > qr) return;
	if (vl == vr) {
		for (int i = ql; i <= qr; ++i) {
			ans[qry[i].id] = sorted[vl];
		}
		return;
	}
	
//	std::cerr << sorted[vl] << " " << sorted[vr] << " " << ql << " " << qr << std::endl;
	
	int mid = (vl + vr) >> 1, vm = sorted[mid];
	
	int gl = std::lower_bound(grids + 1, grids + nn + 1, Grid(sorted[vl], 0, 0)) - grids, 
		gr = std::upper_bound(grids + 1, grids + nn + 1, Grid(vm, 0, 0)) - grids; // [gl, gr)
	for (int i = gl; i < gr; ++i)
		tmpGrids[i] = grids[i];
	
	std::sort(tmpGrids + gl, tmpGrids + gr, [](const Grid &a, const Grid &b){return a.x < b.x;});
	
//	fprintf(stderr, "%d: [%d, %d)\n", vm, gl, gr);
	
	etot = 0;
	for (int i = ql; i <= qr; ++i) {
		tmp[qry[i].id] = 0;
		event[++etot] = Event(-1, qry[i].x - 1, qry[i].y, qry[i].y + qry[i].a - 1, qry[i].id);
		event[++etot] = Event(1, qry[i].x + qry[i].a - 1, qry[i].y, qry[i].y + qry[i].a - 1, qry[i].id);
	}
	
	std::sort(event + 1, event + etot + 1, [](const Event &a, const Event &b){return a.x < b.x;});
	
	int j = gl;
	for (int i = 1; i <= etot; ++i) {
		while (j < gr && tmpGrids[j].x <= event[i].x) {
			BIT::add(tmpGrids[j].y, 1);
			++j;
		}
		tmp[event[i].id] += event[i].label * (BIT::query(event[i].r) - BIT::query(event[i].l - 1));
	}
	
	int qm = std::partition(qry + ql, qry + qr + 1, [](const Query &x){return tmp[x.id] >= x.kth;}) - qry;
	
	for (int i = qm; i <= qr; ++i)
		qry[i].kth -= tmp[qry[i].id];
	
	for (int i = gl; i < j; ++i) {
		BIT::add(tmpGrids[i].y, -1);
	}
	
	DAC(vl, mid, ql, qm - 1);
	DAC(mid + 1, vr, qm, qr);
}

int main() {
	scanf("%d", &n); nn = n * n;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			static int x;
			
			scanf("%d", &x);
			sorted[++*sorted] = x;
			grids[*sorted] = Grid(x, i, j);
		}
	
	std::sort(sorted + 1, sorted + nn + 1);
	*sorted = std::unique(sorted + 1, sorted + nn + 1) - sorted - 1;
	
	std::sort(grids + 1, grids + nn + 1);
	
//	for (int i = 1; i <= nn; ++i)
//		fprintf(stderr, "%d%c", grids[i].val, " \n"[i == nn]);
	
	scanf("%d", &q);
	for (int i = 1; i <= q; ++i)
		qry[i].scan(i);
	
	DAC(1, *sorted, 1, q);
	
	for (int i = 1; i <= q; ++i)
		printf("%d\n", ans[i]);
	
	return 0;
}
