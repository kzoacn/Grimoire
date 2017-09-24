#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 233333;
int x[MAXN], y[MAXN], totx[MAXN], toty[MAXN], testcase, n;

inline int cross(int x1, int y1, int x2, int y2) {
	return (1LL * x1 * y2 - 1LL * x2 * y1) % MOD;
}

inline int C3(int n) {
	return 1LL * n * (n - 1) * (n - 2) / 6 % MOD;
}

inline void update(int &sx, int &sy, int l, int r) {
	sx = (2LL * (totx[r] - totx[l - 1]) + sx) % MOD;
	sy = (2LL * (toty[r] - toty[l - 1]) + sy) % MOD;
}

int main() {
	scanf("%d", &testcase);
	for (int cs = 1; cs <= testcase; ++cs) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", &x[i], &y[i]);
		}
		
		int ans = 0;
		for (int i = 1; i <= n; ++i) {
			x[n + i] = x[i];
			y[n + i] = y[i];
		}
		for (int i = 1; i <= n; ++i) {
			ans = (ans + cross(x[i], y[i], x[i + 1], y[i + 1])) % MOD;
		}
cout << ans << endl;
		if (n == 3) {
			printf("%d\n", ans);
			continue;
		}
		int sx = 0, sy = 0;
		for (int i = 2; i <= n - 1; ++i) {
			sx = (sx + 1LL * (2 * (n - i) - 1) * x[i]);
			sy = (sy + 1LL * (2 * (n - i) - 1) * y[i]);
		}
		for (int i = 1; i <= n + n; ++i) {
			totx[i] = (totx[i - 1] + x[i]) % MOD;
			toty[i] = (toty[i - 1] + y[i]) % MOD;
		}
		int l = 2, r = n - 1;
		for (int i = 1; i <= n; ++i) {
cout << i << " " << l << " " << r << " " << sx << " " << sy << endl;
			ans = (ans + 1LL * x[i] * sy) % MOD;
			ans = (ans - 1LL * y[i] * sx) % MOD;
			sx = (sx - 1LL * x[i + 1] * (2 * (n - 2) - 1)) % MOD;
			sy = (sy - 1LL * y[i + 1] * (2 * (n - 2) - 1)) % MOD;
			update(sx, sy, l + 1, r);
			++l;
			++r;
			sx = (sx + x[r]) % MOD;
			sy = (sy + y[r]) % MOD;
		}
		ans = (ans + MOD) % MOD;
		printf("%d\n", ans);
	}
}


