#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef long double LD;

const LL MOD = 1e9 + 7;
const LL inv2 = (MOD + 1) / 2;

LL a[3], n;

inline LL calc(LL n) {
	if (n < 0) {
		return 0;
	}
	n %= MOD;
	return (n + 2) * (n + 1) % MOD * inv2 % MOD;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	int testcase;
	cin >> testcase;
	for (int cs = 1; cs <= testcase; ++cs) {
		LL total = 0;
		for (int i = 0; i < 3; ++i) {
			LL x, y;
			cin >> x >> y;
			total += x;
			a[i] = y - x;
		}
		cin >> n;
		n -= total;
//cout << n << " " << a[0] << " " << a[1] << " " << a[2] << endl;
		
		LL ans = 0;
		for (int mask = 0; mask < 1 << 3; ++mask) {
			LL tmp = 0;
			LL t = 1;
			for (int i = 0; i < 3; ++i) {
				if ((mask >> i) & 1) {
					tmp += a[i] + 1;
					t = -t;
				}
			}
//cout << mask << " " << tmp << " " << calc(n - tmp) << endl;
			ans = (ans + t * calc(n - tmp)) % MOD;
		}
		ans = (ans + MOD) % MOD;
		cout << "Case #" << cs << ": " << ans << "\n";
	}
}
