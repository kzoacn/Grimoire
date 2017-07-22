#include <bits/stdc++.h>

typedef std::pair<int, bool> pib;
#define mp std::make_pair

char ss[505]; int n;
int fail[505][505];

void get_fail(int idx, char *s, int len) {
	fail[idx][0] = fail[idx][1] = 0;
	for (int i = 1; i <= len; ++i) {
		int j = fail[idx][i];
		while (j && s[j + 1] != s[i + 1]) j = fail[idx][j];
		fail[idx][i + 1] = j + (s[j + 1] == s[i + 1]);
	}
}

int BIT(int x) {
	int bit = 0;
	while (x) {
		x /= 10; ++bit;
	}
	return bit;
}

int kase = 0, vis[505][505];
pib dp[505][505];

pib tmp;
#define len (r - l + 1)
#define cc (r - l + 1 - fail[l][r - l + 1])

pib DP(int l, int r) {
	if (l == r) return mp(1, 0);
	if (vis[l][r] == kase) return dp[l][r];
	vis[l][r] = kase;
	pib &ans = dp[l][r] = mp(0x3f3f3f3f, 1);
	if (len % cc == 0) {
		tmp = DP(l, l + cc - 1);
		ans = mp(BIT(len / cc) + tmp.first + (tmp.second ? 2 : 0), (bool)1);
	}
	for (int mid = l; mid < r; ++mid)
		ans = std::min(ans, mp(DP(l, mid).first + DP(mid + 1, r).first, (bool)1));
	return ans;
}

int main() {
	while (~scanf("%s", ss + 1) && ss[1] != '0') {
		++kase;
		n = strlen(ss + 1);
		
		for (int i = 1; i <= n; ++i)
			get_fail(i, ss + i - 1, n - i + 1);
		
		printf("Case %d: %d\n", kase, DP(1, n).first);
	}
	
	return 0;
}
