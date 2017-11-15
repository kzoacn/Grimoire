#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	LL n, m, k;
	while (cin >> n >> m >> k) {
		LL ans = 0;
		LL t = k / 2;
		for (LL a = 1; a < t && a <= n; ++a) {
			LL up = min(t - a, m);
			assert(up >= 0);
			ans += (n - a + 1) * ((m + m - up + 1) * up / 2);
		}
		cout << ans << endl;
	}
}
