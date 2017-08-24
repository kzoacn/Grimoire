#include <bits/stdc++.h>

#define __advance __attribute__((optimize("O3")))

const int Mod = 1e9 + 7;

int h, w, m, n;

__advance int qpow(int a, int x) {
	int res = 1;
	for (; x; x >>= 1) {
		if (x & 1) res = 1ll * res * a % Mod;
		a = 1ll * a * a % Mod;
	}
	return res;
}

int sorted_x[25], sorted_y[25], cntx, cnty;

struct Matrix {
	int x1, x2, y1, y2, v;
	
	__advance bool operator < (const Matrix &rhs) const {
		return v < rhs.v;
	}
	
	__advance void scan() {
		scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &v);
		--x1; --y1;
	}
} mat[10], sorted[10];

__advance void hash_x(int &x) {
	x = std::lower_bound(sorted_x + 1, sorted_x + cntx + 1, x) - sorted_x;
}

__advance void hash_y(int &y) {
	y = std::lower_bound(sorted_y + 1, sorted_y + cnty + 1, y) - sorted_y;
}

int cnt[25][25];
bool c[25][25];

__advance int Find(int *fa, int x) {
	return fa[x] == x ? x : fa[x] = Find(fa, fa[x]);
}

int fa_x[25][25];

__advance int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (register int kase = 1; kase <= caseCnt; ++kase) {
		cntx = cnty = 0;
		
		scanf("%d%d%d%d", &h, &w, &m, &n);
		
		sorted_x[++cntx] = 0;
		sorted_y[++cnty] = 0;
		sorted_x[++cntx] = h;
		sorted_y[++cnty] = w;
		
		for (register int i = 0; i < n; ++i) {
			mat[i].scan();
			sorted_x[++cntx] = mat[i].x1;
			sorted_x[++cntx] = mat[i].x2;
			sorted_y[++cnty] = mat[i].y1;
			sorted_y[++cnty] = mat[i].y2;
		}
		
		std::sort(sorted_x + 1, sorted_x + cntx + 1);
		cntx = std::unique(sorted_x + 1, sorted_x + cntx + 1) - sorted_x - 1;
		std::sort(sorted_y + 1, sorted_y + cnty + 1);
		cnty = std::unique(sorted_y + 1, sorted_y + cnty + 1) - sorted_y - 1;
		
		for (int x = 2; x <= cntx; ++x)
			for (int y = 2; y <= cnty; ++y)
				cnt[x][y] = (sorted_x[x] - sorted_x[x - 1]) * (sorted_y[y] - sorted_y[y - 1]);
		
		for (register int i = 0; i < n; ++i) {
			hash_x(mat[i].x1);
			hash_x(mat[i].x2);
			hash_y(mat[i].y1);
			hash_y(mat[i].y2);
		}
		
		int ans = 0;
		
		for (register int S = 0; S < (1 << n); ++S) {
			int tp = 1;
			for (int i = 0; i < n; ++i) {
				sorted[i] = mat[i];
				if (S & (1 << i)) {
					tp = -tp;
					--sorted[i].v;
				}
			}
			
			memset(c, 0, sizeof c);
			std::sort(sorted, sorted + n);
			for (register int i = 2; i <= cntx; ++i)
				for (register int j = 2; j <= cnty + 1; ++j)
					fa_x[i][j] = j;
			
			int tmp = 1, sum, left = h * w;
			
			for (register int i = 0; i < n; ++i) {
				sum = 0;
				for (register int x = sorted[i].x1 + 1; x <= sorted[i].x2; ++x)
					for (register int y = Find(fa_x[x], sorted[i].y1 + 1); y <= sorted[i].y2; y = Find(fa_x[x], y + 1)) {
//						if (c[x][y]) continue;
						c[x][y] = 1;
						fa_x[x][y] = Find(fa_x[x], y + 1);
//						tmp = (1ll * tmp * qpow(sorted[i].v, cnt[x][y])) % Mod;
						sum += cnt[x][y];
					}
				tmp = (1ll * tmp * qpow(sorted[i].v, sum)) % Mod;
				left -= sum;
			}
			
			tmp = (1ll * tmp * qpow(m, left)) % Mod;
			
//			fprintf(stderr, "%d\n", tmp);
			
			ans = (1ll * ans + tmp * tp + Mod) % Mod;
		}
		
		printf("Case #%d: %d\n", kase, ans);
	}
	
	return 0;
}
