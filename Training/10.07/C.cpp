#include <bits/stdc++.h>

#define __advance __attribute__((optimize("O3")))

typedef long long ll;

int sgn(ll x) { return x < 0 ? -1 : x > 0; }

struct vec {
	ll x, y;
	
	vec() {}
	vec(ll x, ll y): x(x), y(y) {}
	
	__advance __inline vec operator - (const vec &rhs) const { return vec(x - rhs.x, y - rhs.y); }
};

__advance __inline ll XX(vec a, vec b) { return a.x * b.y - a.y * b.x; }

__advance __inline bool inter(vec a, vec b, vec p, vec q) {
	return sgn(XX(p - a, b - a)) * sgn(XX(q - a, b - a)) <= 0 && 
		   sgn(XX(a - p, q - p)) * sgn(XX(b - p, q - p)) <= 0;
}

int n, m, q;

vec enemy[10005], wall[10005][2], now;

__advance int main() {
	for (register int kase = 1; ~scanf("%d%d%d", &n, &m, &q); ++kase) {
		for (register int i = 1; i <= n; ++i)
			scanf("%lld%lld", &enemy[i].x, &enemy[i].y);
		for (register int i = 1, j; i <= m; ++i)
			for (j = 0; j < 2; ++j)
				scanf("%lld%lld", &wall[i][j].x, &wall[i][j].y);
		
		printf("Case #%d:\n", kase);
		while (q--) {
			scanf("%lld%lld", &now.x, &now.y);
			int ans = 0;
			for (register int i = 1; i <= n; ++i) {
				bool flag = 1;
				for (register int j = 1; j <= m; ++j)
					if (inter(now, enemy[i], wall[j][0], wall[j][1])) {
						flag = 0; break;
					}
				ans += flag;
			}
			printf("%d\n", ans);
		}
	}
	
	return 0;
}
