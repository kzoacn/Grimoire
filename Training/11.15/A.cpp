#include <bits/stdc++.h>

const int cnt[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

int n;

int dp[1000005];
bool vis[1000005];

int main() {
#ifndef LOCAL
	freopen("auxiliary.in", "r", stdin);
	freopen("auxiliary.out", "w", stdout);
#endif
	
	std::cin >> n;
	
	dp[0] = 0;
	vis[0] = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= 9; ++j)
			if (i - cnt[j] >= 0 && vis[i - cnt[j]]) {
				vis[i] = 1;
				dp[i] = std::max(dp[i], dp[i - cnt[j]] + j);
			}
	}
	printf("%d\n", dp[n]);
	
	return 0;
}
