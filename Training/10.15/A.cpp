#include <bits/stdc++.h>

typedef long long ll;

struct Frac {
	ll u, v;
	
	void norm() {
		static ll gcd;
		gcd = std::__gcd(u, v);
		u /= gcd; v /= gcd;
		if (v < 0) {
			u = -u; v = -v;
		}
	}
	
	Frac() {}
	Frac(ll u, ll v): u(u), v(v) {
		norm();
	}
	
	Frac operator + (const Frac &rhs) const {
		static Frac res;
		res = Frac(u * rhs.v + rhs.u * v, v * rhs.v);
		res.norm();
		return res;
	}
	
	Frac operator - (const Frac &rhs) const {
		static Frac res;
		res = Frac(u * rhs.v - rhs.u * v, v * rhs.v);
		res.norm();
		return res;
	}
};

char s[200005], *c;

int stk[25], top;

int main() {
	while (~scanf("%s", (c = s)) && *s != '#') {
		top = 0;
		while (*c) {
			if (*c == 'w') {
				stk[++top] = 1; c += 4;
			}
			else {
				stk[++top] = -1; c += 5;
			}
		}
		
		Frac ans;
		int cnt = 1;
		if (stk[top] == 1) ans = Frac(90, 1);
		else ans = Frac(0, 1);
		for (int i = top - 1; i; --i) {
			if (stk[i] == 1) ans = ans + Frac(90, 1ll << cnt);
			else ans = ans - Frac(90, 1ll << cnt);
			++cnt;
		}
		
		if (ans.v == 1) printf("%lld\n", ans.u);
		else printf("%lld/%lld\n", ans.u, ans.v);
	}
	
	return 0;
}
