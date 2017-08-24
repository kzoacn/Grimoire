#include <bits/stdc++.h>

int n, a, b;

int main() {
	scanf("%d%d%d", &n, &a, &b);
	
	int xx = 0, yy = 0;
	
	for (int x = 1; x <= n; ++x)
		for (int y = x; y; y = (y - 1) & x)
			if ((xx == 0 && yy == 0) || ((1ll * a * x + 1ll * b * y) ^ (1ll * a * y + 1ll * b * x)) > ((1ll * a * xx + 1ll * b * yy) ^ (1ll * a * yy + 1ll * b * xx))) {
				xx = x, yy = y;
			}
	
	printf("%d %d\n", xx, yy);
	
	return 0;
}
