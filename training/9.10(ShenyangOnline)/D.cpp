#include <bits/stdc++.h>

const int Lim = 1e5;

int n, k, a[100005];

namespace BIT {
	int c[100005];
	
	void clear() {
		memset(c, 0, sizeof c);
	}
	
#define lowbit(x) ((x) & -(x))
	
	void modify(int x, int y) {
		for (int i = x; i <= Lim; i += lowbit(i))
			c[i] = std::max(c[i], y);
	}
	
	int query(int x) {
		int res = 0;
		for (int i = x; i > 0; i -= lowbit(i))
			res = std::max(res, c[i]);
		return res;
	}
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= n; ++i) scanf("%d", a + i);
		
		bool flag = 0;
		
		BIT::clear();
		int ans = 0;
		for (int i = 1; i <= n; ++i) {
			int tmp = BIT::query(a[i]) + 1;
			ans = std::max(ans, tmp);
			BIT::modify(a[i], tmp);
		}
		if (ans + k >= n) flag = 1;
		
		BIT::clear();
		ans = 0;
		for (int i = n; i; --i) {
			int tmp = BIT::query(a[i]) + 1;
			ans = std::max(ans, tmp);
			BIT::modify(a[i], tmp);
		}
		if (ans + k >= n) flag = 1;
		
		puts(flag ? "A is a magic array." : "A is not a magic array.");
	}
	
	return 0;
}
