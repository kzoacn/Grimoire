#include <bits/stdc++.h>

const int MAXN = 2e5 + 5;

int n;

namespace BIT {
	int mx[MAXN];
	
	void init() {
		memset(mx, 0, sizeof mx);
	}
	
#define lowbit(x) ((x) & -(x))
	
	void modify(int a, int x) {
		for (int i = a; i <= n; i += lowbit(i))
			mx[i] = std::max(mx[i], x);
	}
	
	int query(int a) {
		int res = 0;
		for (int i = a; i > 0; i -= lowbit(i))
			res = std::max(res, mx[i]);
		return res;
	}
}

int permu[MAXN * 2];

int main() {
#ifndef LOCAL
	freopen("improvements.in", "r", stdin);
	freopen("improvements.out", "w", stdout);
#endif
	
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", permu + i);
		permu[n * 2 - i + 1] = permu[i];
	}
	
	BIT::init();
	
	int ans = 0;
	for (int i = 1; i <= n * 2; ++i) {
		int tmp = BIT::query(permu[i] - 1) + 1;
		ans = std::max(ans, tmp);
		BIT::modify(permu[i], tmp);
	}
	
	printf("%d\n", ans);
	
	return 0;
}
