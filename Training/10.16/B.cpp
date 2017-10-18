#include <bits/stdc++.h>

#define __advance __attribute__((optimize("O3")))

const int Mod = 1e9 + 7;

int n;

char s[55][25]; int ends[55];

int dp[55][55][55][26];
bool vis[55][55][55][26];

//int COUNT = 0;

bool same[55][55][25][26];

__advance int DP(int l, int r, int k, int low_c) {
	if (l > r) return 1;
	if (low_c >= 26) return 0;
	
	if (vis[l][r][k][low_c]) return dp[l][r][k][low_c];
	vis[l][r][k][low_c] = 1;
	int &res = dp[l][r][k][low_c] = 0;
	
	if (k >= ends[l]) {
		if (l == r) return res = 1;
		if (k >= ends[l + 1]) return 0;
		return res = DP(l + 1, r, k, low_c);
	}
	
	for (register int i = l; i <= r; ++i)
		if (k >= ends[i] || (s[i][k] != '?' && s[i][k] - 'a' < low_c)) return 0;
	
	for (register int mid = l; mid <= r; ++mid) {
		for (register int c = low_c; c < 26; ++c) {
			/*for (register int i = l; i <= mid; ++i) {
				++COUNT;
				if (s[i][k] - 'a' != c && s[i][k] != '?')
					goto ENDS;
			}*/
			if (!same[l][mid][k][c]) continue;
//			++COUNT;
			
			res = (res + 1ll * DP(l, mid, k + 1, 0) * DP(mid + 1, r, k, c + 1)) % Mod;
		}
	}
	
	return res;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", s[i]); ends[i] = strlen(s[i]);
	}
	
	for (int k = 0; k < 20; ++k) {
		for (int c = 0; c < 26; ++c)
			for (int i = 1; i <= n; ++i) {
				if (s[i][k] - 'a' != c && s[i][k] != '?') continue;
				same[i][i][k][c] = 1;
				for (int j = i + 1; j <= n; ++j) {
					if (s[j][k] - 'a' != c && s[j][k] != '?') break;
					same[i][j][k][c] = 1;
				}
			}
	}
	
	printf("%d\n", DP(1, n, 0, 0));
	
//	std::cerr << COUNT << std::endl;
	
	return 0;
}
