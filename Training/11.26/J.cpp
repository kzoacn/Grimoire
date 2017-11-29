#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MAXN = 233;
int a[MAXN], s[MAXN], f[MAXN][MAXN], g[MAXN][MAXN][MAXN];
int n, l, r;

int main() {
	while (scanf("%d%d%d", &n, &l, &r) != EOF) {
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			s[i] = s[i - 1] + a[i];
		}
		
		for (int i = 0; i <= n + 1; ++i) {
			for (int j = 0; j <= n + 1; ++j) {
				f[i][j] = INF;
				for (int k = 0; k <= n + 1; ++k) {
					g[i][j][k] = INF;
				}
			}
		}
		
		for (int i = 1; i <= n; ++i) {
			f[i][i] = g[i][i][1] = 0;
		}
		for (int d = 1; d < n; ++d) {
			for (int i = 1; i + d <= n; ++i) {
				int j = i + d;
				for (int k = 2; k <= r && k <= d + 1; ++k) {
					for (int t = i; t < j; ++t) {
						/*if (g[i][t][k - 1] == INF) {
							break;
						}*/
						g[i][j][k] = min(g[i][j][k], g[i][t][k - 1] + f[t + 1][j]);
					}
				}
				for (int k = l; k <= r; ++k) {
					f[i][j] = min(f[i][j], g[i][j][k] + s[j] - s[i - 1]);
				}
				g[i][j][1] = f[i][j];
//cout << i << " " << j << " " << f[1][n] << endl;
			}
		}
//cout << g[1][2][2] << endl;
//cout << f[1][2] << endl;
//cout << g[1][3][2] << endl;
//cout << 
//cout << g[1][1][1] << " " << f[2][2] << endl;
		int ans = f[1][n] == INF ? 0 : f[1][n];
		printf("%d\n", ans);
	}
}
