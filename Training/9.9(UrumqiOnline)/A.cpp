#include <bits/stdc++.h>

int n, m;
bool e1[55][55], e2[55][55];

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		memset(e1, 0, sizeof e1);
		memset(e2, 0, sizeof e2);
		
		scanf("%d%d", &n, &m);
		for (int u, v, i = 1; i <= n; ++i) {
			scanf("%d%d", &u, &v);
			e1[u][v] = 1;
		}
		for (int u, v, i = 1; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			e2[u][v] = 1;
		}
		
		for (int i = 1; i <= 50; ++i)
			for (int j = 1; j <= 50; ++j) {
				bool flag = 0;
				for (int k = 1; k <= 50; ++k)
					if (e1[i][k] && e2[k][j]) {
						flag = 1; break;
					}
				if (flag) printf("%d %d\n", i, j);
			}
		if (kase != caseCnt) putchar('\n');
	}
	
	return 0;
}
