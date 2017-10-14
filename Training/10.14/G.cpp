#include <bits/stdc++.h>

int a[105][105];
/*
bool edge[1005][1005];

void AddEdge(int u, int v) {
	assert(!edge[u][v]);
	edge[u][v] = edge[v][u] = 1;
}
*/
int main() {
	int k; scanf("%d", &k);
	
	int tot = 0;
	for (int i = 0; i < k; ++i)
		for (int j = 0; j < k; ++j)
			a[i][j] = ++tot;
	
	printf("%d\n", k * k);
	if (k == 2) {
		puts("1 2\n1 3\n3 4\n4 1\n2 3\n2 4");
		return 0;
	}
	for (int i = 0; i < k; ++i) {
		for (int j = 1; j < k; ++j) {
			printf("%d %d\n", a[i][j - 1], a[i][j]);
//			AddEdge(a[i][j - 1], a[i][j]);
		}
		for (int j = 0; j < k; ++j)
			for (int t = 0; t < k; ++t) if (t != i) {
				printf("%d %d\n", a[i][j], a[t][(j + 1) % k]);
//				AddEdge(a[i][j], a[t][(j + 1) % k]);
			}
	}
	
	return 0;
}
