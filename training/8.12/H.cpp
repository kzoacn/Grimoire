#include <bits/stdc++.h>

int n, m;
char s[5005];

int calc(int l, int r) {
	int res = 0, len = 0, tmp = 0;
	
	for (int i = l, j = r; l >= 1 && r <= n; --l, ++r) {
		tmp += std::abs(s[l] - s[r]); ++len;
		while (l <= i && tmp > m) {
			--len;
			tmp -= std::abs(s[i] - s[j]);
			--i, ++j;
		}
		if (tmp > m) continue;
		res = std::max(res, len);
	}
	return res;
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d%s", &m, s + 1); n = strlen(s + 1);
		
		int ans = 0;
		for (int i = 1; i <= n; ++i) ans = std::max(ans, calc(i - 1, i + 1));
		for (int i = 1; i < n; ++i) ans = std::max(ans, calc(i, i + 1));
		
		printf("%d\n", ans);
	}
	
	return 0;
}
