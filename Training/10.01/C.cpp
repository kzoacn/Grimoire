#include <bits/stdc++.h>

#define Cnt __builtin_popcount

const int Null = 0x80808080;

int R, C;

char s[135][20]; int len[135];

int dp[2][1 << 16];

int full[17];

int main() {
	for (int i = 1; i <= 16; ++i)
		full[i] = (1 << i) - 1;
		
	scanf("%d%d", &R, &C);
	for (int i = 1; i <= R; ++i) {
		scanf("%s", s[i]);
		len[i] = strlen(s[i]);
	}
	
	memset(dp[0], 0x80, sizeof dp[0]);
	dp[0][0] = 0;
	
	int cur = 1;
	for (int i = 1; i <= R; ++i) {
		memset(dp[cur], 0x80, sizeof dp[cur]);
		for (int S = 0; S <= full[C]; ++S) {
			if (dp[cur ^ 1][S] == Null || Cnt(S) != len[i - 1]) continue;
			
			if (S & 1) dp[cur][S | 1] = std::max(dp[cur][S | 1], dp[cur ^ 1][S] + (s[i][0] == s[i - 1][0]) * 2);
			else dp[cur][S | 1] = std::max(dp[cur][S | 1], dp[cur ^ 1][S]);
			dp[cur][S & (full[C] ^ 1)] = std::max(dp[cur][S & (full[C] ^ 1)], dp[cur ^ 1][S]);
		}
		cur ^= 1;
		for (int j = 1; j < C; ++j) {
			memset(dp[cur], 0x80, sizeof dp[cur]);
			for (int S = 0; S <= full[C]; ++S) {
				if (dp[cur ^ 1][S] == Null) continue;
				
				int i_this = Cnt(S & full[j]), 
					i_last = len[i - 1] - Cnt(S & (full[C] ^ full[j]));
				
				if (i_this > len[i]/* || i_last < 0 || i_last > j*/) continue;
				
				dp[cur][S & (full[C] ^ (1 << j))] = std::max(dp[cur][S & (full[C] ^ (1 << j))], dp[cur ^ 1][S]);
				
				if (i_this >= len[i]) continue;
				
				if (S & (1 << j)) {
					int tmp = dp[cur ^ 1][S] + (s[i - 1][i_last] == s[i][i_this]) * 2;
					if (i_this != 0 && (S & (1 << (j - 1)))) tmp += (s[i][i_this] == s[i][i_this - 1]) * 2;
					dp[cur][S | (1 << j)] = std::max(dp[cur][S | (1 << j)], tmp);
				}
				else {
					int tmp = dp[cur ^ 1][S];
					if (i_this != 0 && (S & (1 << (j - 1)))) tmp += (s[i][i_this] == s[i][i_this - 1]) * 2;
					dp[cur][S | (1 << j)] = std::max(dp[cur][S | (1 << j)], tmp);
				}
			}
			cur ^= 1;
		}
	}
	
	int ans = 0;
	for (int S = 0; S <= full[C]; ++S)
		if (Cnt(S) == len[R]) ans = std::max(ans, dp[cur ^ 1][S]);
	
	printf("%d\n", ans);
	
	return 0;
}
