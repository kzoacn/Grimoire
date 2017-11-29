#include <bits/stdc++.h>
using namespace std;

int f[5111][5111];
int cs, a[111], n, m;

int main() {
	cin >> cs;
	int c = 0;
	for (; cs; --cs) {
		cin >> n >> m;
		for (int i = 1; i <= m; ++i) {
			scanf("%d", &a[i]);
		}
		
		++c;
		f[0][0] = c;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j <= i; ++j) {
				if (f[i][j] < c) {
					continue;
				}
//cout << i << " " << j << endl;
				if (i + j > n) {
					continue;
				}
				for (int k = 1; k <= m; ++k) {
					if (i + j + a[k] <= n) {
						f[i + j + a[k]][j + a[k]] = c;
					}
				}
			}
		}
		int ans = -1;
		for (int i = n; i >= 0; --i) {
			if (f[n][i] == c) {
				ans = i;
				break;
			}
		}
		cout << ans << endl;
	}
}
