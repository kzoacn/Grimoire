#include <bits/stdc++.h>

int n, b, c[1005], d[1005];

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d%d", &n, &b);
		for (int i = 1; i <= n; ++i) scanf("%d", c + i);
		for (int i = 1; i < n; ++i) scanf("%d", d + i);
		
		bool flag = 1;
		
		int coco = 0;
		for (int i = 1; i < n; ++i) {
			coco += c[i];
			coco -= d[i] * b;
			if (coco < 0) {
				flag = 0; break;
			}
		}
		puts(flag ? "Yes" : "No");
	}
	
	return 0;
}
