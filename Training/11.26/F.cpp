#include <bits/stdc++.h>

const int MAXN = 100 + 5;

int drct[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int n;
char s[MAXN][MAXN], ans[MAXN][MAXN];
char seq[MAXN * MAXN]; int tot;
bool vis[MAXN][MAXN];

inline bool valid(int x) {
	return x >= 1 && x <= n;
}

int main() {
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; ++i)
			scanf("%s", s[i] + 1);
		
		tot = 0;
		for (int sum = 2; sum <= n * 2; ++sum) {
			if (sum & 1)
				for (int i = 1, j = sum - 1; i < sum; ++i, --j) {
					if (!valid(i) || !valid(j)) continue;
					seq[++tot] = s[i][j];
				}
			else
				for (int i = 1, j = sum - 1; i < sum; ++i, --j) {
					if (!valid(i) || !valid(j)) continue;
					seq[++tot] = s[j][i];
				}
		}
		
/*		printf("seq = ");
		for (int i = 1; i <= tot; ++i)
			putchar(seq[i]);
		putchar('\n');*/
		
		memset(vis, 0, sizeof vis);
		int x = 1, y = 0, t = 0;
		for (int i = 1; i <= tot; ++i) {
			static int xx, yy;
			
			xx = x + drct[t][0], yy = y + drct[t][1];
			while (!valid(xx) || !valid(yy) || vis[xx][yy]) {
				t = (t + 1) % 4;
				xx = x + drct[t][0], yy = y + drct[t][1];
			}
			
			ans[xx][yy] = seq[i];
			vis[xx][yy] = 1;
			x = xx, y = yy;
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j)
				putchar(ans[i][j]);
			putchar('\n');
		}
	}
	
	return 0;
}
