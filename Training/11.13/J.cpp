#include <bits/stdc++.h>
using namespace std;

int n, w, h;
double eps = 1e-8;

struct P {
	double x, y;
} p[1111111][3];

typedef long long LL;

double random(double l, double r) {
	LL t = rand() * RAND_MAX + rand();
	return (1. * t / RAND_MAX / RAND_MAX) * (r - l);
}

inline int sgn(double x) {
	if (x > eps) {
		return 1;
	} else {
		if (x < -eps) {
			return -1;
		} else {
			return 0;
		}
	}
}

int f[111];

double cross(double x1, double y1, double x2, double y2) {
	return x1 * y2 - x2 * y1;
}

int main() {
	cin >> n >> w >> h;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < 3; ++j) {
			scanf("%lf%lf", &p[i][j].x, &p[i][j].y);
		}
	}
	
	for (; ;) {
		double x = random(0.0, w),
				y = random(0.0, h);
	//cout << x << " " << y << endl;
		x = 1.1;
		y = 1.6;
		bool flag = true;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < 3; ++j) {
				f[j] = sgn(cross(x - p[i][j].x, y - p[i][j].y, p[i][(j + 1) % 3].x - p[i][j].x, p[i][(j + 1) % 3].y - p[i][j].y));
			}
			sort(f, f + 3);
			if (!(f[0] == -1 && f[2] == 1)) {
				flag = false;
				break;
			}
		}
		if (flag) {
			return 0;
		}
	}
}
