#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 27;
LL dp[N][2], a[N], n;

int main() {
	dp[0][0] = 1;
	dp[1][0] = 5;
	dp[1][1] = 0;
	for (int i = 2; i < N; ++i) {
		if (i % 2 == 0) {
			dp[i][1] = dp[i - 1][0] * 2 + dp[i - 1][1] * 3;
			dp[i][0] = dp[i - 1][0] * 3 + dp[i - 1][1] * 2;
		} else {
			dp[i][1] = dp[i - 1][1] * 5;
			dp[i][0] = dp[i - 1][0] * 5;
		}
	}
	
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n, n != -1) {
		LL ans = 0;
		int l = 0;
		for (; n; n /= 5) {
			a[++l] = n % 5;
		}
		int now = 0;
		a[0] = 1;
		for (int i = l; i >= 1; --i) {
			LL even = (a[i] + 1) / 2, odd = a[i] - even;
//cout << i << " " << even << " " << odd << endl;
			if (i % 2 == 0) {
				ans += even * dp[i - 1][0 ^ now];
				ans += odd * dp[i - 1][1 ^ now];
			} else {
				ans += a[i] * dp[i - 1][0 ^ now];
			}
			now ^= (i - 1) * a[i] % 2;
		}
		if (now == 0) {
			ans++;
		}
		cout << ans << endl;
	}
}
