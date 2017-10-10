#include <bits/stdc++.h>
using namespace std;

int testcase, n, a[111], c[111];
double b[111];

double eps = 1e-7;

int main() {
	cin >> testcase;
	for (int cs = 1; cs <= testcase; ++cs) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
		}
		sort(a + 1, a + n + 1);
		
		int ans = n - 1;
		for (int i = 1; i <= n; ++i) {
			for (int j = i + 1; j <= n; ++j) {
				for (int d = 1; d <= n; ++d) {
					double tmp = (a[j] - a[i]) * 1.0 / d;
					for (int k = 1; k <= n; ++k) {
						b[k] = a[i] + tmp * k;
					}
					sort(b + 1, b + n + 1);
					for (int l = 1; l + d - 1 <= n; ++l) {
						int h = l + d - 1;
						//cout << i << " " << j << " " << h << " " << l << endl;
						for (int k = 1; k <= n; ++k) {
							b[k] -= tmp;
						}			
						//cout << 1 << endl;
						int nowans = n;
						int id = 1;
						for (int k = 1; k <= n; ++k) {
							while (id <= n && b[id] + eps < a[k]) {
								++id;
							}
							if (fabs(a[k] - b[id]) < eps) {
								--nowans;
							}
						}
						ans = min(ans, nowans);
					}
				}
			}
		}
		
		printf("Case #%d: %d\n", cs, ans);
	}
}
