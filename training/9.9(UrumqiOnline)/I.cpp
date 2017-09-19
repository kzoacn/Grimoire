#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

char a[555][555];
int deg[1111];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	int testcase;
	cin >> testcase;
	for (; testcase; --testcase) {
		int n;
		cin >> n;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1 + i; j <= n; ++j) {
				if (i % 2 == j % 2) {
					a[i][j] = 2;
				} else {
					a[i][j] = 1;
				}
			}
		}
		if (n == 5) {
			cout << 0 << endl;
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= n; ++j) {
					a[i][j] = i != j;
				}
			}
			a[1][2] = a[2][1] = 2;
			a[2][3] = a[3][2] = 2;
			a[3][4] = a[4][3] = 2;
			a[4][5] = a[5][4] = 2;
			a[1][5] = a[5][1] = 2;
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j < n; ++j) {
					cout << (int)a[i][j] << " ";
				}
				cout << (int)a[i][n] << "\n";
			}
			continue;
		}
		LL tot = 0;
		if (n % 2 == 0) {
			int d = (n - 1) / 2;
			d = d * (d + 1);
			tot = 1LL * n * d;
			//cout << tot << endl;
		} else {
			for (int i = 1; i + 2 <= n; i += 2) {
				a[i][i + 2] = 1;
				//cout << "turn to 1" << " " << i << " " << i + 2 << endl;
			}
			for (int i = 2; i <= n; i += 2) {
			//	cout << "turn to 2" << " " << i << " " << i + 1 << endl;
				a[i][i + 1] = 2;
			}
			for (int i = 1; i + 2 <= n; i += 4) {
				a[i][i + 2] = 2;
			}
			for (int i = 1; i <= n; ++i) {
				deg[i] = 0;
			}
			for (int i = 1; i <= n; ++i) {
				for (int j = i + 1; j <= n; ++j) {
					if (a[i][j] == 2) {
						deg[i]++;
						deg[j]++;
					}
				}
			}
			for (int i = 1; i <= n; ++i) {
				tot += deg[i] * 1LL * (n - 1 - deg[i]);
				//cout << i << " " << deg[i] << endl;
			}
		}
		tot /= 2;
		tot = 1LL * n * (n - 1) * (n - 2) / 6 - tot;
		cout << tot << endl;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j < i; ++j) {
				a[i][j] = a[j][i];
			}
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j < n; ++j) {
				cout << (int)a[i][j] << " ";
			}
			cout << (int)a[i][n] << "\n";
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j < i; ++j) {
				for (int k = 1; k < j; ++k) {
					if (a[i][j] == a[j][k] && a[j][k] == a[k][i]) {
						--tot;
					}
				}
			}
		}
		//cout << "left ans = " << tot << endl;
	}
	cout.flush();
}


