#include <bits/stdc++.h>

const int drct[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int n, m, num[105][105];
char tr[105][105];
bool vis[105][105];

void print(int x, int ld) {
	int bit = 0, tmp = x;
	while (tmp) {
		tmp /= 10; ++bit;
	}
	for (int i = 1; i <= ld - bit; ++i) putchar('.');
	if (x) printf("%d", x);
}

int main() {
	memset(num, -1, sizeof num);
	
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", tr[i] + 1);
		for (int j = 1; j <= m; ++j)
			if (tr[i][j] == '.') vis[i][j] = 1;
	}
	
	for (int i = 0; i <= n + 1; ++i) vis[i][0] = vis[i][m + 1] = 1;
	for (int j = 0; j <= m + 1; ++j) vis[0][j] = vis[n + 1][j] = 1;
	
	int cnt = 0, ans;
	for (ans = 0; ; ++ans) {
		for (int i = 0; i <= n + 1; ++i)
			for (int j = 0; j <= m + 1; ++j) if (vis[i][j] && num[i][j] == -1) {
				num[i][j] = ans;
				if (i >= 1 && i <= n && j >= 1 && j <= m) ++cnt;
			}
		for (int i = 0; i <= n + 1; ++i)
			for (int j = 0; j <= m + 1; ++j) if (num[i][j] == ans) {
				for (int x, y, t = 0; t < 4; ++t) {
					x = i + drct[t][0], y = j + drct[t][1];
					if (x < 1 || x > n || y < 1 || y > m) continue;
					vis[x][y] = 1;
				}
			}
		
		if (cnt == n * m) break;
	}
	
	if (ans < 10) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j)
				print(num[i][j], 2);
			putchar('\n');
		}
	}
	else {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j)
				print(num[i][j], 3);
			putchar('\n');
		}
	}
	
	return 0;
}
