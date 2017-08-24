#include <bits/stdc++.h>

typedef long long ll;

ll n, m;

ll C2(ll x) {
	return x * (x - 1) / 2;
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%lld%lld", &n, &m);
		
		ll ans = 0;
		
		if (m <= n - 1) {
			ans = m + C2(m) * 2 + ((m + 1) * (n - m - 1) + C2(n - m - 1)) * n;
		}
		else {
			ans = std::max(n - 1 + C2(n - 1) * 2 - (m - (n - 1)), C2(n));
		}
		
		printf("%lld\n", ans * 2);
	}
	
	return 0;
}
