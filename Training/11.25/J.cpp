#include <bits/stdc++.h>

#define __advance __attribute__((optimize("O3")))

const int MAXN = 300 + 5;

int n, m;
char mp[MAXN][MAXN];

int T = 0, vis[MAXN][MAXN];

int seq[MAXN];
int dp[MAXN][2];
int tot;

using namespace std;

const int INF = 1e8;

__advance __inline int DP() {
	for (register int i = 0; i <= tot + 1; ++i) {
		dp[i][0] = dp[i][1] = INF;
	}
	dp[1][seq[1]] = seq[1];
	for (register int i = 2; i <= tot; ++i) {
		if (seq[i] == 0) {
			dp[i][0] = dp[i - 1][0];
		} else {
			dp[i][0] = dp[i - 1][1];
			dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + 1;
		}
	}
	return dp[tot][0];
}

__advance int main() {
	int caseCnt; scanf("%d", &caseCnt);
	while (caseCnt--) {
		int ans = 0;
		
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) {
			scanf("%s", mp[i] + 1);
			for (int j = 1; j <= m; ++j)
				ans += (mp[i][j] == '#');
		}
		
		for (register int i = 0; i < n; ++i)
			for (register int j = 0; j < m; ++j) {
				if (!i && !j) continue;
				
				static int tmp;
				
				++T; tmp = 0;
				for (register int x = 1; x <= n; ++x)
					for (register int y = 1; y <= m; ++y) {
						if (vis[x][y] == T) continue;
						
						int xx = x, yy = y;
						tot = 0;
						while (xx >= 1 && xx <= n && yy >= 1 && yy <= m) {
							seq[++tot] = (mp[xx][yy] == '#');
							vis[xx][yy] = T;
							xx += i; yy += j;
						}
						
						tmp += DP();
						if (tmp >= ans)
							goto OUT1;
					}
				ans = std::min(ans, tmp);
				
				OUT1:;
				
				++T; tmp = 0;
				for (register int x = 1; x <= n; ++x)
					for (register int y = m; y; --y) {
						if (vis[x][y] == T) continue;
						
						int xx = x, yy = y;
						tot = 0;
						while (xx >= 1 && xx <= n && yy >= 1 && yy <= m) {
							seq[++tot] = (mp[xx][yy] == '#');
							vis[xx][yy] = T;
							xx += i; yy -= j;
						}
						
						tmp += DP();
						if (tmp >= ans)
							goto OUT2;
					}
				ans = std::min(ans, tmp);
				
				OUT2:;
			}
		
		printf("%d\n", ans);
	}
	
	return 0;
}
