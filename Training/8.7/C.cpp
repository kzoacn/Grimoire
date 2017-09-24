#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int MAXN = 1000000 + 10;
const int MOD = 998244353;
LL a[MAXN], f[MAXN], l, r, k, cs, tot;
int boo[MAXN], pri[MAXN];

inline void prep() {
	tot = 0;
	for (int i = 2; i < MAXN; ++i) {
		if (!boo[i]) {
			pri[++tot] = i;
		}
		for (int j = 1; j <= tot && pri[j] * i < MAXN; ++j) {
			int t = i * pri[j];
			boo[t] = 1;
			if (i % pri[j] == 0) {
				break;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	prep();
	cin >> cs;
	for (; cs; --cs) {
		cin >> l >> r >> k;
		for (int i = 1; i <= r - l + 1; ++i) {
			a[i] = i + l - 1;
			f[i] = 1;
		}
		for (int j = 1; j <= tot && pri[j] <= r; ++j) {
			int d = pri[j];
			for (LL i = ((l - 1) / d + 1) * d; i <= r; i += d) {
				int t = i - l + 1, s = 0;
				while (a[t] % d == 0) {
					a[t] /= d;
					++s;
				}
				f[t] = 1LL * f[t] * (s * k + 1) % MOD;
			}
		}
		LL ans = 0;
		for (int i = 1; i <= r - l + 1; ++i) {
			if (a[i] > 1) {
				f[i] = 1LL * f[i] * (k + 1) % MOD;
			}
			ans = (ans + f[i]) % MOD;
		}
		cout << ans << endl;
	}
}
