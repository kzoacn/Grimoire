#include <bits/stdc++.h>

#define __advance __attribute__((optimize("O3")))

typedef long long ll;
typedef __int128 LL;
typedef long double ldb;

const ldb eps = 1e-12;

struct Frac {
	ll u, v;
	
	Frac() {}
	Frac(ll u, ll v): u(u), v(v) {}
	
	void print() {
		printf("%lld/%lld\n", u, v);
	}
};

char s[20];

ll ten[10];

ll F; int k;
double dF, dF0, dF1;

__advance bool check(Frac x) {
	ldb dx = (ldb)((LL)x.u * x.u) / ((LL)x.v * x.v) * ten[k];
	ll lx = std::floor(dx);
//	printf("%.10f %lld\n", (double)dx, lx);
	if (dx - lx + eps > 0.5) ++lx;
	return lx == F;
}

__advance Frac Farey() {
	static Frac L, R, mid, tmp;
	
	L = Frac(0, 1), R = Frac(1, 1);
	
	while (1) {
		mid = Frac(L.u + R.u, L.v + R.v);
#ifdef LOCAL_X
		mid.print();
		//if (mid.v > 100) return mid;
#endif
		if (check(mid)) return mid;
//		if (mid.v > 100000) break;
		if ((LL)F * mid.v * mid.v < (LL)mid.u * mid.u * ten[k]) {
			ll t = std::max((ll)std::floor((R.u - dF1 * R.v) / (dF1 * L.v - L.u)) - 20, 1ll);
			R = Frac(L.u * t + R.u, L.v * t + R.v);
		}
		else {
			ll t = std::max((ll)std::floor((dF0 * L.v - L.u) / (R.u - dF0 * R.v)) - 20, 1ll);
			L = Frac(L.u + R.u * t, L.v + R.v * t);
		}
	}
	/*
	ll x = std::floor((dF + std::sqrt(dF)) / (1 - dF)) - 50000;
	for (ll i = x; i <= x + 100000; ++i)
	*/
	assert(0);
	return Frac(-1, -1);
}

__advance int main() {
	ten[0] = 1;
	for (int i = 1; i <= 9; ++i) ten[i] = ten[i - 1] * 10;
	
	for (int kase = 1; ~scanf("%s", s); ++kase) {
		k = strlen(s) - 2;
		sscanf(s + 2, "%lld", &F);
		sscanf(s, "%lf", &dF);
		dF0 = std::sqrt(std::max(dF - (0.6 / ten[k]), 0.));
		dF1 = std::sqrt(dF + (0.6 / ten[k]));
		
		printf("Case #%d: ", kase);
		Farey().print();
	}
	
	return 0;
}
