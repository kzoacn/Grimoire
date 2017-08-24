#include <bits/stdc++.h>

typedef long long ll;

ll calc(ll n, int x) {
	switch (x) {
		case 0:
			return 2 * n * n * 2;
		case 1:
			return 2 * n * n * 2 + (n + n - 1);
		case 2:
			return 2 * n * n * 2 + 2 * n * 2;
		case 3:
			return 2 * n * n * 2 + 2 * n * 2 + (n + n - 1) + 1 * 2;
	}
	
	return -1;
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		static int n;
		
		scanf("%d", &n);
		
		ll ans = n, l = 4, r = 1e9;
		while (l <= r) {
			ll mid = (l + r) >> 1;
			if (calc(mid / 4, mid % 4) >= n * 2ll) ans = mid, r = mid - 1;
			else l = mid + 1;
		}
		
		printf("%lld\n", ans);
	}
	
	return 0;
}
