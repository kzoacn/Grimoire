#include <bits/stdc++.h>
using namespace std;

int testcase, n, Q, a[1111][1111];

int main() {
	scanf("%d", &testcase);
	for (; testcase; --testcase) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &a[i][i]);
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = i + 1; j <= n; ++j) {
				a[i][j] = max(a[i][j - 1], a[j][j]);
			}
		}
		scanf("%d", &Q);
		for (; Q; --Q) {
			int l, r;
			scanf("%d%d", &l, &r);
			printf("%d\n", a[l][r]);
		}
	}
}
