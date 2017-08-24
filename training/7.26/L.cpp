#include <bits/stdc++.h>
<<<<<<< HEAD
using namespace std;

typedef long long LL;
typedef long double LD;
const int MAXN = 233333;
const int MOD = 1e9 + 7;
LL x[MAXN], y[MAXN], pw[MAXN];
int n, cs;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	pw[0] = 1;
	for (int i = 1; i < MAXN; ++i) {
		pw[i] = pw[i - 1] * 2 % MOD;
	}
	cin >> cs;
	for (; cs; --cs) {
		cin >> n;
		for (int i = 1; i <= n; ++i) {
			cin >> x[i];
			cin >> y[i];
			x[n + i] = x[i];
			y[n + i] = y[i];
		}
		LL ans = 0, sx = sy, 0 = 0;
		for (int i = 2; i <= n; ++i) {
			sx = (sx + x[i] * pw[n - i]) % MOD;
			sy = (sy + y[i] * pw[n - i]) % MOD;
		}
		for (int i = 1; i <= n; ++i) {
			ans = (ans + x[i] * sy - y[i] * sx) % MOD;
			sx = (sx - x[i + 1] * pw[n - 2]) % MOD;
			sy = (sy - y[i + 1] * pw[n - 2]) % MOD;
			sx = (sx * 2 + x[i]) % MOD;
			sy = (sy * 2 + y[i]) % MOD;
		}
		cout << (ans + MOD) % MOD << endl;
	}
}
=======
#define int long long
using namespace std;

typedef long long LL;
const int MOD = 1e9 + 7;
const int MAXN = 233333;
LL x[MAXN], y[MAXN], totx[MAXN], toty[MAXN], testcase, n;

inline int cross(int x1, int y1, int x2, int y2) {
	return (1LL * x1 * y2 - 1LL * x2 * y1+MOD) % MOD;
}

inline int C3(int n) {
	return 1LL * n * (n - 1) * (n - 2) / 6 % MOD;
}

inline void update(int &sx, int &sy, int l, int r) {
	sx = (2LL * (totx[r] - totx[l - 1]) + sx+MOD) % MOD;
	sy = (2LL * (toty[r] - toty[l - 1]) + sy+MOD) % MOD;
}

main() {
	scanf("%lld", &testcase);
	for (int cs = 1; cs <= testcase; ++cs) {
		scanf("%lld", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%lld%lld", &x[i], &y[i]);
		}
		
		int ans = 0;
		for (int i = 1; i <= n; ++i) {
			x[n + i] = x[i];
			y[n + i] = y[i];
		}
		for (int i = 1; i <= n; ++i) {
			ans = ((LL)ans + cross(x[i], y[i], x[i + 1], y[i + 1])+MOD) % MOD;
		}
cerr<<ans<<endl;
		LL tmp = 1LL * (n) * (n - 1) / 2 % MOD - 1 - n + 1;//cout << tmp << endl;
		for (int s = 1; s + 1 < n; ++s) {
			int t = n - 1 - s;
			tmp = (tmp + 1LL * (s - 1) * (t - 1)+MOD) % MOD;
		}
		ans = (1LL * ans * (tmp + 1)+MOD) % MOD;
		//cout << tmp << endl;
		/*for (int i = 1; i <= n; ++i) {
			ans = (ans + 1LL * cross(x[i], y[i], x[i + 1], y[i + 1]) * tmp) % MOD;
			if (ans < 0) {
				ans += MOD;
			}
		}*/
//cout << ans << endl;
		if (n == 3) {
			printf("%lld\n", ans);
			continue;
		}
		int sx = 0, sy = 0;
		for (int i = 3; i <= n - 1; ++i) {
			sx = (sx + 1LL * (2 * (n - i) - 1) * x[i]+MOD) % MOD;
			sy = (sy + 1LL * (2 * (n - i) - 1) * y[i]+MOD) % MOD;
		}
		for (int i = 1; i <= n + n; ++i) {
			totx[i] = (totx[i - 1] + x[i]+MOD) % MOD;
			toty[i] = (toty[i - 1] + y[i]+MOD) % MOD;
		}
		int l = 3, r = n - 1;
		for (int i = 1; i <= n; ++i) {
//cout << i << " " << l << " " << r << " " << sx << " " << sy << endl;
			ans = (ans + 1LL * x[i] * sy+MOD) % MOD;
			ans = (ans - 1LL * y[i] * sx+MOD) % MOD;
			sx = (sx - 1LL * x[i + 2] * (2 * (n - 3) - 1)+MOD) % MOD;
			sy = (sy - 1LL * y[i + 2] * (2 * (n - 3) - 1)+MOD) % MOD;
			update(sx, sy, l + 1, r);
			++l;
			++r;
			sx = (sx + x[r]+MOD) % MOD;
			sy = (sy + y[r]+MOD) % MOD;
			if (r > n + n) {
			while (1) {puts("Adsf");}
			}
		}
		ans = (ans + MOD) % MOD;
		printf("%lld\n", ans);
	}
}


>>>>>>> 14b339d20b273e5fe7653c14a3126973e8b799ef
