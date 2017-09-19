#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1111111;
typedef long long LL;

struct Frac {
	LL u, v;
	
	Frac() {}
	Frac(LL u, LL v): u(u), v(v) {}
	
	bool operator < (const Frac &rhs) const {
		return u * rhs.v < rhs.u * v;
	}
	
	bool operator == (const Frac &rhs) const {
		return !(*this < rhs) && !(rhs < *this);
	}
};

struct A {
	LL d, v;
	int w;
} a[MAXN];

int testcase, W = 80000000;
int L, n;

inline bool cmp(const A &p, const A &q) {
	return abs(p.v) < abs(q.v);
}

Frac meetTime(int x, int y) {
//	if (v[x] == v[y]) return d[x] == d[y] ? Frac(0, 1) : Frac(1, 0);
//	if (std::abs(v[x]) < std::abs(v[y])) std::swap(x, y);
	
	int vy = a[y].v - a[x].v;
	if (vy > 0) return Frac((1ll * a[x].d - a[y].d + L) % L, vy);
	return Frac((1ll * a[y].d - a[x].d + L) % L, -vy);
}

inline void update(Frac &now, int x, int y) {
	if (a[x].w != a[y].w) {
		now = max(now, meetTime(x, y));
	}
}

int main() {
	srand(time(0));

	cin >> testcase;
	for (; testcase; --testcase) {
		cin >> n >> L;
		int tot = W * 1LL * n / 1000000;
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", &a[i].d);
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%lld", &a[i].v);
		}
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i].w);
		}
		
		Frac ans = Frac(0, 1);
		sort(a + 1, a + n + 1, cmp);
		for (int i = 1; i <= 100 && i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				update(ans, i, j);
				update(ans, j, i);
			}
		}
		for (; tot; --tot) {
			int u, v;
			u = rand() % n + 1;
			v = rand() % n + 1;
			update(ans, u, v);
		}
		
		LL gcd = std::__gcd(ans.u, ans.v);
		ans.u /= gcd;
		ans.v /= gcd;
		
		printf("%lld/%lld\n", ans.u, ans.v);
	}
}
