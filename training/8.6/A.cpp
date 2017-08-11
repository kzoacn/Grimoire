#include <bits/stdc++.h>

int a[4], b[4];

bool check(int t) {
	for (int i = 0; i < 4; ++i)
		if (a[i] != b[(i + t) % 4]) return 0;
	return 1;
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d%d%d%d", a + 0, a + 1, a + 3, a + 2);
		scanf("%d%d%d%d", b + 0, b + 1, b + 3, b + 2);
		
		bool flag = 0;
		
		for (int t = 0; t < 4; ++t) {
			if (check(t)) {
				flag = 1; break;
			}
		}
		
		printf("Case #%d: ", kase);
		if (flag) puts("POSSIBLE");
		else puts("IMPOSSIBLE");
	}
	
	return 0;
}
