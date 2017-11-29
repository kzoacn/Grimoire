#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL MOD = 1e9 + 9;
const int MAXN = 300;
int a[MAXN][MAXN], b[MAXN][MAXN], pri[MAXN][MAXN];
int cs, tot, n, m;
int board[5][5];
bool ok[MAXN];

inline void mul(int k) {
	if (k == 0) {
		memset(a, 0, sizeof(a));
		for (int i = 0; i < tot; ++i) {
			a[i][i] = 1;
		}
		return;
	}
	mul(k / 2);
	for (int i = 0; i < tot; ++i) {
		if (!ok[i]) continue;
		for (int j = 0; j < tot; ++j) {
			if (!ok[j]) continue;
			b[i][j] = 0;
			for (int k = 0; k < tot; ++k) {
				b[i][j] = (b[i][j] + 1LL * a[i][k] * a[k][j]) % MOD;
			}
		}
	}
	if (k % 2 == 0) {
		for (int i = 0; i < tot; ++i) {
			for (int j = 0; j < tot; ++j) {
				a[i][j] = b[i][j];
			}
		}
	} else {
		for (int i = 0; i < tot; ++i) {
			if (!ok[i]) continue;
			for (int j = 0; j < tot; ++j) {
				if (!ok[j]) continue;
				a[i][j] = 0;
				for (int k = 0; k < tot; ++k) {
					a[i][j] = (a[i][j] + 1LL * pri[i][k] * b[k][j]) % MOD;
				}
			}
		}
	}
}

int main() {
	cin >> cs;
	for (; cs; --cs) {
		cin >> n >> m;
		
		memset(pri, 0, sizeof(pri));
		memset(ok, 0, sizeof(ok));
		int c = 0;
		for (int mask = 0; mask < 1 << (3 * n); ++mask) {
			memset(board, 0, sizeof(board));
			for (int x = 1, y = 1, i = 0; i < (3 * n); ++i) {
				board[x][y] = (mask >> i) & 1;
				if (x < n) {
					++x;
				} else {
					++y;
					x = 1;
				}
			}
			
			bool flag = true;
			for (int i = 1; i <= n && flag; ++i) {
				for (int j = 1; j <= 3 && flag; ++j) {
					for (int ii = 1; ii <= n && flag; ++ii) {
						for (int jj = 1; jj <= 3 && flag; ++jj) {
							if (!board[i][j] || !board[ii][jj]) {
								continue;
							}
							int x = abs(i - ii), y = abs(j - jj);
							if (x == 1 && y == 2 || x == 2 && y == 1) {
								flag = false;
							}
						}
					}
				}
			}
			
			int x[2] = {0, 0};
			/*for (int k = 0; k < 2; ++k) {
				x[k] = 0;
				for (int i = 1; i <= 2; ++i) {
					for (int j = 1; j <= n; ++j) {
						x[k] += board[j][i + k] << (j - 1 + (i - 1) * 4);
					}
				}
			}*/
			x[0] = mask % (1 << (n + n));
			x[1] = mask >> n;
			if (flag) { ++c;
				ok[x[0]] = 1;
				pri[x[0]][x[1]] = 1;
			}
		}
		cout << c << endl;
		//return 0;
		tot = 1 << (2 * n);
		mul(m - 1);
		LL ans = 0;
		for (int i = 0; i < 1 << n; ++i) {
			for (int j = 0; j < tot; ++j) {
				ans = (ans + a[i][j]) % MOD;
			}
		}
		cout << ans << endl;
	}
}
