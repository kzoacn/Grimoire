#include <bits/stdc++.h>

typedef std::pair<int, int> pii;
#define mp std::make_pair

int n, m, a[500005];

namespace BIT {
	int c[500005];
	
	void init() {
		memset(c, 0, sizeof(int) * (n + 1));
	}
	
#define lowbit(x) ((x) & -(x))
	
	void modify(int a, int x) {
		for (int i = a; i <= n; i += lowbit(i))
			c[i] = std::max(c[i], x);
	}
	
	int query(int a) {
		int res = 0;
		for (int i = a; i > 0; i -= lowbit(i))
			res = std::max(res, c[i]);
		return res;
	}
}

int sorted[500005];

int hsh(int x) {
	return std::lower_bound(sorted + 1, sorted + *sorted + 1, x) - sorted;
}

int dp1[500005], dp2[500005];

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			sorted[i] = a[i];
		}
		
		std::sort(sorted + 1, sorted + n + 1);
		*sorted = std::unique(sorted + 1, sorted + n + 1) - sorted - 1;
		
		BIT::init();
		for (int i = 1; i <= n; ++i) {
			int t = hsh(a[i]);
			dp1[i] = BIT::query(t - 1) + 1;
			BIT::modify(t, dp1[i]);
		}
		
		BIT::init();
		for (int i = n; i; --i) {
			int t = *sorted - hsh(a[i]) + 1;
			dp2[i] = BIT::query(t - 1) + 1;
			BIT::modify(t, dp2[i]);
		}
		dp2[n + 1] = 0;
		
		int ans = std::max(dp1[n - m], dp2[m + 1]);
		
		BIT::init();
		for (int i = 1; i + m <= n; ++i) {
			BIT::modify(hsh(a[i]), dp1[i]);
			ans = std::max(ans, BIT::query(hsh(a[i + m + 1] - 1)) + dp2[i + m + 1]);
		}
		
		printf("Case #%d: %d\n", kase, ans);
	}
	
	return 0;
}
