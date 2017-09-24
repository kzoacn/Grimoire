#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL MOD = 998244353;

inline LL fpw(LL x, LL k, LL MOD) {
	LL ret = 1;
	for (; k; k >>= 1) {
		if (k & 1) {
			ret = ret * x % MOD;
		}
		x = x * x % MOD;
	}
	return ret;
}

inline LL get_c(LL n, LL m) {
	if (m > n || m < 0) {
		return 0;
	}
	m = min(m, n - m);
	LL ret = 1;
	for (int i = 1; i <= m; ++i) {
		ret = ret * (n - i + 1) % MOD;
		ret = ret * fpw(i, MOD - 2, MOD) % MOD;
	}
	return ret;
}

LL n, m;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	while (cin >> n >> m) {
		if (n % 2 != m % 2 || m > n) {
			cout << 0 << "\n";
			continue;
		}
		LL x = (n - m) >> 1, y = n / 2;
		LL c1 = get_c(n, 2 * y), c2 = get_c(y, y - (n - m) / 2);
		LL ans = 0;
		for (LL k = y; k >= x; --k) {
			ans = (ans + c1 * c2) % MOD;
			if (k == x) {
				continue;
			}
			c1 = c1 * (k * 2) % MOD;
			c1 = c1 * (k * 2 - 1) % MOD;
			c1 = c1 * fpw(n - 2 * k + 2, MOD - 2, MOD) % MOD;
			c1 = c1 * fpw(n - 2 * k + 1, MOD - 2, MOD) % MOD;
			
			c2 = c2 * (k - (n - m) / 2) % MOD;
			c2 = c2 * fpw(k, MOD - 2, MOD) % MOD;			
		}
		ans = (ans % MOD + MOD) % MOD;
		if ((n - m) / 2 % 2) {
			ans = MOD - ans;
		}
		ans = (ans % MOD + MOD) % MOD;
		cout << ans << "\n";
		//turn to positive
	}
}
