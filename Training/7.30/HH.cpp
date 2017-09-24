#include <bits/stdc++.h>

#define __advance __attribute__((optimize("O3")))

int n, m, a[105][105];

int sorted[105 * 105];

struct Coor {
	int x, y;
	
	Coor() {}
	Coor(int x, int y): x(x), y(y) {}
}; std::vector<Coor> coor[105 * 105];

__advance int calc(int x, int bnd) {
	static std::map<int, int> mp;
	static std::map<int, int>::iterator pre, nxt;
	
	register int res = 0;
	
	mp.clear();
	mp.insert(std::make_pair(0, bnd));
	mp.insert(std::make_pair(m + 1, bnd));
	for (register int i = 0; i < (int)coor[x].size(); ++i) {
		if (coor[x][i].x < bnd) continue;
		
		if (mp.count(coor[x][i].y)) {
			continue;
		}
		
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
	
	return res;
}

__advance int solve(int x) {
	register int res = 0;
	for (register int bnd = 1; bnd <= n; ++bnd)
		res += calc(x, bnd);
	return res;
}

__advance int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (register int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d%d", &n, &m);
		*sorted = 0;
		for (register int i = 1; i <= n; ++i)
			for (register int j = 1; j <= m; ++j) {
				scanf("%d", a[i] + j); sorted[++*sorted] = a[i][j];
			}
		
		std::sort(sorted + 1, sorted + *sorted + 1);
		*sorted = std::unique(sorted + 1, sorted + *sorted + 1) - sorted - 1;
		
		for (int i = 1; i <= *sorted; ++i)
			std::vector<Coor>().swap(coor[i]);
		
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				coor[std::lower_bound(sorted + 1, sorted + *sorted + 1, a[i][j]) - sorted].push_back(Coor(i, j));
		
		double ans = 0;
		for (register int i = 1; i <= *sorted; ++i) {
//			printf("%d: count = %d\n", sorted[i], solve(sorted[i]));
			ans += 1. - solve(i) / (n * (n + 1.) * m * (m + 1.) / 4.);
		}
		
		printf("%.9f\n", ans);
	}
	
	return 0;
}
