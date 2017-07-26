#include <bits/stdc++.h>

typedef __int128 lll;

const int Mod = 1e9 + 7;

int n;

lll pos(lll x) {
	
}

bool check(lll x) {
	lll a = pos(pos(x));
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d", &n);
		lll l = 1, r = (lll)n * n * n, ans;
		while (l <= r) {
			lll mid = (l + r) >> 1;
			if (check(mid)) ans = mid, l = mid + 1;
			else r = mid - 1;
		}
		printf("%d\n", (int)(ans % Mod));
	}
	
	return 0;
}
