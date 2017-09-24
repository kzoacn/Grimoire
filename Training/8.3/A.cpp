#include <bits/stdc++.h>

typedef long long ll;

const int drct[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

struct Num {
	int val, x, y;
	
	Num() {}
	Num(int val, int x, int y): val(val), x(x), y(y) {}
	
	bool operator < (const Num &rhs) const {
		return val < rhs.val;
	}
} num[55 * 55]; int tot;

int n, m, a[55][55];
ll dp[55][55];

ll ans;

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d%d", &n, &m);
		tot = 0;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j) {
				scanf("%d", a[i] + j);
				num[++tot] = Num(a[i][j], i, j);
			}
		ans = 0;
		std::sort(num + 1, num + tot + 1);
		for (int i = 1; i <= tot; ++i) {
			int x = num[i].x, y = num[i].y;
			
			dp[x][y] = 0;
			for (int t = 0; t < 4; ++t) {
				int xx = x + drct[t][0], yy = y + drct[t][1];
				if (xx < 1 || xx > n || yy < 1 || yy > m || a[xx][yy] >= a[x][y]) continue;
				
				dp[x][y] += dp[xx][yy];
			}
			if (dp[x][y] == 0) dp[x][y] = 1;
			
			bool flag = 0;
			for (int t = 0; t < 4; ++t) {
				int xx = x + drct[t][0], yy = y + drct[t][1];
				if (xx < 1 || xx > n || yy < 1 || yy > m) continue;
				if (a[xx][yy] > a[x][y]) {
					flag = 1; break;
				}
			}
			if (!flag) ans += dp[x][y];
		}
		
		printf("Case #%d: %lld\n", kase, ans);
	}
	
	return 0;
}
