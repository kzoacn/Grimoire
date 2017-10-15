#include <bits/stdc++.h>
using namespace std;

typedef long double LD;

const int MAXN = 211111;
int n, pw;

struct L {
	LD k1, k2, b1, b2, x;
	L() {}
	L(LD _k1, LD _k2, LD _b1, LD _b2, LD _x): k1(_k1), k2(_k2), b1(_b1), b2(_b2), x(_x) {};
} a[MAXN];

inline bool cmp(const L &p, const L &q) {
	return p.x < q.x;
}

int main() {
	while (scanf("%d", &n), n) {
		scanf("%d", &pw);
		LD k = pw, b = 0.0;
		int m = 1;
		a[1].k1 = 0.0, a[1].b1 = 0.0, a[1].k2 = 0.0, a[1].b2 = 0.0, a[1].x = 0.0;
		for (int i = 1; i <= n; ++i) {
			int vw, pf, vf, th;
			scanf("%d%d%d%d", &vw, &pf, &vf, &th);
			if (vw == 0) {
				b += max(0.0, 1.0 * th / vf) * pf;
				continue;
			}
			LD kk = -1.0 * pf * vw / vf, bb = 1.0 * pf * th / vf;
			LD x = th * 1.0 / vw;
			if (kk < 0) {
				a[++m] = L(kk, 0.0, bb, 0.0, x);
			} else {
				a[++m] = L(0.0, kk, 0.0, bb, x);
			}
		}
		
		sort(a + 1, a + m + 1, cmp);
		for (int i = 1; i <= m; ++i) {
			if (a[i].x < 0) {
				k += a[i].k2;
				b += a[i].b2;
			} else {
				k += a[i].k1;
				b += a[i].b1;
			}
		}
		LD ans = b;
		for (int i = 1; i <= m; ++i) {
			if (a[i].x < 0) {
				continue;
			}
			ans = min(ans, k * a[i].x + b);
			k += a[i].k2 - a[i].k1;
			b += a[i].b2 - a[i].b1;
		}
		printf("%.4f\n", (double)ans);
	}
}
