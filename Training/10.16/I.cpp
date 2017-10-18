#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2500;
const int MOD = 1e9 + 7;
typedef long long LL;

int n, m, A, cnt;
vector<int> a;
int e[MAXN][55];
vector<int> inv[MAXN];
map<vector<int>, int> M;
int f[233][55][MAXN][2];

inline void print(vector<int> a) {
	for (auto u : a) cout << u << " ";
	cout << endl;
}

inline int get_fa(vector<int> &fa, int u) {
	return fa[u] == u ? u : fa[u] = get_fa(fa, fa[u]);
}

inline int dfs(vector<int> a) {
	auto it = M.find(a);
	if (it != M.end()) {
		return it -> second;
	}
	int now = M[a] = ++cnt;
	e[now][m] = now;
	inv[now] = a;
	for (int i = 2; i <= m; ++i) {
		vector<int> b = a;
		for (int j = i, k = 1; j <= m; ++j, ++k) {
			if (get_fa(b, j) != get_fa(b, k)) {
				int u = get_fa(b, j), v = get_fa(b, k);
				b[u] = b[v] = min(u, v);
			}
		}
		for (int j = 1; j <= m; ++j) {
			b[j] = get_fa(b, j);
		}
		//e[now].push_back(dfs(b));
		e[now][i - 1] = dfs(b);
	}
	return now;
}

inline void update(int &f, LL g, int tp = 0) {
	if (tp == 1) {
		f += g;
		return;
	}
	f = (f + g) % MOD;
}

inline int fpm(int x, int k, int mod) {
	int ret = 1;
	for (; k; k >>= 1) {
		if (k & 1) {
			ret = 1LL * ret * x % MOD;
		}
		x = 1LL * x * x % MOD;
	}
	return ret;
}

inline int calc(int A, vector<int>& a) {
	int s = 0;
	for (int i = 1; i <= m; ++i) {
		s += a[i] == i;
	}
	return fpm(A, s, MOD);
}

int main() {
	scanf("%d%d%d", &n, &m, &A);
	
	a.clear();
	a.push_back(0);
	for (int i = 1; i <= m; ++i) {
		a.push_back(i);
	}
	cnt = 0;
	M.clear();
	dfs(a);
	
	f[0][m][1][0] = 1;
	for (int i = 0; i < n; ++i) {
		for (int j = 1; j <= m; ++j) {
			for (int s = 1; s <= cnt; ++s) {
				for (int t = 0; t < 2; ++t) {
					if (!f[i][j][s][t]) {
						continue;
					}
					//cout << i + 1 << " " << j + 1 << " " << s << endl;
					if (j == m && i + 2 - j > 0) {
						update(f[i + 1][m][s][t], 1LL * A * f[i][j][s][t]);
					} else {
						update(f[i + 1][min(m, j + 1)][s][t], f[i][j][s][t]);
					}
					if (i + 1 >= m) {
						update(f[i + 1][1][e[s][j]][t | 1], -f[i][j][s][t]);
					}
				}
			}
		}
	}
	
/*for (int i = 0; i <= n; ++i) {
	for (int j = 1; j <= m; ++j) {
		for (int s = 1; s <= cnt; ++s) {
cout << i << " " << j << " " << s << " " << f[i][j][s][1] << endl;
		}
	}
}*/
	
	int ans = 0;
	for (int j = 1; j <= m; ++j) {
		for (int s = 1; s <= cnt; ++s) {
			update(ans, f[n][j][s][1] * 1LL * calc(A, inv[s]) % MOD * fpm(A, j - 1, MOD));
		}
	}
	ans = (ans + MOD) % MOD;
	ans = (MOD - ans) % MOD;
	cout << ans << endl;
}
