#include <bits/stdc++.h>

int n, m;
char s[1005];

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d%d%s", &n, &m, s + 1);
		for (int i = 1; i <= n * m; ++i) {
			putchar(s[i]);
			if (i % m == 0) putchar('\n');
		}
	}
	
	return 0;
}
