#include <bits/stdc++.h>

int m, n, col[105];
int st, dr;

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d%d", &m, &n);
		for (int i = 1; i <= m; ++i) {
			scanf("%d", col + i);
			if (col[i] == 2) {
				st = i; dr = 1;
			}
			else if (col[i] == 3) {
				st = i; dr = -1;
			}
		}
		
		int ans = 0;
		while (n--) {
			if (st + dr < 1 || st + dr > m) dr = -dr;
			st += dr;
			if (col[st] == 0) ++ans;
		}
		
		printf("%d\n", ans);
	}
	
	return 0;
}
