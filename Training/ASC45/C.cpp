#include <bits/stdc++.h>

#define debugPrint(x) std::cerr << #x << " = " << x << std::endl;

typedef long long LL;

const int Lim = 32;

LL dp[33][33][33];
LL presum[33][33][33];

LL C[65][65];

void pretreatment() {
	for (int i = 0; i <= Lim * 2; ++i) {
		C[i][0] = C[i][i] = 1;
		for (int j = 1; j < i; ++j)
			C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
	}
	
	for (int up = 0; up <= Lim; ++up) {
		dp[1][up][0] = 1;
		presum[1][up][0] = up + 1;
	}
	
	for (int L = 2; L <= Lim; ++L) {
		dp[L][0][0] = 1;
		for (int up = 1; up <= Lim; ++up) {
			dp[L][up][0] = C[up + L - 1][L - 1];
			for (int A = 1; A <= Lim; ++A) {
				for (int i = 1; i <= ((L + 1) >> 1); ++i) {
					for (int j = 0; j <= up - 1; ++j) {
						for (int A_ = up - 1; A_ <= A - 1; ++A_) {
							dp[L][up][A] += dp[i - 1][j][A_] * presum[L - i][up - j][A - 1 - A_];
						}
					}
				}
			}
		}
		for (int A = 0; A <= Lim; ++A) {
			presum[L][0][A] = dp[L][0][A];
			for (int up = 1; up <= Lim; ++up)
				presum[L][up][A] = presum[L][up - 1][A] + dp[L][up][A];
		}
	}
	
#ifdef LOCAL
	for (int L = 1; L <= 4; ++L)
		for (int up = 0; up <= 4; ++up)
			for (int A = 0; A <= 4; ++A)
				printf("dp[%d][%d][%d] = %lld\n", L, up, A, dp[L][up][A]);
#endif
}

int main() {
	pretreatment();
	
	int n;
	for (int kase = 1; ~scanf("%d", &n) && n; ++kase) {
		
		LL ans = 0;
		for (int up = 0; up <= n - 1; ++up)
			for (int A = up; A <= n - 1; ++A)
				ans += dp[n][up][A];
		printf("Case #%d: %lld\n", kase, ans);
	}
	
	return 0;
}
