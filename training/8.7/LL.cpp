#include <bits/stdc++.h>

#define __advance //__attribute__((optimize("O3")))

const int Mod = 998244353;
int lim;
const int N = 3333;
int n, m, a[2005], b[2005];

#define fix(x) if (x >= Mod) x -= Mod

namespace BIT {
	int c[2][2005][2005];
	
	void init() {
		memset(c, 0, sizeof c);
	}
	
#define lowbit(x) ((x) & -(x))
	
	void add(int t, int x, int y, int val) {
		for (int i = x; i <= m; i += lowbit(i))
			for (int j = y; j <= lim; j += lowbit(j)) {
				c[t][i][j] += val; fix(c[t][i][j]);
			}
	}
	
	int query(int t, int x, int y) {
		int res = 0;
		for (int i = x; i > 0; i -= lowbit(i))
			for (int j = y; j > 0; j -= lowbit(j)) {
				res += c[t][i][j]; fix(res);
			}
		return res;
	}
}

int dp[2005][2005][2];

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d%d", &n, &m);
		lim = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i); lim = std::max(lim, a[i]);
		}
		for (int i = 1; i <= m; ++i) {
			scanf("%d", b + i); lim = std::max(lim, b[i]);
		}
		
		BIT::init();
		
		long long ans = 0;
		
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) if (a[i] == b[j]) {
				dp[i][j][0] = BIT::query(1, j - 1, lim) - BIT::query(1, j - 1, a[i]) + Mod + 1; fix(dp[i][j][0]);
				dp[i][j][1] = BIT::query(0, j - 1, a[i] - 1);
				ans += dp[i][j][0] + dp[i][j][1];
			}
			for (int j = 1; j <= m; ++j) if (a[i] == b[j]) {
				for (int k = 0; k < 2; ++k)
					BIT::add(k, j, a[i], dp[i][j][k]);
			}
		}
		
		printf("%d\n", (int)(ans % Mod));
	}
	
	return 0;
}
