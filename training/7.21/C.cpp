#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int dx[] = {0, 0, -1, 1};
const int dy[] = {-1, 1, 0, 0};
LL total;
char op[11];
LL ans = 0, pw[11];
int x[11], xx[11], y[11], yy[11];
bool exist_x[11][11], exist_y[11][11];
int M[11][11], seq[11];
int ex[111], ey[111], board[600][600][90];
int n, m, DFN;

inline void pre_dfs(int dep, int now) {
	if (dep > m) {
		return;
	}
	for (int k = 0; k < 4; ++k) {
		int tx = xx[now] + dx[k], ty = yy[now] + dy[k];
		if (M[tx][ty]) {
			seq[++DFN] = M[tx][ty];
			M[tx][ty] = 0;
			pre_dfs(dep + 1, seq[DFN]);
		}
	}
}

inline void dfs(int dep, LL nowtot) {
//cout << dep << " " << nowtot << endl;
	/*if (dep > m) {
		//if (op[0] == '*' && nowtot == 1 || nowtot == 0) {
			++ans;
		//}
		return;
	}*/
	if (dep + 2 > m) {
		if (nowtot <= 81 && nowtot >= 0) {
			ans += board[ex[x[m - 1]] | ey[y[m - 1]]][ex[x[m]] | ey[y[m]]][nowtot];
		}
		return;
	}
	if (op[0] == '*') {
		if (nowtot > pw[m - dep + 1]) {
			return;
		}
	} else {
		if (nowtot > n * (m - dep + 1) || nowtot < (m - dep + 1)) {
			return;
		}
	}
	int tx = n, ty = 1;
	/*if (dep == m) {
		tx = ty = nowtot;
		if (tx > n) {
			return;
		}
	}*/
	for (int i = tx; i >= ty; --i) {
//cout << i << endl;
		/*if (exist_x[x[dep]][i] || exist_y[y[dep]][i] || i > nowtot || op[0] == '*' && nowtot % i) {
			continue;
		}
		exist_x[x[dep]][i] = exist_y[y[dep]][i] = true;*/
		if ((ex[x[dep]] & (1 << i - 1)) || (ey[y[dep]] & (1 << i - 1)) || i > nowtot || op[0] == '*' && nowtot % i) {
			continue;
		}
		ex[x[dep]] ^= 1 << i - 1;
		ey[y[dep]] ^= 1 << i - 1;
		LL newtot = op[0] == '*' ? nowtot / i : nowtot - i;
		dfs(dep + 1, newtot);
		ex[x[dep]] ^= 1 << i - 1;
		ey[y[dep]] ^= 1 << i - 1;
		/*exist_x[x[dep]][i] = exist_y[y[dep]][i] = false;*/
	}
}

int main() {
	cin >> n >> m >> total >> op;
	for (int i = 1; i <= m; ++i) {
		//cin >> xx[i] >> yy[i];
		//M[xx[i]][yy[i]] = i;
		cin >> x[i] >> y[i];
	}
	/*DFN = 0;
	pre_dfs(1, 1);
	for (int i = 1; i <= m; ++i) {
		x[i] = xx[seq[i]];
		y[i] = yy[seq[i]];
		//cout << x[i] << " ---- " << y[i] << endl;
	}*/
	ans = 0;
	if (op[0] == '-') {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (i == j) {
					continue;
				}
				if (abs(i - j) == total) {
					++ans;
				}
			}
		}
		cout << ans << endl;
		return 0;
	}
	if (op[0] == '/') {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (i == j) {
					continue;
				}
				if (i == 1LL * j * total || j == 1LL * i * total) {
					++ans;
				}
			}
		}
		cout << ans << endl;
		return 0;
	}
	if (total == 1) {
		cout << 0 << endl;
		return 0;
	}
	if (m == 2) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (i == j) {
					continue;
				}
				if (op[0] == '+' && i + j == total || op[0] == '*' && i * j == total) {
					++ans;
				}
			}
		}
		cout << ans << endl;
		return 0;
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (i == j && (x[m - 1] == x[m] || y[m - 1] == y[m])) {
				continue;
			}
			for (int b1 = 0; b1 < (1 << n); ++b1) {
				if (b1 & (1 << i - 1)) {
					continue;
				}
				for (int b2 = 0; b2 < (1 << n); ++b2) {
					if (b2 & (1 << j - 1)) {
						continue;
					}
					int now = op[0] == '*' ? i * j : i + j;
					board[b1][b2][now]++;
				}
			}
		}
	}
	pw[0] = 1;
	for (int i = 1; i <= 10; ++i) {
		pw[i] = 1LL * pw[i - 1] * n;
	}
	dfs(1, total);
	cout << ans << endl;
}
