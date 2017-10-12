#include <bits/stdc++.h>

typedef long long ll;

int n;

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d", &n);
		ll ans = 0, a, b;
		for (int i = 1; i <= n; ++i) {
			scanf("%lld%lld", &a, &b);
			ans += a * b;
		}
		printf("%lld\n", ans);
	}
	
	return 0;
}
