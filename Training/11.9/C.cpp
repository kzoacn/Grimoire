#include <bits/stdc++.h>

#define __advance //__attribute__((optimize("O3")))

typedef unsigned long long ULL;

const int MAXN = 5e3 + 5;

int n, m;
ULL a[MAXN], b[MAXN];

__advance int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) scanf("%llu", a + i);
	for (int i = 1; i <= m; ++i) scanf("%llu", b + i);
	
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
			static ULL tmp;
			
			tmp = std::__gcd(a[i], b[j]);
			if (tmp != 1u) {
				a[i] /= tmp;
				b[i] /= tmp;
			}
		}
	
	puts("completed");
	
	return 0;
}
