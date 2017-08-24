#include <bits/stdc++.h>

int dp[2][25][25][25][25];

int n, A, B;
int cnt[205];

int main() {
	scanf("%d%d%d", &n, &A, &B);
	for (int x, i = 1; i <= n; ++i) {
		x = 0;
		scanf("%d", &x); cnt[i] += x;
	}
	for (int x, i = 1; i <= n; ++i) {
		x = 0;
		scanf("%d", &x); cnt[i] += x;
	}
	
	memset(dp[0], 0x3f, sizeof dp[0]);
	dp[0][0][0][0][0] = 0;
	
	int cur = 1;
	for (int i = 1; i <= n; ++i) {
		memset(dp[cur], 0x3f, sizeof dp[cur]);
		for (int a1 = 0; a1 <= A; ++a1)
		for (int b1 = 0; b1 <= B; ++b1) if ((a1 == 0) == (b1 == 0))
		for (int a2 = 0; a2 <= A; ++a2)
		for (int b2 = 0; b2 <= B; ++b2) if ((a2 == 0) == (b2 == 0)) {
			if (cnt[i] == 0) {
				int A1 = a1, A2 = a2, B1 = std::max(b1 - 1, 0), B2 = std::max(b2 - 1, 0);
				if (A1 == 0 || B1 == 0) A1 = B1 = 0;
				if (A2 == 0 || B2 == 0) A2 = B2 = 0;
				dp[cur][A1][B1][A2][B2] = std::min(dp[cur][A1][B1][A2][B2], dp[cur ^ 1][a1][b1][a2][b2]);
				dp[cur][A - 1][B - 1][A2][B2] = std::min(dp[cur][A - 1][B - 1][A2][B2], dp[cur ^ 1][a1][b1][a2][b2] + 1);
				dp[cur][A1][B1][A - 1][B - 1] = std::min(dp[cur][A1][B1][A - 1][B - 1], dp[cur ^ 1][a1][b1][a2][b2] + 1);
				dp[cur][A - 1][B - 1][A - 1][B - 1] = std::min(dp[cur][A - 1][B - 1][A - 1][B - 1], dp[cur ^ 1][a1][b1][a2][b2] + 2);
			}
			else if (cnt[i] == 2) {
				int A1 = a1 - 1, A2 = a2 - 1, B1 = std::max(b1 - 1, 0), B2 = std::max(b2 - 1, 0), tmp = 0;
				if (A1 < 0) {
					A1 = A - 1; B1 = B - 1; ++tmp;
				}
				if (A2 < 0) {
					A2 = A - 1; B2 = B - 1; ++tmp;
				}
				if (A1 == 0 || B1 == 0) A1 = B1 = 0;
				if (A2 == 0 || B2 == 0) A2 = B2 = 0;
				dp[cur][A1][B1][A2][B2] = std::min(dp[cur][A1][B1][A2][B2], dp[cur ^ 1][a1][b1][a2][b2] + tmp);
				
				dp[cur][A - 1][B - 1][A2][B2] = std::min(dp[cur][A - 1][B - 1][A2][B2], dp[cur ^ 1][a1][b1][a2][b2] + 1 + tmp);
				dp[cur][A1][B1][A - 1][B - 1] = std::min(dp[cur][A1][B1][A - 1][B - 1], dp[cur ^ 1][a1][b1][a2][b2] + 1 + tmp);
				dp[cur][A - 1][B - 1][A - 1][B - 1] = std::min(dp[cur][A - 1][B - 1][A - 1][B - 1], dp[cur ^ 1][a1][b1][a2][b2] + 2);
			}
			else {
				int A1 = a1 - 1, A2 = a2, B1 = std::max(b1 - 1, 0), B2 = std::max(b2 - 1, 0), tmp = 0;
				if (A1 < 0) {
					A1 = A - 1; B1 = B - 1; ++tmp;
				}
				if (A1 == 0 || B1 == 0) A1 = B1 = 0;
				if (A2 == 0 || B2 == 0) A2 = B2 = 0;
				dp[cur][A1][B1][A2][B2] = std::min(dp[cur][A1][B1][A2][B2], dp[cur ^ 1][a1][b1][a2][b2] + tmp);
				
				dp[cur][A - 1][B - 1][A2][B2] = std::min(dp[cur][A - 1][B - 1][A2][B2], dp[cur ^ 1][a1][b1][a2][b2] + 1 + tmp);
				dp[cur][A1][B1][A - 1][B - 1] = std::min(dp[cur][A1][B1][A - 1][B - 1], dp[cur ^ 1][a1][b1][a2][b2] + 1 + tmp);
				dp[cur][A - 1][B - 1][A - 1][B - 1] = std::min(dp[cur][A - 1][B - 1][A - 1][B - 1], dp[cur ^ 1][a1][b1][a2][b2] + 2);
				
				A1 = a1, A2 = a2 - 1, B1 = std::max(b1 - 1, 0), B2 = std::max(b2 - 1, 0), tmp = 0;
				if (A2 < 0) {
					A2 = A - 1; B2 = B - 1; ++tmp;
				}
				if (A1 == 0 || B1 == 0) A1 = B1 = 0;
				if (A2 == 0 || B2 == 0) A2 = B2 = 0;
				dp[cur][A1][B1][A2][B2] = std::min(dp[cur][A1][B1][A2][B2], dp[cur ^ 1][a1][b1][a2][b2] + tmp);
				
				dp[cur][A - 1][B - 1][A2][B2] = std::min(dp[cur][A - 1][B - 1][A2][B2], dp[cur ^ 1][a1][b1][a2][b2] + 1 + tmp);
				dp[cur][A1][B1][A - 1][B - 1] = std::min(dp[cur][A1][B1][A - 1][B - 1], dp[cur ^ 1][a1][b1][a2][b2] + 1 + tmp);
				dp[cur][A - 1][B - 1][A - 1][B - 1] = std::min(dp[cur][A - 1][B - 1][A - 1][B - 1], dp[cur ^ 1][a1][b1][a2][b2] + 2);
			}
		}
		
		cur ^= 1;
	}
	cur ^= 1;
	
	int ans = 0x3f3f3f3f;
	for (int a1 = 0; a1 <= A; ++a1)
	for (int b1 = 0; b1 <= B; ++b1) if ((a1 == 0) == (b1 == 0))
	for (int a2 = 0; a2 <= A; ++a2)
	for (int b2 = 0; b2 <= B; ++b2) if ((a2 == 0) == (b2 == 0))
		ans = std::min(ans, dp[cur][a1][b1][a2][b2]);
	
	printf("%d\n", ans);
		
	return 0;
}
