#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int MAXN = 17;
const LL MOD = 998244353;
const LL inv2 = (MOD + 1) / 2;

int n, m;
int id[MAXN];
LL cnt[1 << MAXN];
vector<int> to[MAXN];
LL f[1 << MAXN][MAXN];
LL a[MAXN][MAXN];

inline void update(LL &dp, LL dpt) {
	dp = (dp + dpt) % MOD;
}

inline LL fpw(int x, int k, int MOD) {
	LL ret = 1;
	for (; k; k >>= 1) {
		if (k & 1) {
			ret = 1LL * ret * x % MOD;
		}
		x = 1LL * x * x % MOD;
	}
	return ret;
}

inline LL det(int n) {
	if (n == 0) {
		return 1;
	}
	int s = 0;
	for (int i = 1; i <= n; ++i) {
		int k = -1;
		for (int j = i; j <= n; ++j) {
			if (a[j][i]) {
				k = j;
				break;
			}
		}
		if (k == -1) {
			return 0;
		}
		if (k != i) {
			s ^= 1;
			for (int j = 1; j <= n; ++j) {
				swap(a[i][j], a[k][j]);
			}
		}
		for (int j = i + 1; j <= n; ++j) {
			LL r = a[j][i] * fpw(a[i][i], MOD - 2, MOD) % MOD;
			for (int k = 1; k <= n; ++k) {
				a[j][k] = (a[j][k] - a[i][k] * r) % MOD;
			}
		}
	}
	LL ret = 1;
	for (int i = 1; i <= n; ++i) {
		ret = 1LL * ret * a[i][i] % MOD;
	}
	ret = (ret + MOD) % MOD;
	if (s) {
		ret = (MOD - ret) % MOD;
	}
	return ret;
}

int main(){
	while (scanf("%d%d", &n, &m) == 2) {
		for (int i = 0; i <= n; ++i) {
			to[i].clear();
		}
		for (int i = 1; i <= m; ++i) {
			int u, v;
			scanf("%d%d", &u, &v);
			--u;
			--v;
			to[u].push_back(v);
			to[v].push_back(u);
		}
		
		for (int i = 0; i < 1 << n; ++i) {
			cnt[i] = 0;
		}
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < 1 << n; ++j) {
				for (int k = 0; k < n; ++k) {
					f[j][k] = 0;
				}
			}
			f[0][i] = 1;
			for (int mask = 0; mask < 1 << n; ++mask) {
				for (int j = i; j < n; ++j) {
					if (!f[mask][j]) {
						continue;
					}
					for (auto v : to[j]) {
						if ((mask >> v) & 1) {
							continue;
						}
						if (v == i && __builtin_popcount(mask) > 1) {
							update(cnt[mask | (1 << i)], f[mask][j]);
						}
						if (v > i) {
							update(f[mask | (1 << v)][v], f[mask][j]);
						}
					}
				}
			}
		}
		
		LL ans = 0;
		for (int mask = 0; mask < 1 << n; ++mask) {
			if (!cnt[mask]) {
				continue;
			}
			int tot = 1;
			memset(id, 0, sizeof(*id) * (n + 1));
			for (int i = 0; i < n; ++i) {
				if ((mask >> i) & 1) {
					id[i] = 1;
				}
			}
			for (int i = 0; i < n; ++i) {
				if (!id[i]) {
					id[i] = ++tot;
				}
			}
			for (int i = 1; i <= tot; ++i) {
				for (int j = 1; j <= tot; ++j) {
					a[i][j] = 0;
				}
			}
			for (int u = 0; u < n; ++u) {
				for (auto v : to[u]) {
					if (id[u] == id[v]) {
						continue;
					}
					a[id[u]][id[u]]++;
					a[id[u]][id[v]]--;
				}
			}
			LL c = cnt[mask] * inv2 % MOD;
			//cout << cnt[mask] << " " << c << endl;
	//cout << mask << " " << cnt[mask] << " " << det(tot - 1) << endl;
/*cout << "----------" << endl;
for (int i = 1; i <= tot; ++i) {
	for (int j = 1; j <= tot; ++j) {
		cout << a[i][j] << " ";
	}
	cout << endl;
}*/
			update(ans, c * det(tot - 1));
		}
		printf("%lld\n", ans);
	}
	return 0;
}


