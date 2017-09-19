#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;

int n, L, K;

int cd[1005];

int dp[1005][1005][2];

int sorted[1005];

int Tran(int l, int r, int t) {
	if (t == 0) return std::min(dp[l + 1][r][0] + std::abs(sorted[l] - sorted[l + 1]), dp[l + 1][r][1] + std::abs(sorted[l] - sorted[r]));
	return std::min(dp[l][r - 1][0] + std::abs(sorted[r] - sorted[l]), dp[l][r - 1][1] + std::abs(sorted[r] - sorted[r - 1]));
}

bool check(int mid) {
	for (int i = 1; i <= *sorted; ++i) {
		int tmp = std::abs(K - sorted[i]);
		if (tmp + cd[sorted[i]] > mid) tmp = INF;
		dp[i][i][0] = dp[i][i][1] = tmp;
	}
	for (int len = 2; len <= *sorted; ++len)
		for (int l = 1; l + len - 1 <= *sorted; ++l) {
			int r = l + len - 1;
			dp[l][r][0] = Tran(l, r, 0);
			if (dp[l][r][0] + cd[sorted[l]] > mid) dp[l][r][0] = INF;
			dp[l][r][1] = Tran(l, r, 1);
			if (dp[l][r][1] + cd[sorted[r]] > mid) dp[l][r][1] = INF;
		}
	
//	std::cerr << mid << " " << dp[1][*sorted][0] << std::endl;
	
	return dp[1][*sorted][0] + cd[0] <= mid || dp[1][*sorted][1] + sorted[*sorted] <= mid;
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		memset(cd, 0, sizeof cd);
		
		scanf("%d%d%d", &n, &L, &K);
		for (int x, y, i = 1; i <= n; ++i) {
			scanf("%d%d", &x, &y);
			sorted[i] = x;
			cd[x] = std::max(cd[x], y);
		}
		sorted[n + 1] = 0;
		
		std::sort(sorted + 1, sorted + n + 2);
		*sorted = std::unique(sorted + 1, sorted + n + 2) - sorted - 1;
		
//		std::cerr << *sorted << std::endl;
		
		int ans = -1, l = 0, r = 50000;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (check(mid)) ans = mid, r = mid - 1;
			else l = mid + 1;
		}
		printf("Case #%d: %d\n", kase, ans);
	}
	
	return 0;
}
