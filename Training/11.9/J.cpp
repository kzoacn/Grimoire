#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const LL MOD = 1e9 + 7;
const int MAXN = 2333;
LL pw[MAXN], dp[MAXN][MAXN], f[MAXN], comb[MAXN][MAXN];
int n, p[MAXN];

struct C {
	LL a[MAXN];
	inline int lowbit(int x) {
		return x & (-x);
	}
	inline void modify(int k, LL x) {
		for (; k <= n; k += lowbit(k)) {
			a[k] = (a[k] + x) % MOD;
		}
	}
	inline LL query(int k) {
		LL ret = 0;
		for (; k; k -= lowbit(k)) {
			ret += a[k];
		}
		ret %= MOD;
		return ret;
	}
} c[MAXN];

int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &p[i]);
	}
	
	pw[0] = 0;
	for (int i = 1; i <= n; ++i) {
		pw[i] = 1;
		for (int j = 1; j <= n; ++j) {
			pw[i] = pw[i] * i % MOD;
		}
	}
	for (int i = 0; i <= n; ++i) {
		comb[i][0] = comb[i][i] = 1;
		for (int j = 1; j < i; ++j) {
			comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
		}
	}
	for (int k = 1; k <= n; ++k) {
		f[k] = 0;
		LL t = 1;
		for (int i = 0; i <= k; ++i) {
			f[k] = (f[k] + t * comb[k][i] * pw[k - i]) % MOD;
			t = -t;
		}
	}
	
	dp[0][0] = 1;
	c[0].modify(0 + 1, dp[0][0]);
	
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= i; ++j) {
			dp[i][j] = c[j - 1].query(p[i] - 1 + 1);
			c[j].modify(p[i] + 1, dp[i][j]);
		}
	}
	
	LL ans = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= i; ++j) {
			ans = (ans + f[j] * dp[i][j]) % MOD;
		}
	}
	
	ans = (ans + MOD) % MOD;
	cout << ans << endl;
}
