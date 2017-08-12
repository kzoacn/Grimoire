#include <bits/stdc++.h>

int n, a[100005];

int sorted[100005], cnt[100005];

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		memset(cnt, 0, sizeof cnt);
		
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", a + i); sorted[i] = a[i];
		}
		
		std::sort(sorted + 1, sorted + n + 1);
		*sorted = std::unique(sorted + 1, sorted + n + 1) - sorted - 1;
		
		for (int i = 1; i <= n; ++i) {
			int t = std::lower_bound(sorted + 1, sorted + *sorted + 1, a[i]) - sorted;
			a[i] = t; ++cnt[t];
		}
		
		for (int i = 2; i <= n; ++i) {
			for (int j = i; j <= n; j += i) --cnt[a[j]];
			for (int j = *sorted; j; --j)
				if (cnt[j]) {
					printf("%d%c", sorted[j], " \n"[i == n]);
					break;
				}
			for (int j = i; j <= n; j += i) ++cnt[a[j]];
		}
	}
	
	return 0;
}
