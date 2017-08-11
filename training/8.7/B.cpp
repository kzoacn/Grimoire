#include <bits/stdc++.h>

typedef long long ll;

int n, m;
char S[50005], T[105];

ll pre[50005][105], suf[50005][105];

ll pre2[50005], suf2[50005];

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		int q;
		scanf("%d%d%d%s%s", &n, &m, &q, S + 1, T + 1);
		
		for (int i = 1; i <= m; ++i) pre[0][i] = suf[n + 1][i] = 0;
		pre[0][0] = suf[n + 1][m + 1] = 1;
		
		for (int i = 1; i <= n; ++i) {
			pre[i][0] = 1;
			for (int j = 1; j <= m; ++j)
				pre[i][j] = (T[j] == S[i] ? pre[i - 1][j - 1] : 0);
		}
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				pre[i][j] += pre[i - 1][j];
		
		for (int i = n; i; --i) {
			suf[i][m + 1] = 1;
			for (int j = m; j; --j)
				suf[i][j] = (T[j] == S[i] ? suf[i + 1][j + 1] : 0);
		}
		for (int i = n; i; --i)
			for (int j = m; j; --j)
				suf[i][j] += suf[i + 1][j];
		
		pre2[0] = 0;
		for (int i = 1; i <= n; ++i) pre2[i] = pre2[i - 1] + pre[i][m];
		
		suf2[m + 1] = 0;
		for (int i = n; i; --i) suf2[i] = suf2[i + 1] + suf[i][1];
		
		int L, R;
		while (q--) {
			scanf("%d%d", &L, &R);
			
			ll ans = pre2[L] * (n - R + 1) + suf2[R] * L;
			for (int i = 1; i < m; ++i)
				ans += pre[L][i] * suf[R][i + 1];
			
			printf("%lld\n", ans);
		}
	}
	
	return 0;
}
