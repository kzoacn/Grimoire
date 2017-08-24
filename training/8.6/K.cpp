#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 4040;
const LL INF = 1e18;
int testcase, n, t[MAXN], p[MAXN];
//LL f[MAXN][MAXN], g[MAXN][MAXN];
LL f[2][MAXN], g[2][MAXN];

int main() {
	cin >> testcase;
	for (int cs = 1; cs <= testcase; ++cs) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", &t[i], &p[i]);
		}
		
		int now = 1;
		f[1][1] = g[1][1] = INF;
		f[1][0] = g[1][0] = INF;
		f[1][n + 1] = g[1][n + 1] = INF;
		for (int i = 2; i <= n; ++i) {
			f[1][i] = 1LL * t[1] * (i - 1);
			g[1][i] = 1LL * p[1] * (i - 1);
		}
		for (int i = 2; i <= n; ++i) {
			now ^= 1;
			for (int j = 0; j <= n + 1; ++j) {
				f[now][j] = g[now][j] = INF;
			}
			for (int j = 1; j <= n; ++j) {
				if (i == j) {
					continue;
				}
				if (j < i - 1) {
					f[now][j] = f[now ^ 1][j] + 1LL * t[i] * (i - j);
					g[now][j] = g[now ^ 1][j] + 1LL * p[i] * (i - j);
				}
				if (j == i - 1) {
					f[now][i - 1] = min(g[now ^ 1][i] + t[i], g[now ^ 1][i - 2] + t[i]);
					g[now][i - 1] = min(f[now ^ 1][i] + p[i], f[now ^ 1][i - 2] + p[i]);
				}
				if (j == i + 1) {
					f[now][i + 1] = min(f[now][i + 1], f[now ^ 1][i + 1] + t[i]);
					f[now][i + 1] = min(f[now][i + 1], f[now ^ 1][i - 2] + t[i]);
					if (i > 2) {
						f[now][i + 1] = min(f[now][i + 1], f[now ^ 1][i - 3] + t[i]);
					}
					f[now][i + 1] = min(f[now][i + 1], g[now ^ 1][i] + t[i]);
					f[now][i + 1] = min(f[now][i + 1], g[now ^ 1][i - 2] + t[i]);
					
					g[now][i + 1] = min(g[now][i + 1], g[now ^ 1][i + 1] + p[i]);
					g[now][i + 1] = min(g[now][i + 1], g[now ^ 1][i - 2] + p[i]);
					if (i > 2) {
						g[now][i + 1] = min(g[now][i + 1], g[now ^ 1][i - 3] + p[i]);
					}
					g[now][i + 1] = min(g[now][i + 1], f[now ^ 1][i] + p[i]);
					g[now][i + 1] = min(g[now][i + 1], f[now ^ 1][i - 2] + p[i]);
				}
				if (j > i + 1) {
					f[now][j] = f[now ^ 1][j] + 1LL * t[i] * (j - i);
					g[now][j] = g[now ^ 1][j] + 1LL * p[i] * (j - i);
					for (int k = 2 * (i - 1) - j; k <= 2 * i - j; ++k) {
						if (k > 0 && k <= n) {
							f[now][j] = min(f[now][j], f[now ^ 1][k] + 1LL * t[i] * (j - i));
							g[now][j] = min(g[now][j], g[now ^ 1][k] + 1LL * p[i] * (j - i));
						}
					}
				}
				f[now][j] = min(f[now][j], INF);
				g[now][j] = min(g[now][j], INF);
			}
		}
		
		LL ans = INF;
		for (int i = 1; i <= n; ++i) {
			ans = min(f[now][i], ans);
			ans = min(g[now][i], ans);
		}
		printf("Case #%d: %lld\n", cs, ans);
	}
}
