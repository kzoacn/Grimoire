#include <bits/stdc++.h>

typedef long long LL;

LL qpow(LL a, LL x, LL Mod) {
	LL res = 1;
	for (; x; x >>= 1) {
		if (x & 1) res = 1LL * res * a % Mod;
		a = 1LL * a * a % Mod;
	}
	return res;
}

/*LL exgcd(LL a, LL b, LL &x, LL &y) {
	if (!b) {
		x = 1, y = 0;
		return a;
	}
	LL d = exgcd(b, a % b, x, y);
	LL t = x; x = y; y = t - a / b * y;
	return d;
}*/

LL inv(LL a, LL p) {
	return qpow(a, p - 2, p);
}

std::unordered_map<LL, LL> hash;

LL bsgs(LL a, LL b, LL p) {
	LL m = std::sqrt(p) + 0.5, v = inv(qpow(a, m, p), p), e = 1;
	hash.clear(); hash[1] = 0;
	for (int i = 1; i < m; ++i) {
		e = e * a % p;
		hash[e] = i;
	}
	for (int i = 0; i <= m; ++i) {
		if (hash.count(b)) return i * m + hash[b];
		b = b * v % p;
	}
	return -1;
}

/*LL exbsgs(LL a, LL b, LL p) {
	b %= p;
	LL e = 1 % p;
	for (int i = 0; i < 100; ++i) {
		if (e == b) return i;
		e = e * a % p;
	}
	int r = 0;
	while (std::__gcd(a, p) != 1) {
		LL d = std::__gcd(a, p);
		if (b % d) return -1;
		p /= d; b /= d; b = b * inv(a / d, p);
		++r;
	}
	LL res = bsgs(a, b, p);
	if (res == -1) return -1;
	return res + r;
}*/

int main() {
#ifndef LOCAL
	freopen("alot.in", "r", stdin);
	freopen("alot.out", "w", stdout);
#endif
	
	static LL P;
	static int Q;
	
	scanf("%lld%d", &P, &Q);
	while (Q--) {
		static LL x, y;
		
		scanf("%lld%lld", &x, &y);
		
		if (x) {
			printf("%lld\n", bsgs(x, y, P));
		} else {
			if (y == 0) puts("1");
			else if (y == 1) puts("0");
			else puts("-1");
		}
	}
	
	return 0;
}

/*

5 5
2 4
3 2
4 1
4 2
1 1

2
3 (-1 output)
0
-1
0

*/
