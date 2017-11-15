#include <bits/stdc++.h>

const int MAXN = 5e3 + 5;

int n, a[MAXN], lis[MAXN], f[MAXN];

std::bitset<MAXN> pre[MAXN], tmp;

int main() {
	while (~scanf("%d", &n)) {
		tmp.reset();
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i);
			
			pre[i].reset();
			lis[i] = 1;
			for (int j = 1; j < i; ++j) if (a[j] < a[i])
				lis[i] = std::max(lis[i], lis[j] + 1);
			for (int j = 1; j < i; ++j) if (a[j] < a[i] && lis[i] == lis[j] + 1)
				pre[i][j] = 1;
		}
		
		for (int del = 1; del <= n; ++del) {
			tmp.reset();
			tmp[del] = 1;
			
			int ans = 0;
			
			for (int i = 1; i <= n; ++i) if (i != del) {
				if (pre[i].count() && (pre[i] & tmp).count() == pre[i].count()) {
					tmp[i] = 1;
					f[i] = lis[i] - 1;
				}
				else f[i] = lis[i];
				
				ans ^= f[i] * f[i];
			}
			
			printf("%d%c", ans, " \n"[del == n]);
		}
	}
	
	return 0;
}
