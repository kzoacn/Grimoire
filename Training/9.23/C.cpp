#include <bits/stdc++.h>

int n, m, p;

int a[305][305];

int mn[305], sum[305];

int pre[305], suf[305];
int pre_mn[305], suf_mn[305];

int Calc(int L, int R) {
	if (L > R) return -0x3f3f3f3f;
	
	memset(pre, 0, sizeof pre);
	memset(suf, 0, sizeof suf);
	memset(pre_mn, 0x1f, sizeof pre_mn);
	memset(suf_mn, 0x1f, sizeof suf_mn);

	pre_mn[L - 1] = suf_mn[R + 1] = 0;	
	
	for (int i = L; i <= R; ++i) {
		pre[i] = pre[i - 1] + sum[i];
		pre_mn[i] = std::min(pre_mn[i - 1], pre[i]);
	}
	for (int i = R; i >= L; --i) {
		suf[i] = suf[i + 1] + sum[i];
		suf_mn[i] = std::min(suf_mn[i + 1], suf[i]);
	}
	
	int tmp = -0x3f3f3f3f;
	
	for (int i = L; i <= R; ++i) {
		int t = sum[i] + std::max(p - mn[i], 0) + pre[i - 1] - pre_mn[i - 1] + suf[i + 1] - suf_mn[i + 1];
		tmp = std::max(tmp, t);
	}
	
	return tmp;
}

int main() {
	while (~scanf("%d%d%d", &n, &m, &p)) {
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				scanf("%d", a[i] + j);
		
		int ans = -0x3f3f3f3f;
		
		for (int L = 1; L <= n; ++L) {
			memset(mn, 0x1f, sizeof mn);
			memset(sum, 0, sizeof sum);
			for (int R = L; R <= n; ++R) {
				for (int i = 1; i <= m; ++i) {
					mn[i] = std::min(mn[i], a[R][i]);
					sum[i] += a[R][i];
				}
				
				if (L == 1 && R == n) {
					ans = std::max(ans, std::max(Calc(1, m - 1), Calc(2, m)));
					
					int Mn = 0x3f3f3f3f, Sum = 0;
					for (int i = 1; i <= m; ++i) {
						Mn = std::min(Mn, mn[i]);
						Sum += sum[i];
						ans = std::max(ans, Sum + p - Mn);
						continue;
					}
					
					continue;
				}
				
				ans = std::max(ans, Calc(1, m));
			}
		}
		
		printf("%d\n", ans);
	}
	
	return 0;
}
