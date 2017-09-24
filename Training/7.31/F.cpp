#include <bits/stdc++.h>

const int INF = 1e7;

char s[100005]; int len;

int dp[100005][4];

int stk[100005], top;

bool vis[100005];

int main() {
	scanf("%s", s + 1); len = strlen(s + 1);
	
	top = 0;
	for (int i = 1; i <= len; ++i) {
		dp[i][0b00] = 0;
		dp[i][0b01] = dp[i][0b10] = 1;
		dp[i][0b11] = -INF;
		stk[++top] = i;
		if (s[i] == 'g') {
			vis[i] = 1;
		}
		while (top >= 3 && vis[stk[top]] && vis[stk[top - 1]]) {
			int x = stk[top - 2], y = stk[top - 1], z = stk[top];
			if (s[x] == 'S') {
				dp[x][0b00] = std::max(std::max(dp[y][0b01] + dp[z][0b10] - 1, dp[y][0b00] + dp[z][0b00]), dp[x][0b00]);
				dp[x][0b01] = std::max(std::max(dp[y][0b01] + dp[z][0b11] - 1, dp[y][0b00] + dp[z][0b01]), dp[x][0b01]);
				dp[x][0b10] = std::max(std::max(dp[y][0b11] + dp[z][0b10] - 1, dp[y][0b10] + dp[z][0b00]), dp[x][0b10]);
				dp[x][0b11] = std::max(std::max(dp[y][0b11] + dp[z][0b11] - 1, dp[y][0b10] + dp[z][0b01]), dp[x][0b11]);
			}
			else {
				dp[x][0b00] = std::max(dp[y][0b00] + dp[z][0b00], dp[x][0b00]);
				dp[x][0b01] = std::max(dp[y][0b01] + dp[z][0b01] - 1, dp[x][0b01]);
				dp[x][0b10] = std::max(dp[y][0b10] + dp[z][0b10] - 1, dp[x][0b10]);
				dp[x][0b11] = std::max(dp[y][0b11] + dp[z][0b11] - 2, dp[x][0b11]);
			}
			vis[x] = 1;
			top -= 2;
		}
	}
	
	int ans = 1;
	for (int i = 0b00; i <= 0b11; ++i)
		ans = std::max(ans, dp[1][i]);
	printf("%d\n", ans);
	
	return 0;
}
