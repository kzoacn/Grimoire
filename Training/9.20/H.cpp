#include <bits/stdc++.h>
using namespace std;

double x, y, p, q;
int cs;

int main() {
	cin >> cs;
	for (; cs; --cs) {
		scanf("%lf%lf%lf%lf", &x, &y, &p, &q);
		double a = q * p * (x + y) + (1 - q) * x,
				b = q * y + (1 - q) * p * (x + y);
		if (a > b) {
			printf("tiger %.4f\n", a);
		} else {
			printf("wolf %.4f\n", b);
		}
	}
}
