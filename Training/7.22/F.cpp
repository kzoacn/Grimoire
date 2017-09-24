#include <bits/stdc++.h>

const int drct[4][2] = {{0, 1}, {-1, 0}, {1, 0}, {0, -1}};
const char DRCT[5] = "ENSW";

struct Block {
	int len, dr; // DRCT
	
	Block() {
		len = dr = -1;
	}
	Block(int len, int dr): len(len), dr(dr) {}
	
	void scan() {
		static char ch;
		scanf("%d%c", &len, &ch);
		for (dr = 0; dr < 4; ++dr) if (DRCT[dr] == ch) break;
	}
	
	bool operator < (const Block &rhs) const {
		return len == rhs.len ? dr < rhs.dr : len < rhs.len;
	}
} blk[105][105];

struct Ans {
	int x, y;
	Block to;
	int dis;
	
	Ans() {
		x = y = dis = -1; to = Block();
	}
	Ans(int x, int y, const Block &to, int dis): x(x), y(y), to(to), dis(dis) {}
	
	bool operator < (const Ans &rhs) const {
		if (dis != rhs.dis) {
			if (dis == -1) return 0;
			if (rhs.dis == -1) return 1;
			return dis < rhs.dis;
		}
		if (x != rhs.x) return x < rhs.x;
		if (y != rhs.y) return y < rhs.y;
		return to < rhs.to;
	}
};

int dist[105][105];
bool vis[105][105];

int n, m;

int DFS(int x, int y) {
	if (x < 1 || x > n || y < 1 || y > m) return -1;
	if (vis[x][y]) return dist[x][y];
	vis[x][y] = 1;
	if (x == n && y == m) return dist[x][y] = 0;
	dist[x][y] = -1;
	
	if (DFS(x + drct[blk[x][y].dr][0] * blk[x][y].len, y + drct[blk[x][y].dr][1] * blk[x][y].len) == -1)
		return dist[x][y] = -1;
	return dist[x][y] = DFS(x + drct[blk[x][y].dr][0] * blk[x][y].len, y + drct[blk[x][y].dr][1] * blk[x][y].len) + 1;
}

Ans DFS2(int x, int y) {
	if (x < 1 || x > n || y < 1 || y > m) return Ans();
	if ((x == n && y == m) || vis[x][y]) return Ans();
	
	vis[x][y] = 1;
	Ans res = DFS2(x + drct[blk[x][y].dr][0] * blk[x][y].len, y + drct[blk[x][y].dr][1] * blk[x][y].len);
	if (res.dis != -1) ++res.dis;
	for (int t = 0; t < 4; ++t) {
		for (int i = 1; ; ++i) {
			int xx = x + drct[t][0] * i, yy = y + drct[t][1] * i;
			if (xx < 1 || xx > n || yy < 1 || yy > m) break;
//			if (t == blk[x][y].dr && i == blk[x][y].len) continue;
			if (dist[xx][yy] == -1) continue;
			res = std::min(res, Ans(x, y, Block(i, t), dist[xx][yy] + 1));
		}
	}
	return res;
}

int main() {
	int kase = 0;
	while (~scanf("%d%d", &n, &m) && n && m) {
		++kase;
		
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j) {
				if (i == n && j == m) {
					blk[i][j] = Block();
					break;
				}
				blk[i][j].scan();
			}
		
		memset(vis, 0, sizeof vis);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				DFS(i, j);
		
//		printf("dist[1][1] = %d\n", dist[1][1]);
		
		memset(vis, 0, sizeof vis);
		Ans tmp = DFS2(1, 1);
		
		printf("Case %d: ", kase);
//		printf("tmp.dis = %d\n", tmp.dis);
		if (tmp.dis == -1/* && dist[1][1] == -1*/) puts("impossible");
		else if (/*tmp.dis == -1 || */(dist[1][1] != -1 && tmp.dis >= dist[1][1])) printf("none %d\n", dist[1][1]);
		else printf("%d %d %d%c %d\n", tmp.x - 1, tmp.y - 1, tmp.to.len, DRCT[tmp.to.dr], tmp.dis);
	}
	
	return 0;
}
