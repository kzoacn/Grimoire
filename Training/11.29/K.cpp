#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

LL k, p;

inline LL fpw(LL x, LL k, LL p) {
	LL ret = 1;
	x %= p;
	for (; k; k >>= 1) {
		if (k & 1) {
			ret = ret * x % p;
		}
		x = x * x % p;
	}
	return ret;
}

inline LL solve(LL n) {
	if (n == 0) {
		return 1;
	}
	if (n % 2 == 0) {
		return (solve(n - 1) + fpw(10, n, p)) % p;
	} else {
		LL tmp = solve(n / 2);
		return (fpw(10, n / 2 + 1, p) + 1) * tmp % p;
	}
}

int main() {
	freopen("zeroes.in", "r", stdin);
	freopen("zeroes.out", "w", stdout);
	
	cin >> k >> p;
	//cout << p << endl;
	LL ans = (k % p + k % p * fpw(10, k - 1, p)) % p;
//cout << ans << endl;
	ans -= solve(k - 1);
//cout << solve(k - 1) << endl;
	ans %= p;
	ans = (ans + p) % p;
	cout << ans << endl;
}
