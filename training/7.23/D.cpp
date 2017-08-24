#include <bits/stdc++.h>

typedef long long ll;

char s[25]; int n;

ll dp[25][25];

int main() {
	while (~scanf("%s", s + 1)) {
		n = strlen(s + 1);
		
		if (s[1] == '-') {
			puts("0");
			continue;
		}
		
		memset(dp, 0, sizeof dp);
		dp[1][1] = 1;
		
		int plus = 1;
		
		for (int i = 2; i <= n; ++i) {
			plus += (s[i] == '+');
			for (int j = 1; j <= plus; ++j) {
				if (s[i] == '+') {
					dp[i][j] += dp[i - 1][j] * j;
					dp[i][j + 1] += dp[i - 1][j] * (plus - j);
				}
				else {
					dp[i][j - 1] += dp[i - 1][j] * j;
					dp[i][j] += dp[i - 1][j] * (plus - j);
				}
			}
			if (s[i] == '+') dp[i][1] += dp[i - 1][0] * plus;
			else dp[i][0] += dp[i - 1][0] * plus;
		}
		
		std::cout << dp[n][0] << '\n';
	}
	
	return 0;
}
