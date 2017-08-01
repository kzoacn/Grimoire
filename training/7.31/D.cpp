#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;

int B, I, D, C;

char s[3005], t[3005]; int ls, lt;

int dp[3005][3005], mindp[3005], mindp_i[3005];
int from_i[3005][3005], from_j[3005][3005]; char from_tp[3005][3005];

std::vector<int> dex, dey;
std::vector<char> opt;

void get_ans() {
	int x = ls, y = lt, xx, yy;
	
	while (x || y) {
		if (from_tp[x][y] == 'B') {
			dex.push_back(from_i[x][y] + 1);
			dey.push_back(x);
		}
		else opt.push_back(from_tp[x][y]);
		xx = from_i[x][y];
		yy = from_j[x][y];
		x = xx; y = yy;
	}
}

int main() {
	scanf("%d%d%d%d%s%s", &B, &I, &D, &C, s + 1, t + 1);
	ls = strlen(s + 1); lt = strlen(t + 1);
	
	memset(dp, 0x3f, sizeof dp);
	dp[0][0] = 0;
	
	mindp[0] = 0;
	mindp_i[0] = 0;
	for (int j = 1; j <= lt; ++j) {
		mindp[j] = INF;
		mindp_i[j] = 0;
	}
	
	for (int i = 0; i <= ls; ++i)
		for (int j = 0; j <= lt; ++j) {
			if (mindp[j] + B < dp[i][j]) {
				dp[i][j] = mindp[j] + B;
				from_i[i][j] = mindp_i[j];
				from_j[i][j] = j;
				from_tp[i][j] = 'B';
			}
			if (dp[i][j] + D < dp[i + 1][j]) {
				dp[i + 1][j] = dp[i][j] + D;
				from_i[i + 1][j] = i;
				from_j[i + 1][j] = j;
				from_tp[i + 1][j] = 'D';
			}
			if (dp[i][j] + I < dp[i][j + 1]) {
				dp[i][j + 1] = dp[i][j] + I;
				from_i[i][j + 1] = i;
				from_j[i][j + 1] = j;
				from_tp[i][j + 1] = 'I';
			}
			if (i < ls && j < lt && s[i + 1] == t[j + 1] && dp[i][j] + C < dp[i + 1][j + 1]) {
				dp[i + 1][j + 1] = dp[i][j] + C;
				from_i[i + 1][j + 1] = i;
				from_j[i + 1][j + 1] = j;
				from_tp[i + 1][j + 1] = 'C';
			}
			if (dp[i][j] < mindp[j]) {
				mindp[j] = dp[i][j];
				mindp_i[j] = i;
			}
		}
	
	get_ans();
	printf("%d\n", dp[ls][lt]);
	printf("%d\n", (int)dex.size());
	for (int i = 0; i < (int)dex.size(); ++i)
		printf("%d %d\n", dex[i], dey[i]);
	for (int i = (int)opt.size() - 1; i >= 0; --i)
		putchar(opt[i]);
	putchar('\n');
	
	return 0;
}
