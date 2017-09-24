#include <bits/stdc++.h>

int n, m;

int p[105];
bool tc[105];

int main() {
	while (~scanf("%d%d", &n, &m)) {
		memset(tc, 0, sizeof tc);
		
		for (int i = 1; i <= n; ++i) scanf("%d", p + i);
		int q; scanf("%d", &q);
		for (int x; q--; ) {
			scanf("%d", &x); ++x;
			tc[x] = 1;
		}
		
		p[0] = 0x3f3f3f3f;
		int x = 0, y = 0;
		
		int cnt = 0;
		for (int L = 1, R = 1; L <= n; ++L) {
			while (R <= n && cnt < m) {
				if (!tc[R]) ++cnt;
				++R;
			}
			
			if (cnt < m) break;
			
			if (tc[L]) continue;
			
			int mn = 0;
			
			for (int i = L + 1; i < R; ++i) {
				if (tc[i]) continue;
				if (p[i] < p[mn]) {
					mn = i;
				}
			}
			
			if (p[mn] + p[L] < p[x] + p[y]) {
				x = L; y = mn;
			}
			
			if (!tc[L])
				--cnt;
		}
		
		if (x > y) std::swap(x, y);
		--x; --y;
		
		printf("%d %d\n", x, y);
	} 
	
	return 0;
}
