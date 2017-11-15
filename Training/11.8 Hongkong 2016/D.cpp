#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const LL INF = 1e18;
const int MAXN = 71;
const int W = 80;
const int MAXS = (W * 2 + 1) * MAXN;
LL c[MAXN], H[MAXN], h[111111];
LL f[MAXN][MAXS][MAXN], g[MAXN][MAXS][MAXN];
int n, m;

int main() {
	cin >> n >> m;
	int cnt = 0;
	h[0] = 0;
	for (int i = 1; i <= n; ++i) {
		cin >> H[i] >> c[i];
		for (int j = -W; j <= W; ++j) {
			if (j + H[i] > 0) {
				h[++cnt] = j + H[i];
			}
		}
	}
	sort(h + 1, h + cnt + 1);
	cnt = unique(h + 1, h + cnt + 1) - h - 1;
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= cnt; ++j) {
			for (int k = 0; k <= m; ++k) {
				f[i][j][k] = g[i][j][k] = INF;
			}
		}
	}
	f[0][0][0] = 0;
	LL ans = INF;
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= cnt; ++j) {
			for (int k = 0; k <= m; ++k) {
				if (i && !j) {
					continue;
				}
				if (i) {
					if (j && k) {
						f[i][j][k] = min(f[i][j][k], g[i - 1][j - 1][k - 1] + c[i] * abs(h[j] - H[i]));
					}
					if (H[i] <= h[j]) {
						f[i][j][k] = min(f[i][j][k], f[i - 1][j][k]);
					} else {
						f[i][j][k] = min(f[i][j][k], f[i - 1][j][k] + c[i] * (H[i] - h[j]));
					}
				}
				if (k == m) {
					ans = min(ans, f[i][j][k]);
				}
				g[i][j][k] = f[i][j][k];
				if (j) {
					g[i][j][k] = min(g[i][j - 1][k], f[i][j][k]);
				}
			}
		}
	}
	cout << ans << endl;
}
