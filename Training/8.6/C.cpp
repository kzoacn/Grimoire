#include <bits/stdc++.h>

const int Mod = 1e9 + 7;

int n, m, a[1005], sorted[1005];

struct BIT {
	int c[1005];
	
	void init() { memset(c, 0, sizeof c); }
	
#define lowbit(x) ((x) & -(x))
	
	void add(int a, int x) {
		x %= Mod;
		for (int i = a; i <= *sorted; i += lowbit(i))
			c[i] = (c[i] + x) % Mod;
	}
	
	int query(int a) {
		int res = 0;
		for (int i = a; i; i -= lowbit(i))
			res = (res + c[i]) % Mod;
		return res;
	}
} bit[1005];

int hsh(int x) {
	return std::lower_bound(sorted + 1, sorted + *sorted + 1, x) - sorted;
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d%d", &n, &m);
		
		sorted[*sorted = 1] = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			sorted[++*sorted] = a[i];
		}
		
		std::sort(sorted + 1, sorted + *sorted + 1);
		*sorted = std::unique(sorted + 1, sorted + *sorted + 1) - sorted - 1;
		
		bit[0].init();
		bit[0].add(1, 1);
		
		for (int j = 1; j <= m; ++j)
			bit[j].init();
		
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				bit[j].add(hsh(a[i]), bit[j - 1].query(hsh(a[i]) - 1));
		
		printf("Case #%d: %d\n", kase, bit[m].query(*sorted));
	}
	
	return 0;
}
