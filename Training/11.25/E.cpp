#include <bits/stdc++.h>

typedef unsigned long long ULL;

ULL dp[75][10][2];

void pretreatment() {
	for (int j = 0; j <= 9; ++j)
		dp[1][j][0] = 1;
	for (int i = 2; i <= 70; ++i)
		for (int j = 0; j <= 9; ++j) {
			for (int k = 0; k <= j; ++k)
				dp[i][j][0] += dp[i - 1][k][0];
			for (int k = 9; k > j; --k)
				dp[i][j][1] += dp[i - 1][k][0];
			for (int k = 9; k >= j; --k)
				dp[i][j][1] += dp[i - 1][k][1];
		}
}

int n, bit[75];

ULL Solve() {
	ULL ans = 0;
	
	bool top = 0;
	int last = 0;
	for (int i = 1; i <= n; ++i) {
		if (!top) {
			for (int x = 0; x < last && x < bit[i]; ++x)
				ans += dp[n - i + 1][x][0];
			for (int x = last; x < bit[i]; ++x)
				ans += dp[n - i + 1][x][0] + dp[n - i + 1][x][1];
		}
		else {
			for (int x = 0; x <= last && x < bit[i]; ++x)
				ans += dp[n - i + 1][x][0];
		}
		
		if (i > 1 && bit[i] < bit[i - 1])
			top = 1;
		last = bit[i];
	}
	
	return ans;
}

int main() {
	pretreatment();
	
	int caseCnt; scanf("%d", &caseCnt);
	while (caseCnt--) {
		static char s[75];
		
		scanf("%s", s + 1); n = strlen(s + 1);
		for (int i = 1; i <= n; ++i)
			bit[i] = s[i] - '0';
		
		bool top = 0, flag = 0;
		for (int i = 2; i <= n; ++i) {
			if (bit[i] > bit[i - 1] && top) {
				flag = 1; break;
			}
			if (bit[i] < bit[i - 1])
				top = 1;
		}
		if (flag) {
			puts("-1");
			continue;
		}
		printf("%llu\n", Solve());
	}
	
	return 0;
}
