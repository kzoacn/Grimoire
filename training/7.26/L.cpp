#include <bits/stdc++.h>
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
