#include <bits/stdc++.h>

const int INF = 0x1f1f1f1f;

int node[205], tot;

char s[205]; int len;

int f[205][205], g[205][205];

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		memset(node, 0, sizeof node);
		tot = 0;
		
		scanf("%s", s + 1); len = strlen(s + 1);
		int tmp = 1;
		for (int i = 2; i <= len; ++i) {
			if (s[i] != s[i - 1]) {
				node[++tot] = tmp;
				tmp = 1;
			}
			else ++tmp;
		}
		node[++tot] = tmp;
		
		for (int i = 1; i <= tot; ++i)
			f[i][i] = 3 - node[i];
		for (int L = 2; L <= tot; ++L) {
			for (int l = 1; l + L - 1 <= tot; ++l) {
				int r = l + L - 1;
				
				f[l][r] = INF;
				
				for (int mid = l; mid < r; ++mid)
					f[l][r] = std::min(f[l][r], f[l][mid] + f[mid + 1][r]);
				if ((r - l + 1) & 1) {
					
					g[l][r] = INF;
					
					f[l][r] = std::min(f[l][r], f[l + 1][r - 1] + std::max(3 - node[l] - node[r], 0));
					for (int mid = l + 2; mid < r; mid += 2) {
						if (node[mid] + node[l] >= 3 && node[mid] + node[r] >= 3) continue;
						f[l][r] = std::min(f[l][r], f[l + 1][mid - 1] + f[mid + 1][r - 1]);
						if (node[l] == 1 && node[mid] == 1 && node[r] == 1) {
							g[l][r] = std::min(g[l][r], f[l + 1][mid - 1] + f[mid + 1][r - 1]);
							f[l][r] = std::min(f[l][r], std::min(g[l][mid] + f[mid + 1][r - 1], f[l + 1][mid - 1] + g[mid][r]));
						}
					}
				}
			}
		}
		
		printf("Case #%d: %d\n", kase, f[1][tot]);
	}
	
	return 0;
}
