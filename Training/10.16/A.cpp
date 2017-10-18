#include <bits/stdc++.h>

double d;

double Sqrt(double x) {
	return x < 0 ? 0 : std::sqrt(x);
}

int main() {
	std::cin >> d;
	
	double ans = std::sqrt(2.) * d;
	
	for (int h = 1; h <= 10; ++h) {
		if (h > d) break;
		double a = Sqrt(d * d - h * h);
		ans = std::max(ans, h + std::max(a, 1.));
	}
	
	printf("%.12f\n", ans);
	
	return 0;
}
