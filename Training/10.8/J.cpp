#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL MOD = 1e9 + 7;
const int MAXN = 233;
LL c[MAXN + 10][MAXN + 10], f[MAXN + 10][MAXN + 10][MAXN + 10], fac[MAXN + 10];
int testcase, nn, mm, p, q;

int main() {
	for (int i = 0; i < MAXN; ++i) {
		c[i][0] = c[i][i] = 1;
		for (int j = 1; j < i; ++j) {
			c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % MOD;
		}
	}
	fac[0] = 1;
	for (int i = 1; i < MAXN; ++i) {
		fac[i] = 1LL * fac[i - 1] * i % MOD;
	}
	
	f[0][0][0] = 1;
	for (int i = 1; i < MAXN; ++i) {
		for (int a = 0; a * 2 < MAXN; ++a) {
			for (int b = 0; a * 2 + b < MAXN; ++b) {
				f[i][a][b] = f[i - 1][a][b];
				if (b) {
					f[i][a][b] = (f[i][a][b] + 1LL * b * f[i - 1][a][b - 1]) % MOD;
				}
				if (a) {
					f[i][a][b] = (f[i][a][b] + 1LL * a * f[i - 1][a - 1][b + 1]) % MOD;
				}
				if (b >= 2) {
				//if (i == 1 && a == 0 && b == 2 ) cout << "adsf" << " " << c[b][2] << endl;
					f[i][a][b] = (f[i][a][b] + 1LL * c[b][2] * f[i - 1][a][b - 2]) % MOD;
				}
				if (a && b) {
					f[i][a][b] = (f[i][a][b] + 1LL * a * b * f[i - 1][a - 1][b]) % MOD;
				}
				if (a >= 2) {
					f[i][a][b] = (f[i][a][b] + 1LL * c[a][2] * f[i - 1][a - 2][b + 2]) % MOD;
				}
			}
		}
	}
	/*cout << f[1][0][2] << endl;
	cout << f[1][0][1] << endl;
	cout << f[1][0][0] << endl;
	cout << f[2][0][2] << endl;
	return 0;*/
	cin >> testcase;
	for (; testcase; --testcase) {
		scanf("%d%d%d%d", &nn, &mm, &q, &p);
		LL ans = 0;
		for (int k = 0; k <= nn && k <= mm && k <= p; ++k) {
			LL tmp = 1LL * c[nn][k] * c[mm][k] % MOD * fac[k] % MOD;
			LL tot = 0;
			int n = nn - k, m = mm - k;
			for (int a = 0; a <= n; ++a) {
				for (int b = 0; a + b <= n && a * 2 + b <= q; ++b) {
				//cout << a << " " << b << endl;
					tot = (tot + 1LL * c[n][a] * c[n - a][b] % MOD * f[m][a][b]) % MOD;
//printf("single(%d, %d) = %d\n", a, b, c[n][a] * c[n - a][b] % MOD * f[m][a][b]);
				}
			}
//cout << k << " " << tmp << " " << tot << endl;
			ans = (ans + tmp * tot) % MOD;
		}
		ans = (ans - 1) % MOD;
		ans = (ans + MOD) % MOD;
		printf("%d\n", (int)ans);
	}
}

