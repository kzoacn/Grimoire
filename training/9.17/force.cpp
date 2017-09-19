#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef long double LD;
typedef pair<LL, LL> pi;
#define X first
#define Y second
const LL N = 100000;
const LD eps = 1e-12;
int cs;
int K;

inline pi optimal(LD p, const pi &a, const pi &b) {
	LD ta = fabs(a.Y * 1.0 / a.X - p),
		tb = fabs(b.Y * 1.0 / b.X - p);
	if (ta < tb) {
		return a;
	} else {
		return b;
	}
}

int main() {
	cin >> cs;
	for (; cs; --cs) {
		scanf("%d", &K);
		LD p = pow(K * 1LL * K, 1./3);
		LL t = p - 1;
		for (int i = 0; i < 3; ++i) {
			if (t * t * t == K * 1LL * K) {
				printf("%d/1\n", (int)t);
				t = -10;
				break;
			}
			++t;
		}
		if (t == -10) {
			continue;
		}
		pi ans(1, 0);
		for (LL i = 1; i <= N; ++i) {
			for (LL j = -1; j <= 1; ++j) {
				pi now(i, i * p + j);
				if (__gcd((LL)i, (LL)(i * p + j)) > 1) {
					continue;
				}
				ans = optimal(p, ans, now);
			}
		}
		//ans = optimal(p, ans, pi(24337,50623));
		//printf("%.20f %.20f %.20f\n", 50623.0 / 24337, (double)ans.Y / ans.X, (double)p);
		printf("%lld/%lld\n", ans.Y, ans.X);
	}
}
