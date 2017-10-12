#include <bits/stdc++.h>
using namespace std;

int testcase;
double l, d;

int main() {
	cin >> testcase;
	for (; testcase; --testcase) {
		scanf("%lf%lf", &l, &d);
		if (d > l - 1e-8) {
			printf("%.6f\n", 0.0);
			continue;
		}
		double p = d / l;
		double ans = 1 + log(l) - log(d);
		printf("%.6f\n", ans);
	}
}
