#include <bits/stdc++.h>

int n, x[35], y[35];

bool poi[205][205];

bool isSquare(int p, int q) {
	return x[p] != x[q] && y[p] != y[q] && poi[x[p]][y[q]] && poi[x[q]][y[p]];
}
/*
int xl, xr, yl, yr;

bool inSquare(int x, int y) {
	return xl <= x && x <= xr && yl <= y && y <= yr;
}
*/

int Area(int xl, int yl, int xr, int yr) {
	return std::abs((xl - xr) * (yl - yr));
}

int Area(int i, int j) {
	return std::abs((x[i] - x[j]) * (y[i] - y[j]));
}

int Check(int i, int j, int p, int q) {
	/*xl = std::min(x[i], x[j]); xr = std::max(x[i], x[j]);
	yl = std::min(y[i], y[j]); yr = std::max(y[i], y[j]);
	if (inSquare(x[p], y[p]) || inSquare(x[p], y[q]) || inSquare(x[q], y[p]) || inSquare(x[q], y[q])) return 0;
	
	xl = std::min(x[p], x[q]); xr = std::max(x[p], x[q]);
	yl = std::min(y[p], y[q]); yr = std::max(y[p], y[q]);
	if (inSquare(x[i], y[i]) || inSquare(x[i], y[j]) || inSquare(x[j], y[i]) || inSquare(x[j], y[j])) return 0;
	*/
	
	int xr = std::min(std::max(x[i], x[j]), std::max(x[p], x[q])), xl = std::max(std::min(x[i], x[j]), std::min(x[p], x[q])), 
		yr = std::min(std::max(y[i], y[j]), std::max(y[p], y[q])), yl = std::max(std::min(y[i], y[j]), std::min(y[p], y[q]));
	
	if (xr >= xl && yr >= yl) {
		if (std::min(x[i], x[j]) == std::min(x[p], x[q]) || std::max(x[i], x[j]) == std::max(x[p], x[q]) || 
			std::min(y[i], y[j]) == std::min(y[p], y[q]) || std::max(y[i], y[j]) == std::max(y[p], y[q]))
			return 0;
		int ar = Area(xl, yl, xr, yr);
		if (ar == Area(i, j) && ar == Area(p, q)) return 0;
		if (ar == Area(i, j) || ar == Area(p, q)) return std::max(Area(i, j), Area(p, q));
		return 0;
	}
	
	return Area(i, j) + Area(p, q);
}

int main() {
	while (~scanf("%d", &n) && n) {
		memset(poi, 0, sizeof poi);
		
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", x + i, y + i);
			poi[x[i]][y[i]] = 1;
		}
		
		int ans = -1;
		
		for (int i = 1; i <= n; ++i)
			for (int j = i + 1; j <= n; ++j)
				for (int p = 1; p <= n; ++p) if (p != i && p != j)
					for (int q = p + 1; q <= n; ++q) if (q != i && q != j) {
						int S;
						if (isSquare(i, j) && isSquare(p, q) && (S = Check(i, j, p, q))) {
							//int S = std::abs((x[i] - x[j]) * (y[i] - y[j])) + std::abs((x[p] - x[q]) * (y[p] - y[q]));
							ans = std::max(ans, S);
						}
					}
		
		if (ans == -1) puts("imp");
		else printf("%d\n", ans);
	}
	
	return 0;
}
