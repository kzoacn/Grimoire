#include <bits/stdc++.h>

const int drct[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int R, C, swi;

bool F2[1 << 10][55][55], chg[10][55][55];
char mp[55][55]; // '#', '|', alphabet 

int st_x, st_y, ed_x, ed_y;

int dist[1 << 10][55][55][2];

struct Status {
	int mp_kd, x, y;
	bool fl;
	
	Status() {}
	Status(int a, int b, int c, bool d): mp_kd(a), x(b), y(c), fl(d) {}
};

int BFS() {
	static std::queue<Status> que;
	Status now(0, st_x, st_y, 0);
	memset(dist, -1, sizeof dist);
	que.push(now); dist[0][st_x][st_y][0] = 0;
	
	while (!que.empty()) {
		now = que.front(); que.pop();
		int mp_kd = now.mp_kd, x = now.x, y = now.y, fl = now.fl, disnow = dist[mp_kd][x][y][fl];
		if (x == ed_x && y == ed_y) return disnow;
		for (int t = 0; t < 4; ++t) {
			int xx = x + drct[t][0], yy = y + drct[t][1];
			if (xx < 1 || xx > R || yy < 1 || yy > C || dist[mp_kd][xx][yy][fl] != -1 || mp[xx][yy] == '#')
				continue;
			if (mp[xx][yy] != '|' && F2[mp_kd][xx][yy] != fl) continue;
			
			dist[mp_kd][xx][yy][fl] = disnow + 1;
			que.push(Status(mp_kd, xx, yy, fl));
		}
		if (mp[x][y] == '|') {
			if (dist[mp_kd][x][y][fl ^ 1] != -1) continue;
			dist[mp_kd][x][y][fl ^ 1] = disnow + 1;
			que.push(Status(mp_kd, x, y, fl ^ 1));
		}
		if (mp[x][y] >= 'a' && mp[x][y] <= 'j') {
			int t = mp[x][y] - 'a';
			if (dist[mp_kd ^ (1 << t)][x][y][fl ^ chg[t][x][y]] != -1) continue;
			dist[mp_kd ^ (1 << t)][x][y][fl ^ chg[t][x][y]] = disnow + 1;
			que.push(Status(mp_kd ^ (1 << t), x, y, fl ^ chg[t][x][y]));
		}
	}
	
	return -1;
}

void Build() {
	for (int S = 1; S < (1 << swi); ++S) {
		if (__builtin_popcount(S) <= 1) continue;
		
		memcpy(F2[S], F2[0], sizeof F2[0]);
		
		for (int t = 0; t < swi; ++t) if (S & (1 << t)) {
			for (int i = 1; i <= R; ++i)
				for (int j = 1; j <= C; ++j)
					F2[S][i][j] ^= chg[t][i][j];
		}
	}
}

int main() {
	scanf("%d%d", &C, &R);
	for (int i = 1; i <= R; ++i) {
		scanf("%s", mp[i] + 1);
		for (int j = 1; j <= C; ++j) {
			if (mp[i][j] == '^' || (mp[i][j] >= 'A' && mp[i][j] <= 'J')) {
				F2[0][i][j] = 1;
				if (mp[i][j] >= 'A' && mp[i][j] <= 'J')
					mp[i][j] = mp[i][j] - 'A' + 'a';
			}
			
			if (mp[i][j] == '%')
				st_x = i, st_y = j;
			if (mp[i][j] == '&')
				ed_x = i, ed_y = j;
		}
	}
	
	scanf("%d", &swi);
	for (int t = 0; t < swi; ++t) {
		static char s[55];
		
		int cur = 1 << t;
		memcpy(F2[cur], F2[0], sizeof F2[0]);
		
		for (int i = 1; i <= R; ++i) {
			scanf("%s", s + 1);
			for (int j = 1; j <= C; ++j) {
				if (s[j] == '*') {
					chg[t][i][j] = 1;
					F2[cur][i][j] ^= 1;
				}
			}
		}
	}
	
	Build();
	
	printf("%d\n", BFS());
	
	return 0;
}
