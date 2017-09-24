#include <bits/stdc++.h>

int *uu[1000005], *dd[1000005], *cnt_v[1000005];

int n, m, k;

void NEW(int **X) {
	for (int i = 0; i < n + 5; ++i) {
		X[i] = new int [m + 5];
		memset(X[i], 0, sizeof(int) * (m + 5));
	}
}

void DEL(int **X) {
	for (int i = 0; i < n + 5; ++i)
		delete X[i];
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d%d%d", &n, &m, &k);
		
		NEW(uu); NEW(dd); NEW(cnt_v);
		
		char dr[2]; int step;
		
		int x = 0, y = 0;
		while (k--) {
			scanf("%s%d", dr, &step);
			switch (*dr) {
				case 'U':
					++uu[x][y + 1];
					x -= step;
					--uu[x][y + 1];
					break;
				case 'D':
					++dd[x + 1][y + 1];
					x += step;
					--dd[x + 1][y + 1];
					break;
				case 'L':
					y -= step;
					break;
				case 'R':
					y += step;
					break;
			}
			
//			std::cerr << x << " " << y << std::endl;
		}
		
		for (int j = 1; j <= m + 1; ++j) {
			int tmp = 0;
			for (int i = 1; i <= n; ++i) {
				tmp += dd[i][j];
				cnt_v[i][j] += tmp;
			}
			tmp = 0;
			for (int i = n; i; --i) {
				tmp += uu[i][j];
				cnt_v[i][j] -= tmp;
			}
		}
		
		/*for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m + 1; ++j)
				fprintf(stderr, "%d%c", uu[i][j], " \n"[j == m + 1]);
		fprintf(stderr, "--------\n");
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m + 1; ++j)
				fprintf(stderr, "%d%c", dd[i][j], " \n"[j == m + 1]);*/
		
		long long ans = 0;
		
		for (int i = 1; i <= n; ++i) {
			int tmp = 0;
			for (int j = 1; j <= m; ++j) {
				tmp += cnt_v[i][j];
				ans += tmp * tmp;
			}
		}
		
		printf("Case #%d: %lld\n", kase, ans);
		
		DEL(uu); DEL(dd); DEL(cnt_v);
	}
	
	return 0;
}
