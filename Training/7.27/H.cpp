#include <bits/stdc++.h>

const int Mod = 21092013;

char str[100005]; int len;

int s[100005], ls;
int t[100005], lt;

int dp[100005][2];

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%s", str + 1); len = strlen(str + 1);
		
		ls = 0;
		for (int i = 1; i <= len; ++i) {
			switch (str[i]) {
				case 'L': s[++ls] = 0; break;
				case 'R': s[++ls] = 1; break;
				case 'U': if (ls) --ls; break;
			}			
		}
		
		scanf("%s", str + 1); len = strlen(str + 1);
		lt = len;
		for (int i = 1; i <= len; ++i) {
			switch (str[i]) {
				case 'L': t[i] = 0; break;
				case 'R': t[i] = 1; break;
				case 'U': t[i] = -1; break;
			}
		}
		
		dp[lt + 1][0] = dp[lt + 1][1] = 0;
		for (int i = lt; i; --i) {
			if (t[i] == 0) {
				dp[i][0] = (dp[i + 1][0] + dp[i + 1][1] + 1) % Mod;
				dp[i][1] = dp[i + 1][1];
			}
			else if (t[i] == 1) {
				dp[i][0] = dp[i + 1][0];
				dp[i][1] = (dp[i + 1][0] + dp[i + 1][1] + 1) % Mod;
			}
			else {
				dp[i][0] = dp[i + 1][0];
				dp[i][1] = dp[i + 1][1];
			}
		}
		
		int ans = (dp[1][0] + dp[1][1] + 1) % Mod;
		
		int u_cnt = 0;
		for (int i = 1; i <= lt; ++i) {
			if (t[i] != -1) continue;
			++u_cnt;
			if (u_cnt > ls) break;
			if (s[ls - u_cnt + 1] == 0) ans = (ans + dp[i + 1][1] + 1) % Mod;
			else ans = (ans + dp[i + 1][0] + 1) % Mod;
		}
		
		printf("Case %d: %d\n", kase, ans);
	}
	
	return 0;
}
