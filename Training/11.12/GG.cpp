#include <bits/stdc++.h>
using namespace std;

typedef long double LD;
const int MAXN = 111;
int testcase, n;
int l[MAXN], r[MAXN];
__float128 f[MAXN][MAXN], comb[MAXN][MAXN], g[MAXN];

int main() {
	cin >> testcase;
	for (int cs = 1; cs <= testcase; ++cs) {
		cin >> n;
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", &l[i], &r[i]);
		}
		
		for (int i = 0; i < MAXN; ++i) {
			comb[i][0] = comb[i][i] = 1;
			for (int j = 1; j < i; ++j) {
				comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
			}
		}
		memset(f, 0, sizeof(f));
		f[0][0] = 1;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < i; ++j) {
				f[i][j] = 0;
				int left = l[i], right = r[i];
				LD t = 1.0;
				for (int k = 0; k <= j; ++k) {
					left = max(left, l[i - k]);
					right = min(right, r[i - k]);
					t = t * (r[i - k] - l[i - k] + 1);
					if (left > right) {
						break;
					}
					f[i][j] += f[i - k - 1][j - k] / t * (right - left + 1);
				}
			}
		}
		
		for (int i = n - 1; i >= 0; --i) {
			g[i] = f[n][i];
//cout << i << " " << (double)f[n][i] << endl;
			LD c = 1;
			for (int j = i + 1; j < n; ++j) {
				c = c * j / (j - i);
				g[i] -= g[j] * comb[j][i];
			}
//cout << "final g: " << i << " " << (double)g[i] << endl;
		}
		
		LD total = 1;
		/*for (int i = 1; i <= n; ++i) {
			total *= (r[i] - l[i] + 1);
		}*/
		LD ans = 0.0;
		for (int i = 0; i < n; ++i) {
//cout << "prop: " << i << " " << (double)g[i] / total << endl;
			int tmp = n - 1 - i;
			ans += g[i] / total * tmp * sqrt(tmp);
		}
		
		printf("Case #%d: %.10f\n", cs, (double)ans);
	}
}
