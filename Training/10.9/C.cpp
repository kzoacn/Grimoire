#include <bits/stdc++.h>

typedef long long ll;

int n; double p;
int score[45], sum;

ll dp[45][40005];

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		sum = 0;
		
		scanf("%d%lf", &n, &p);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", score + i);
			sum += score[i];
		}
		
		dp[0][0] = 1;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j <= sum; ++j)
				dp[i][j] = dp[i - 1][j];
			for (int j = score[i]; j <= sum; ++j)
				dp[i][j] += dp[i - 1][j - score[i]];
		}
		
		ll tmp = 0, full = 1ll << n;
		for (int i = 0; i <= sum; ++i) {
			tmp += dp[n][i];
//			std::cerr << i << " " << tmp << '/' << full << std::endl;
			if (tmp >= p * full) {
				printf("%d\n", i);
				break;
			}
		}
	}
	
	return 0;
}
