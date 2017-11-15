#include <bits/stdc++.h>

const int MAXN = 1e5 + 5;
const double eps = 1e-10;

int sgn(double x) { return x < -eps ? -1 : x > eps; }

struct Ingre {
	int g, a, b, id;
	
	bool operator < (const Ingre &rhs) const {
		return a * rhs.b > rhs.a * b;
	}
	
	void scan(int ID) {
		scanf("%d%d%d", &g, &a, &b);
		id = ID;
	}
} ingre[MAXN];

int n, A, B;
double used[MAXN];

int main() {
#ifndef LOCAL
	freopen("burrito.in", "r", stdin);
	freopen("burrito.out", "w", stdout);
#endif
	
	scanf("%d%d%d", &n, &A, &B);
	for (int i = 1; i <= n; ++i) {
		ingre[i].scan(i);
	}
	
	std::sort(ingre + 1, ingre + n + 1);
	double aa = 0, bb = 0;
	for (int i = 1; i <= n; ++i) {
		if (ingre[i].a == 0) continue;
		if (ingre[i].b == 0) {
			aa += ingre[i].a * ingre[i].g;
			used[ingre[i].id] = ingre[i].g;
			continue;
		}
		double t = std::min((B - bb) / ingre[i].b, 1. * ingre[i].g);
		aa += ingre[i].a * t;
		bb += ingre[i].b * t;
		
		used[ingre[i].id] = t;
		if (sgn(t - ingre[i].g)) break;
	}
	
	if (aa >= A) {
		printf("%f %f\n", aa, bb);
		for (int i = 1; i <= n; ++i)
			printf("%f%c", used[i], " \n"[i == n]);
	}
	else puts("-1 -1");
	
	return 0;
}
