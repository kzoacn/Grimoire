#include <bits/stdc++.h>

typedef long long ll;
const int Mod = 105225319;

int n, good;
int dp[1005][1 << 10], LL[1005], RR[1005];
int	id[1005][1005], cnt[1005], stage[1005][10];

#define fix(x) if (x >= Mod) x -= Mod

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d", &n);
		memset(cnt, 0, sizeof(int) * (n + 1));
		for (int i = 0; i <= n; ++i)
			for (int j = 0; j <= n; ++j)
				id[i][j] = -1;
		good = 0;
		
		bool flag = 0;
		for (int i = 1; i <= n; ++i)
			scanf("%d", LL + i);
		for (int i = 1; i <= n; ++i)
			scanf("%d", RR + i);
		for (int i = 1; i <= n; ++i) {
			int L = LL[i], R = RR[i];
			if (L == 1 && R == n) {
				++good; continue;
			}
			if (flag) continue;
			for (int j = L; j <= R; ++j) {
				if (cnt[j] == 10) {
					flag = 1; break;
				}
				stage[j][cnt[j]] = i;
				id[j][i] = cnt[j];
				++cnt[j];
			}
		}
		if (flag) {
			printf("Case #%d: 0\n", kase);
			continue;
		}
		
		memset(dp, 0, sizeof(*dp) * (n + 1));
		dp[0][0] = 1;
		for (int i = 1; i <= n; ++i) {
			for (int S1 = (1 << cnt[i - 1]) - 1; S1 >= 0; --S1) {
				int S2 = 0;
				for (int j = 0; j < cnt[i]; ++j) {
					if (id[i - 1][stage[i][j]] != -1) S2 |= (1 << j) * ((S1 & (1 << id[i - 1][stage[i][j]])) != 0);
					else S2 |= (1 << j);
				}
				flag = 0;
				for (int j = 0; j < cnt[i - 1]; ++j)
					if (id[i][stage[i - 1][j]] == -1 && (S1 & (1 << j))) {
						flag = 1; break;
					}
				if (flag) continue;
				
				dp[i][S2] += dp[i - 1][S1]; fix(dp[i][S2]);
				for (int j = 0; j < cnt[i]; ++j) if (S2 & (1 << j)) {
					dp[i][S2 ^ (1 << j)] += dp[i - 1][S1]; fix(dp[i][S2 ^ (1 << j)]);
				}
			}
		}
		
		int ans = dp[n][0];
		for (int i = 2; i <= good; ++i)
			ans = (ll)ans * i % Mod;
		
		printf("Case #%d: %d\n", kase, ans);
	}
	
	return 0;
}
