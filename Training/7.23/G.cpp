#include <bits/stdc++.h>

#define __advance __attribute__((optimize("O3")))

typedef long long ll;

const int MAXB = 9 * 18;
const ll INF = 10000000000000001ll;

ll bit_cnt[20][180], ten[20];
ll c1 = 0, c2 = 0;

__advance ll LL(const ll &x) {
	return x >= INF ? INF : x;
}

__advance ll mul(const ll &x, const ll &y) {
	double tmp = (double)x * y;
	if (tmp >= INF) return INF;
	return LL(x * y);
}

__advance int BIT(ll x) {
	int bit = 0;
	while (x) {
		x /= 10; ++bit;
	}
	return bit;
}

__advance int BITSUM(ll x) {
	int res = 0;
	while (x) {
		res += x % 10; x /= 10;
	}
	return res;
}

__advance void init() {
	ten[0] = 1;
	for (int i = 1; i <= 18; ++i) ten[i] = ten[i - 1] * 10;
	
	bit_cnt[0][0] = 1;
	for (int i = 1; i <= 18; ++i)
		for (int j = 0; j <= 9; ++j)
			for (int s = j; s <= MAXB; ++s)
				bit_cnt[i][s] = bit_cnt[i][s] + bit_cnt[i - 1][s - j];
}

//ll g[10][20][2][180];
//ll vis[10][20][2][180], T = 0;

__advance ll DP(ll x, int bit, bool lim, int sum) {
++c1;
	if (bit == 0) return sum == 0;
	if (!lim)
		return bit_cnt[bit][sum];
	
	int this_bit = x / ten[bit - 1]; x %= ten[bit - 1];
	
//	if (vis[this_bit][bit][lim][sum] == T) return g[this_bit][bit][lim][sum];
//	vis[this_bit][bit][lim][sum] = T;
//	ll &res = g[this_bit][bit][lim][sum] = 0;
	ll res = 0;
	for (int i = 0; i < this_bit; ++i)
		res = res + DP(x, bit - 1, 0, sum - i);
	res = res + DP(x, bit - 1, 1, sum - this_bit);
	return res;
}

__advance ll DP(const ll &x, int sum) {
//	++T;
	return DP(x, BIT(x), 1, sum);
}

int n; ll k;
ll a[105], b[105]; int c[105]; // 1: <   2: <=   3: =   4: >=   5: >
ll cnt[105][180];

ll dp[105][180];
ll pre[105][180], suf[105][180];

__advance void DP2(int l, int r) {
	for (register int i = l; i <= r; ++i) {
		pre[i - 1][0] = 0;
		for (register int j = 1; j <= MAXB; ++j, ++c2) {
			pre[i - 1][j] = LL(pre[i - 1][j - 1] + dp[i - 1][j]);
			if (pre[i - 1][j] > k) {
				dp[n][1] = INF; return;
			}
		}
		suf[i - 1][MAXB + 1] = 0;
		for (register int j = MAXB; j; --j, ++c2) {
			suf[i - 1][j] = LL(suf[i - 1][j + 1] + dp[i - 1][j]);
			if (suf[i - 1][j] > k) {
				dp[n][1] = INF; return;
			}
		}
		
		for (register int j = 1; j <= MAXB; ++j, ++c2) {
			dp[i][j] = 0;
			switch (c[i - 1]) {
				case 1:
					dp[i][j] = LL(dp[i][j] + mul(pre[i - 1][j - 1], cnt[i][j]));
					break;
				case 2:
					dp[i][j] = LL(dp[i][j] + mul(pre[i - 1][j], cnt[i][j]));
					break;
				case 3:
					dp[i][j] = mul(dp[i - 1][j], cnt[i][j]);
					break;
				case 4:
					dp[i][j] = LL(dp[i][j] + mul(suf[i - 1][j], cnt[i][j]));
					break;
				case 5:
					dp[i][j] = LL(dp[i][j] + mul(suf[i - 1][j + 1], cnt[i][j]));
					break;
			}
		}
	}
}

ll ans[105];

__advance int main() {
	init();
	c[0] = 2;
	dp[0][1] = 1;
	
	ll dpn;
	
	char s[5];
	while (~scanf("%d%lld", &n, &k)) {
		for (int i = 1; i < n; ++i) {
			scanf("%lld%lld%s", a + i, b + i, s);
			if (s[0] == '<' && s[1] == '\0') c[i] = 1;
			else if (s[0] == '<' && s[1] == '=' && s[2] == '\0') c[i] = 2;
			else if (s[0] == '=' && s[1] == '\0') c[i] = 3;
			else if (s[0] == '>' && s[1] == '=' && s[2] == '\0') c[i] = 4;
			else c[i] = 5;
		}
		scanf("%lld%lld", a + n, b + n);
		
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= MAXB; ++j)
				cnt[i][j] = LL(DP(b[i], j) - DP(a[i] - 1, j));
		
		DP2(1, n);
		
		dpn = 0;
		for (int i = 1; i <= MAXB; ++i) dpn = LL(dpn + dp[n][i]);
		
		if (dpn < k) {
			puts("OUT OF RANGE");
			continue;
		}
		
		ll precnt = 0;
		for (int i = 1; i <= n; ++i) {
			ll l = a[i], r = b[i] + 1;
			while (l < r) {
				ll mid = (l + r) >> 1;
				for (int j = 1; j <= MAXB; ++j)
					cnt[i][j] = LL(DP(mid, j) - DP(l - 1, j));
				DP2(i, n);
				
				dpn = 0;
				for (int j = 1; j <= MAXB; ++j) dpn = LL(dpn + dp[n][j]);
				
//				printf("[%lld, %lld] -> %lld %lld\n", l, r, precnt, dpn);
				if (precnt + dpn < k) l = mid + 1, precnt += dpn;
				else r = mid;
			}
			ans[i] = l;
			memset(cnt[i], 0, sizeof cnt[i]);
			cnt[i][BITSUM(ans[i])] = 1;
			DP2(i, i);
			
			//std::cout << i << " " << c1 << " " << c2 << std::endl;
		}
		
		for (int i = 1; i <= n; ++i)
			printf("%lld%c", ans[i], " \n"[i == n]);
	}
	
	return 0;
}
