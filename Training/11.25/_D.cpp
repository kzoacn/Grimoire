#include <bits/stdc++.h>
using namespace std;

int cs;
int n, m, a, b, c, d, r;

inline long double calc(long double t) {
	/*if (fabs(t - 1) < 1e-15) {
		return -1.0 * (a * r + c * r + a * d) / (b * r + d * r + b * d);
	}*/
	long double p = (t > 0) ? (t * t + 1. * d / r) : (t * t + 1. * b / r);
	if (t > 0) {
//printf("%.10f %.10f\n", )
		return 1.0 * c / r + tmp * calc(1 - 2 * t);
	} else {
		return 1.0 * a / r + tmp * calc(-1 - 2 * t);
	}
}

int main() {
	cin >> cs;
	for (; cs; --cs) {
		scanf("%d%d%d%d%d%d%d", &n, &m, &a, &b, &c, &d, &r);
		printf("%.10f\n", (double)calc(1. * n / m));
	}
}
