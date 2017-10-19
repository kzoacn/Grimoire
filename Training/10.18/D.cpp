#include <bits/stdc++.h>

#define __advance __attribute__((optimize("O3")))

typedef std::pair<int, int> pii;
#define mkpair std::make_pair

int thr[8];

int n, m, k;

int edge[55][55], t[8], ft[8];

std::vector<int> attr[55], tic[55];

int dist[55][7000];
bool inq[55][7000];

const int SIZE = 400005;

__advance __inline int inc(int &x) {
	static int res;
	res = x++;
	if (x == SIZE) x = 0;
	return res;
}

__advance std::string THREE(int x) {
	std::string res;
	for (int i = 0; i < k; ++i) {
		res.push_back(x % 3 + '0');
		x /= 3;
	}
	return res;
}

__advance void BellmanFord(int S_st) {
	static pii que[SIZE];
	static int hd, tl;
	
	hd = tl = 0;
	memset(dist, 0x3f, sizeof dist);
	dist[1][S_st] = 0; que[inc(tl)] = mkpair(1, S_st); inq[1][S_st] = 1;
	
	while (hd != tl) {
		int x = que[hd].first, y = que[hd].second; inc(hd); inq[x][y] = 0;
		
//		if (x == 2) std::cerr << x << " " << THREE(y) << std::endl;
		
		for (int xx = 1; xx <= n; ++xx) if (xx != x && ~edge[x][xx]) {
			int yy = y;
			for (int i: tic[xx]) {
				if (yy / thr[i] % 3 == 0)
					yy += thr[i];
			}
			if (dist[xx][yy] <= dist[x][y] + edge[x][xx]) continue;
			dist[xx][yy] = dist[x][y] + edge[x][xx];
			if (!inq[xx][yy]) {
				que[inc(tl)] = mkpair(xx, yy); inq[xx][yy] = 1;
			}
		}
		for (int i: attr[x]) {
			int xx = x, yy = y + (2 - y / thr[i] % 3) * thr[i], dd;
			
//			if (x == 2) std::cerr << "TO: " << i << " " << xx << " " << THREE(yy) << std::endl;
			
			if (y / thr[i] % 3 == 0) dd = t[i];
			else if (y / thr[i] % 3 == 1) dd = ft[i];
			else continue;
			if (dist[xx][yy] <= dist[x][y] + dd) continue;
			dist[xx][yy] = dist[x][y] + dd;
			if (!inq[xx][yy]) {
				que[inc(tl)] = mkpair(xx, yy); inq[xx][yy] = 1;
			}
		}
	}
}

__advance int main() {
	thr[0] = 1;
	for (int i = 1; i < 8; ++i) thr[i] = thr[i - 1] * 3;
	
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		memset(edge, -1, sizeof edge);
		
		scanf("%d%d%d", &n, &m, &k);
		for (int i = 1; i <= n; ++i) {
			attr[i].clear();
			tic[i].clear();
		}
		for (int i = 1; i <= m; ++i) {
			static int u, v, d;
			
			scanf("%d%d%d", &u, &v, &d);
			if (!~edge[u][v]) edge[u][v] = edge[v][u] = d;
			else edge[u][v] = edge[v][u] = std::min(edge[u][v], d);
		}
		
		for (int i = 0; i < k; ++i) {
			static int p, ni, ff;
			
			scanf("%d%d%d%d", &p, t + i, ft + i, &ni);
			attr[p].push_back(i);
			while (ni--) {
				scanf("%d", &ff);
				tic[ff].push_back(i);
			}
		}
		
		int S_st = 0;
		for (int i: tic[1]) {
			S_st += thr[i];
		}
		
		BellmanFord(S_st);
		
		int full = 0;
		for (int i = 0; i < k; ++i)
			full += thr[i] * 2;
//		for (int i = 1; i <= n; ++i)
//			ans = std::min(ans, dist[i][full]);
		
		printf("Case #%d: %d\n", kase, dist[1][full]);
	}
	
	return 0;
}
