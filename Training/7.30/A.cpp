#include <bits/stdc++.h>

int n, x, y;

char s1[80005], s2[80005];

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d%d%d%s%s", &n, &x, &y, s1, s2);
		int m = 0;
		for (int i = 0; i < n; ++i)
			if (s1[i] != s2[i]) ++m;
		
		int i = std::min(n - m, std::min(x, y));
		if (x + y - i - i <= m) puts("Not lying");
		else puts("Lying");
	}
	
	return 0;
}
