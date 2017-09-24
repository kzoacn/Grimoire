#include <bits/stdc++.h>

#define __advance //__attribute__((optimize("O2")))

int n, m, a[105][105];

int sorted[105 * 105];

struct Coor {
	int x, y;
	
	Coor() {}
	Coor(int x, int y): x(x), y(y) {}
	
	bool operator < (const Coor &rhs) const {
		return y == rhs.y ? x < rhs.x : y < rhs.y;
	}
}; std::vector<Coor> coor_x[105 * 105], coor_y[105 * 105];

struct Node *pool_pointer;
struct Node {
	int x, y;
	Node *pre, *nxt;
	
	Node() {}
	Node(int x, int y, Node *pre = 0, Node *nxt = 0): x(x), y(y), pre(pre), nxt(nxt) {}
	
	void *operator new (size_t) {
		return pool_pointer++;
	}
} pool[105], *lnk[105];

int skp[105][105], T = 0;

__advance int calc(int x, int bnd) {
	/*static std::map<int, int> mp;
	static std::map<int, int>::iterator pre, nxt;
	
	int res = 0;
	
	std::map<int, int>().swap(mp);
	mp.insert(std::make_pair(0, bnd));
	mp.insert(std::make_pair(m + 1, bnd));
	for (int i = 0; i < (int)coor[x].size(); ++i) {
		if (coor[x][i].x < bnd) continue;
		if (mp.count(coor[x][i].y)) continue;
		
		pre = nxt = mp.lower_bound(coor[x][i].y);
		--pre;
		
		int tmp = std::max(pre->second, nxt->second);
		if (tmp < coor[x][i].x) {
			res += (nxt->first - pre->first - 1) * (nxt->first - pre->first) / 2 * (coor[x][i].x - tmp);
		}
		
		mp.insert(std::make_pair(coor[x][i].y, coor[x][i].x));
	}
	for (pre = mp.begin(), nxt = ++mp.begin(); nxt != mp.end(); ++pre, ++nxt) {
		int tmp = std::max(pre->second, nxt->second);
		res += (nxt->first - pre->first - 1) * (nxt->first - pre->first) / 2 * (n + 1 - tmp);
	}
	
	return res;*/
	
	memset(lnk, 0, sizeof lnk);
	pool_pointer = pool;
	
	lnk[0] = new Node(bnd, 0);
	lnk[m + 1] = new Node(bnd, m + 1);
	lnk[0]->nxt = lnk[m + 1];
	lnk[m + 1]->pre = lnk[0];
	
	int res = 0;
	Node *last = lnk[0];
	for (int i = 0; i < (int)coor_y[x].size(); ++i) {
		if (coor_y[x][i].x < bnd || coor_y[x][i].y == last->y) {
			skp[coor_y[x][i].x][coor_y[x][i].y] = T; continue;
		}
		
		lnk[coor_y[x][i].y] = new Node(coor_y[x][i].x, coor_y[x][i].y, last, last->nxt);
		last->nxt->pre = lnk[coor_y[x][i].y];
		last->nxt = lnk[coor_y[x][i].y];
		last = lnk[coor_y[x][i].y];
	}
	
	for (Node *pr = lnk[0], *nx = lnk[0]->nxt; ; pr = pr->nxt, nx = nx->nxt) {
		int tmp = std::max(pr->x, nx->x);
		res += (nx->y - pr->y - 1) * (nx->y - pr->y) / 2 * (n + 1 - tmp);
		if (nx == lnk[m + 1]) break;
	}
	for (int i = (int)coor_x[x].size() - 1; i >= 0; --i) {
		if (coor_x[x][i].x < bnd) break;
		if (skp[coor_x[x][i].x][coor_x[x][i].y] == T || !lnk[coor_x[x][i].y]) continue;
		
		Node *&k = lnk[coor_x[x][i].y];
		
		Node *pr = k->pre, *nx = k->nxt;
		int tmp = std::max(pr->x, nx->x);
		res += (nx->y - pr->y - 1) * (nx->y - pr->y) / 2 * (coor_x[x][i].x - tmp);
		
		k->nxt->pre = k->pre;
		k->pre->nxt = k->nxt;
		k = 0;
	}
	
	return res;
}

__advance int solve(int x) {
	int res = 0;
	for (int bnd = 1; bnd <= n; ++bnd) {
		++T;
		res += calc(x, bnd);
	}
	return res;
}

__advance int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d%d", &n, &m);
		*sorted = 0;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j) {
				scanf("%d", a[i] + j); sorted[++*sorted] = a[i][j];
			}
		
		std::sort(sorted + 1, sorted + *sorted + 1);
		*sorted = std::unique(sorted + 1, sorted + *sorted + 1) - sorted - 1;
		
		for (int i = 1; i <= *sorted; ++i) {
			std::vector<Coor>().swap(coor_x[i]);
			std::vector<Coor>().swap(coor_y[i]);
		}
		
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j) {
				coor_x[std::lower_bound(sorted + 1, sorted + *sorted + 1, a[i][j]) - sorted].push_back(Coor(i, j));
				coor_y[std::lower_bound(sorted + 1, sorted + *sorted + 1, a[i][j]) - sorted].push_back(Coor(i, j));
			}
		for (int i = 1; i <= *sorted; ++i)
			std::sort(coor_y[i].begin(), coor_y[i].end());
		
		double ans = 0;
		for (int i = 1; i <= *sorted; ++i) {
//			printf("%d: count = %d\n", sorted[i], solve(sorted[i]));
			ans += 1. - solve(i) / (n * (n + 1.) * m * (m + 1.) / 4.);
		}
		
		printf("%.9f\n", ans);
	}
	
	return 0;
}
