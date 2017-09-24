#include <bits/stdc++.h>
#define y1 Y11
using namespace std;

const double eps = 1e-10;
int cs;
double r, x1, x2, y1, y2, a, b, d, l;

inline double mysqrt(double x) {
	if (x < 0.) {
		return 0.;
	} else {
		return sqrt(x);
	}
}

inline int sgn(double x) {
	if (x < -eps) {
		return -1.0;
	} else {
		return x > eps;
	}
}

inline double dis(double x1, double y1, double x2, double y2) {
	double x = x2 - x1, y = y2 - y1;
	return mysqrt(x * x + y * y);
}

inline bool check(double A) {
//cout << A << " " << a << endl;
	double B = mysqrt(A * A - a * a);
//cout << A << " " << B << endl;
	double A1 = a * a / B / B;
	double B1 = -2.0 * b * A * A / B / B;
	double C1 = r * r - A * A + A * A * b * b / B / B;
//cout << A1 << " " << B1 << " " << C1 << endl;
	double delta = B1 * B1 - 4 * A1 * C1;
	if (delta < -eps) {
		return false;
	} else {
	    if ((A1 * r * r + B1 * r + C1) * (A1 * r * r - B1 * r + C1) < eps || -B1 <= 2 * A1 * r && -B1 >= -2 * A1 * r) {
			return true;
		} else {
			return false;
		}
	}
	delta = mysqrt(delta);
	double y1 = (-B1 + delta) / 2 / A1;
	double y2 = (-B1 - delta) / 2 / A1;
cout << y1 << " " << y2 << endl;
	return y1 > -r - eps && y1 < r + eps || y2 > -r - eps && y2 < r + eps;
}

int main() {
	cin >> cs;
	for (; cs; --cs) {
		scanf("%lf%lf%lf%lf%lf", &r, &x1, &y1, &x2, &y2);
		
		d = dis(0, 0, x1, y1);
		l = dis(x1, y1, x2, y2);
		a = l / 2;
		b = mysqrt(d * d - a * a);
		if (sgn(d - r) == 0) {
			printf("%.6f\n", l);
			continue;
		}
		if (sgn(d) == 0) {
			printf("%.6f\n", r * 2);
			continue;
		}
		//cout << check(3.0) << endl;return 0;
		double left = a, right = mysqrt(r * r - b * b);
		while ((right - left) / max(1.0, right) > 1e-9) {
			double mid = (left + right) / 2;
			if (check(mid)) {
				right = mid;
			} else {
				left = mid;
			}
		}
		printf("%.6f\n", left * 2);
	}
}
