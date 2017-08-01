#include <bits/stdc++.h>

const int INF = 1e7;

struct Range {
	int l, r;
	
	Range() {}
	Range(int l, int r): l(l), r(r) {}
} stk[3005]; int top;

int n, a[3005], ia[3005];

int dp[3005][3005], mn[3005][3005], mx[3005][3005];

void init() {
	for (int l = 1; l <= n; ++l) {
		mn[l][l] = mx[l][l] = a[l];
		for (int r = l + 1; r <= n; ++r) {
			mn[l][r] = std::min(mn[l][r - 1], a[r]);
			mx[l][r] = std::max(mx[l][r - 1], a[r]);
		}
	}
	
	Range now;
	for (int l = 1; l <= n; ++l) {
		top = 0;
		for (int r = l; r <= n; ++r) {
			now = Range(a[r], a[r]);
			while (top && stk[top].r > now.l) {
				now.l = std::min(now.l, stk[top].l);
				now.r = std::min(now.r, stk[top].r);
				--top;
			}
			stk[++top] = now;
			dp[l][r] = top;
		}
	}
}

int calc(int l, int r) {
	int l2 = l, r2 = r, 
		l4 = mn[l][r], r4 = (r == n ? ia[n] : ia[mn[r + 1][n]]);
	if (!(mx[l2][r2] < mn[l4][r4] || mx[l4][r4] < mn[l2][r2]) || l2 < l4) return -INF;
	if (!(mn[l2][r2] == l4 && mx[l2][r2] == r4 && mn[l4][r4] == l2 && mx[l4][r4] == r2)) return -INF;
	
	int res = 0;
	if (l4 > 1) {
		if (mn[1][l4 - 1] == 1 && mx[1][l4 - 1] == l4) res += dp[1][l4 - 1];
		else return -INF;
	}
	if (r4)
	
	return -INF;
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i); ia[a[i]] = i;
		}
		
		init();
		/*
		for (int i = 1; i <= n; ++i)
			for (int j = i; j <= n; ++j)
				printf("dp[%d][%d] = %d\n", i, j, dp[i][j]);
		
		int ans = 1;
		for (int i = 1; i <= n; ++i)
			for (int j = i; j <= n; ++j)
				ans = std::max(ans, calc(i, j) - 2);
		*/
		printf("%d\n", calc(4, 5) - 2);
		
		//printf("%d\n", ans);
	}
	
	return 0;
}
