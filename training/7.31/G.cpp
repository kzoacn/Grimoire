#include <bits/stdc++.h>

const int drct[4][3] = {{2, 1, 0}, {-2, 1, 0}, {2, -1, 0}, {-2, -1, 0}};

int a, b, c;

int stk[2050][30]; int top = 0;

int deg[60][60][60];

bool vis[60][60][60];

std::pair<int, int> permu[3];
int inv[3];

struct vec {
	int x, y, z;
	
	vec() {}
	vec(int x, int y, int z): x(x), y(y), z(z) {}
	
	bool operator < (const vec &rhs) const {
		return deg[x][y][z] < deg[rhs.x][rhs.y][rhs.z];
	}
}; std::vector<vec> to[60][60][60];

void DFS(int x, int y, int z) {
	static int cnt;
	
	if (clock() > 0.95 * CLOCKS_PER_SEC) {
		puts("TLE");
		exit(0);
	}
	/*if (top <= 100) {
		std::cout << top << std::endl;
	}*/
	++top;
	stk[top][0] = x;
	stk[top][1] = y;
	stk[top][2] = z;
	vis[x][y][z] = 1;
	
	if (top == a * b * c) {
		puts("YES");
		for (int i = 1; i <= top; ++i)
			printf("%d %d %d\n", stk[i][inv[0]], stk[i][inv[1]], stk[i][inv[2]]);
		exit(0);
	}
	
	to[x][y][z].clear();
	cnt = 0;
	for (int i = 0; i < 3; ++i)
	for (int j = 0; j < 3; ++j) if (i != j)
		for (int t = 0; t < 4; ++t) {
			int xx = x + drct[t][i], yy = y + drct[t][j], zz = z + drct[t][3 - i - j];
			if (xx < 1 || xx > a || yy < 1 || yy > b || zz < 1 || zz > c || vis[xx][yy][zz]) continue;
			--deg[xx][yy][zz];
			if (!deg[xx][yy][zz]) ++cnt;
			to[x][y][z].push_back(vec(xx, yy, zz));
		}
	if (cnt == 0 || (cnt == 1 && top == a * b * c - 1)) {
		std::sort(to[x][y][z].begin(), to[x][y][z].end());
		for (std::vector<vec>::iterator it = to[x][y][z].begin(); it != to[x][y][z].end(); ++it)
			DFS(it->x, it->y, it->z);
	}
	
	for (int i = 0; i < 3; ++i)
	for (int j = 0; j < 3; ++j) if (i != j)
		for (int t = 0; t < 4; ++t) {
			int xx = x + drct[t][i], yy = y + drct[t][j], zz = z + drct[t][3 - i - j];
			if (xx < 1 || xx > a || yy < 1 || yy > b || zz < 1 || zz > c || vis[xx][yy][zz]) continue;
			++deg[xx][yy][zz];
		}
	
	vis[x][y][z] = 0;
	--top;
}

int main() {
	scanf("%d%d%d", &a, &b, &c);
	
	if (a == 3 && b == 3 && c == 3) {
		puts("NO"); return 0;
	}
	/*if (a == 5 && b == 5 && c == 5) {
		puts("NO"); return 0;
	}*/
	
	permu[0] = std::make_pair(a, 0);
	permu[1] = std::make_pair(b, 1);
	permu[2] = std::make_pair(c, 2);
	
	std::sort(permu, permu + 3);
	a = permu[0].first;
	b = permu[1].first;
	c = permu[2].first;
	for (int i = 0; i < 3; ++i)
		inv[permu[i].second] = i;
	
	for (int x = 1; x <= a; ++x)
	for (int y = 1; y <= b; ++y)
	for (int z = 1; z <= c; ++z)
		for (int t = 0; t < 4; ++t)
			for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j) if (i != j) {
				int xx = x + drct[t][i], yy = y + drct[t][j], zz = z + drct[t][3 - i - j];
				if (xx < 1 || xx > a || yy < 1 || yy > b || zz < 1 || zz > c) continue;
				++deg[x][y][z];
			}

	
	DFS(1, 1, 1);
	
	puts("NO");
	return 0;
}
