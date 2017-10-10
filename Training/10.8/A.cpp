#include <bits/stdc++.h>

typedef std::pair<int, int> pii;
#define mkpair std::make_pair

const int drct[5][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int n, m;

char mp[205][205];

pii vul[15];
int tot;

int vis[205][205], T = 0;

bool check(int S) {
	static bool flag;
	for (int i = 0; i < tot; ++i) if (S & (1 << i)) {
		for (int t = 0; t < 4; ++t) {
			flag = 1;
			++T;
			int x = vul[i].first, y = vul[i].second;
			vis[x][y] = T;
			for (int tt = t; tt < t + 2; ++tt) {
				int xx = x + drct[tt][0], yy = y + drct[tt][1];
				if (xx < 1 || xx > n || yy < 1 || yy > m) continue;
				if (mp[xx][yy] == '#') {
					flag = 0; break;
				}
				vis[xx][yy] = T;
			}
			for (int j = 0; j < tot; ++j) if (i != j && (S & (1 << j))) {
				x = vul[j].first, y = vul[j].second;
				vis[x][y] = T;
				for (int tt = 0; tt < 2; ++tt) {
					int xx = x + drct[tt][0], yy = y + drct[tt][1];
					if (xx < 1 || xx > n || yy < 1 || yy > m) continue;
					if (mp[xx][yy] == '#') {
						flag = 0; break;
					}
					vis[xx][yy] = T;
				}
			}
			for (int j = 0; j < tot; ++j)
				if (vis[vul[j].first][vul[j].second] != T) {
					flag = 0; break;
				}
			if (flag) return 1;
		}
	}
	return 0;
}

int main() {
	while (~scanf("%d%d", &n, &m) && (n || m)) {
		tot = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%s", mp[i] + 1);
			for (int j = 1; j <= m; ++j)
				if (mp[i][j] == '.')
					vul[tot++] = mkpair(i, j);
		}
		
		if (tot == 0) {
			puts("0");
			continue;
		}
		
		int ans = 0x3f3f3f3f;
		for (int S = 1; S < (1 << tot); ++S) {
			if (check(S)) ans = std::min(ans, __builtin_popcount(S));
		}
		
		if (ans == 0x3f3f3f3f) puts("-1");
		else printf("%d\n", ans);
	}
	
	return 0;
}
