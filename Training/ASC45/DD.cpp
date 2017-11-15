#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 33;
LL f[N][N][N], g[N][N][N], h[N][N][N];

inline void prep() {
	f[1][0][0] = 1;
	for (int i = 0; i < N; ++i) {
		h[1][i][0] = 1;
		g[1][i][0] = i == 0 ? 1 : g[1][i - 1][0] + 1;
	}
	for (int i = 2; i < N; ++i) {
		for (int up = 0; up < N; ++up) {
			for (int a = 0; a < N; ++a) {
				//j = 1
				h[i][up][a] = g[i - 1][up][a];
				//j = i
				if (a && up) {
					h[i][up][a] += g[i - 1][up - 1][a - 1];
				}
				for (int j = 2; j < i; ++j) {
					for (int t = 0; t < up; ++t) {
						for (int ta = 0; ta < a; ++ta) {
							h[i][up][a] += h[j - 1][t][ta] * g[i - j][up - t][a - ta - 1];
						}
					}					
				}
				g[i][up][a] = h[i][up][a];
				if (up) {
					g[i][up][a] += g[i][up - 1][a];
				}
			}
		}
	}
	
	for (int i = 2; i < N; ++i) {
		for (int up = 0; up < N; ++up) {
			for (int a = 0; a < N; ++a) {
				//j = 1
				f[i][up][a] = up == 0 && a == 0;
				//j = i
				if (a && up) {
					for (int t = 0; t < up; ++t) {
/*if (i == 2 && up == 2 && a == 1) {
	cout << "now: " << t << " " << f[i - 1][t][a - 1] << " " << f[i][up][a] << endl;
}*/
						if (a - 1 + 1 >= up) {
							f[i][up][a] += f[i - 1][t][a - 1];
						}
					}
				}
				for (int j = 2; j < i; ++j) {
					for (int t = 0; t < up; ++t) {
						for (int ta = 0; ta < a; ++ta) {
							if (ta + 1 >= up) {
								f[i][up][a] += f[j - 1][t][ta] * g[i - j][up - t][a - ta - 1];
							}
						}
					}					
				}
			}
		}
	}
}

int n;

int main() {
	freopen("catalian.in", "r", stdin);
	freopen("catalian.out", "w", stdout);
	prep();
	int cs = 0;
	while (cin >> n, n) {
		LL ans = 0;
		for (int i = 0; i <= n; ++i) {
			for (int j = 0; j <= n; ++j) {
			//cout << n << " "<< i << " " << j << " " << f[n][i][j] << endl;
				ans += f[n][i][j];
			}
		}
		cout << "Case #" << ++cs << ": " << ans << endl;
	}
}
