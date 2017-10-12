#include <bits/stdc++.h>
using namespace std;

typedef long double LD;
const int N = 10000;
int n, testcase;
double p[1111];
int a[1111];
LD f[11][N + 1];

inline LD get(LD p, LD a) {
	p = 1. - p;
	return pow(p, a);
}

int main() {
	scanf("%d", &testcase);
	for (; testcase; --testcase) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d%lf", &a[i], &p[i]);
			f[i][0] = 1.0;
			for (int j = 1; j <= N; ++j) {
				f[i][j] = f[i][j - 1] * p[i];
			}
		}
		if (n == 1) {
			printf("%.6f\n", 1.0);
			continue;
		}		
		
		for (int i = 1; i <= n; ++i) {
			LD ans = 0.0;
			for (int k = 1; k <= N; ++k) {
				LD t1 = get(f[i][k], a[i]), t2 = get(f[i][k - 1], a[i]);
				LD t = t1 - t2;
				for (int j = 1; j <= n; ++j) {
					if (j != i) {
						t = t * get(f[j][k - 1], a[j]);
					}
				}
				ans += t;
			}
			printf("%.6f%s", (double)ans, i == n ? "\n" : " ");
		}
	}
}
