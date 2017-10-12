#include <bits/stdc++.h>

int main() {
	__int128 aasdfasf;
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		static int n, a, b, gcd;
		
		scanf("%d%d%d", &n, &a, &b);
		
		gcd = std::__gcd(a, b);
		
		printf("Case #%d: %s\n", kase, (n / gcd) & 1 ? "Yuwgna" : "Iaka");
	}
	
	return 0;
}
