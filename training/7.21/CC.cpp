#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int dx[] = {0, 0, -1, 1};
const int dy[] = {-1, 1, 0, 0};
LL total;
char op[11];
LL ans = 0, pw[11];
int x[11], xx[11], y[11], yy[11];
int exist_x[20][20], exist_y[20][20];
int M[11][11], seq[11];
int n, m, DFN;
int nowtot;
inline void dfs1(int dep) {
	if (dep == m) {
		if (nowtot >= 1 && nowtot <= n) {
			if (!exist_x[x[m]][nowtot] && !exist_y[y[m]][nowtot]) {
				++ans;
			}
		}
		return;
	}
	if (nowtot > n * (m - dep + 1) || nowtot < (m - dep + 1)) {
		return;
	}
	//int tx = min(nowtot, 1LL * n), ty = 1;
	
	for (int i = 1; i<=n; i++) {
		if (exist_x[x[dep]][i] || exist_y[y[dep]][i]) {
			continue;
		}
		exist_x[x[dep]][i] = exist_y[y[dep]][i] = 1;
		nowtot -= i;
		dfs1(dep + 1);
		nowtot+=i;
		exist_x[x[dep]][i] = exist_y[y[dep]][i] = 0;
	}
}

inline void dfs2(int dep, LL nowtot) {
	if (nowtot > pw[m - dep + 1]) {
		return;
	}
	int tx = min(nowtot, 1LL * n), ty = 1;
	if (dep == m) {
		if (nowtot >= 1 && nowtot <= n && !exist_x[x[m]][nowtot] && !exist_y[y[m]][nowtot]) {
			++ans;
		}
		return;
	}
	for (int i = tx; i >= ty; --i) {
		if (exist_x[x[dep]][i] || exist_y[y[dep]][i] || nowtot % i) {
			continue;
		}
		exist_x[x[dep]][i] = exist_y[y[dep]][i] = true;
		LL newtot = nowtot / i;
		dfs2(dep + 1, newtot);
		exist_x[x[dep]][i] = exist_y[y[dep]][i] = false;
	}
}

int main() {
	cin >> n >> m >> total >> op;
	for (int i = 1; i <= m; ++i) {
		cin >> x[i] >> y[i];
	}
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
	pw[0] = 1;
	for (int i = 1; i <= 10; ++i) {
		pw[i] = 1LL * pw[i - 1] * n;
	}
	if (op[0] == '+') {
		nowtot=total;
		dfs1(1);
	} else {
		dfs2(1, total);
	}
	cout << ans << endl;
}

