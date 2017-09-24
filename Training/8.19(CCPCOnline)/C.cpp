#include <bits/stdc++.h>
using namespace std;

int testcase, n;
char a[3333][3333];

int main() {
	cin >> testcase;
	for (; testcase; --testcase) {
		scanf("%d", &n);
		for (int i = 1; i < n; ++i) {
			for (int j = i + 1; j <= n; ++j) {
				int x;
				scanf("%d", &x);
				a[j][i] = a[i][j] = (char)x;
			}
		}
		
		if (n > 6) {
			puts("Bad Team!");
			continue;
		}
		bool flag = false;
		for (int i = 1; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				for (int k = j + 1; k <= n; ++k) {
					if (a[i][j] && a[j][k] && a[k][i] || !a[i][j] && !a[j][k] && !a[k][i]) {
						flag = true;
					}
				}
			}
		}
		if (flag) {
			puts("Bad Team!");
		} else {
			puts("Great Team!");
		}
	}
}
