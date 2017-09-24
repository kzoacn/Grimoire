#include <bits/stdc++.h>

const int drct[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

char s[10][10];

bool vis[10][10];

bool DFS(int x, int y) {
	if (x < 0 || x >= 9 || y < 0 || y >= 9 || vis[x][y] || s[x][y] == 'x') return 0;
	if (s[x][y] == '.') return 1;
	vis[x][y] = 1;
	
	bool res = 0;
	
	for (int t = 0; t < 4; ++t) {
		int xx = x + drct[t][0], yy = y + drct[t][1];
		
		res |= DFS(xx, yy);
	}
	return res;
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		for (int i = 0; i < 9; ++i) scanf("%s", s[i]);
		
		bool flag = 0;
		
		for (int i = 0; i < 9; ++i)
			for (int j = 0; j < 9; ++j) if (s[i][j] == '.') {
				memset(vis, 0, sizeof vis);
				s[i][j] = 'x';
				for (int x = 0; x < 9; ++x)
					for (int y = 0; y < 9; ++y) if (s[x][y] == 'o' && !vis[x][y]) {
						if (!DFS(x, y)) {
							flag = 1; break;
						}
					}
				s[i][j] = '.';
			}
		
		printf("Case #%d: ", kase);
		if (flag) puts("Can kill in one move!!!");
		else puts("Can not kill in one move!!!");
	}
	
	return 0;
}
