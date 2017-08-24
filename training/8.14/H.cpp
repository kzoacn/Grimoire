#include <bits/stdc++.h>

typedef long long ll;

std::vector<int> A;

int n, m;
ll B[10005];

ll dp[10005];

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i <= m; ++i) scanf("%lld", B + i);
		
		std::vector<int>().swap(A);
		memset(dp, 0, sizeof dp);
		dp[0] = 1;
		
		for (int i = 1; i <= m; ++i) {
			int cnt = B[i] - dp[i];
			if (!cnt) continue;
			
			for (int j = 1; j <= cnt; ++j) A.push_back(i);
			
			for (int j = 1; j <= cnt; ++j)
				for (int k = m; k >= i; --k)
					dp[k] += dp[k - i];
		}
		
		for (int i = 0; i < (int)A.size(); ++i)
			printf("%d%c", A[i], " \n"[i == (int)A.size() - 1]);
	}
	
	return 0;
}
