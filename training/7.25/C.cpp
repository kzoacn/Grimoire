#include <bits/stdc++.h>

double ave = 0;

int n, a[1005];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i); ave += a[i];
	}
	
	ave /= n;
	
	int ans = 0;
	for (int i = 1; i <= n; ++i) if (a[i] - ave > 1e-8) ++ans;
	
	printf("%d\n", ans);
	
	return 0;
}
