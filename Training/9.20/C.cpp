#include <bits/stdc++.h>

const int cost[10] = {0, 1, 2, 3, 4, 5, 4, 3, 2, 1};

char s[1005]; int n;

int a[1005], b[1005];

int dp[2][10][10];

int main() {
	while (~scanf("%s", s + 1)) {
		n = strlen(s + 1);
		for (int i = 1; i <= n; ++i) a[i] = s[i] - '0';
		
		scanf("%s", s + 1);
		for (int i = 1; i <= n; ++i) b[i] = s[i] - '0';
		
		if (n == 1) {
			printf("%d\n", cost[std::abs(a[1] - b[1])]);
			continue;
		}
		
		memset(dp, 0x3f, sizeof dp);
		dp[0][a[1]][a[2]] = 0;
		int cur = 0;
		for (int i = 0; i <= n - 3; ++i) {
			memset(dp[cur ^ 1], 0x3f, sizeof dp[cur ^ 1]);
			for (int j = 0; j <= 9; ++j)
				for (int k = 0; k <= 9; ++k)
					for (int dlt2 = 0; dlt2 <= 9; ++dlt2)
						for (int dlt3 = 0; dlt3 <= 9; ++dlt3) {
							int &tmp = dp[cur ^ 1][(k + dlt2 + dlt3) % 10][(a[i + 3] + dlt3) % 10];
							tmp = std::min(tmp, dp[cur][j][k] + cost[dlt2] + cost[dlt3] + cost[std::abs((j + dlt2 + dlt3) % 10 - b[i + 1])]);
						}
			cur ^= 1;
		}
		int ans = 0x3f3f3f3f;
		
		for (int j = 0; j <= 9; ++j)
			for (int k = 0; k <= 9; ++k)
				for (int dlt2 = 0; dlt2 <= 9; ++dlt2)
					ans = std::min(ans, dp[cur][j][k] + cost[dlt2] + cost[std::abs((j + dlt2) % 10 - b[n - 1])] + cost[std::abs((k + dlt2) % 10 - b[n])]);
		
		printf("%d\n", ans);
	}
	
	return 0;
}
