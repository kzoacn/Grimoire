#include <bits/stdc++.h>
using namespace std;

const int MAXN = 256;
const int INF = 1000000000;
const int MAXP = 55555;
int q[MAXN][MAXP];
int cost[MAXN], lim[MAXN], size[MAXN], tot[MAXN], val[MAXN], sum[MAXN];
int n, m, p, testcase;
int h[MAXN], t[MAXN], dp[MAXN][MAXP], f[MAXN][MAXP];

inline void dp1(int p) {
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= p; ++j) {
			dp[i][j] = INF;
		}
	}
	dp[0][0] = 0;
//p = 14;
	for (register int i = 1; i <= n; ++i) {
		for (register int j = 0; j < val[i]; ++j) {  
			h[j] = 1;
			t[j] = 0;
		}
		for (register int j = 0, mo = 0; j <= p; ++j, mo = mo + 1 == val[i] ? 0 : mo + 1) {
			while (h[mo] <= t[mo] && j - q[mo][h[mo]] > val[i] * sum[i]) {
			  
				++h[mo];
			}
			  
			register int tmp = dp[i - 1][j] - j / val[i] * size[i];
			while (h[mo] <= t[mo] && tmp <= dp[i - 1][q[mo][t[mo]]] - q[mo][t[mo]] / val[i] * size[i]) {
			  
				--t[mo];
			}
			q[mo][++t[mo]] = j;
			dp[i][j] = dp[i - 1][q[mo][h[mo]]] - q[mo][h[mo]] / val[i] * size[i] + j / val[i] * size[i];
			  
		}
	}
	for (int j = p - 1; j >= 0; --j) {//  
		dp[n][j] = min(dp[n][j], dp[n][j + 1]);
	}
	//cout << n << " " << p - 200 << " " << dp[1][7] << " " << dp[1][14] << endl;
	//cout << dp[n][p - 200] << endl;
}

inline void dp2() {
	int c = 0;
	for (int i = 1; i <= m; ++i) {  
		c += cost[i] * tot[i];
	}
	c = min(c, 50000);
	for (int i = 1; i <= m; ++i) {
		for (int j = 0; j <= 50000; ++j) {  
			f[i][j] = 0;
		}
	}
	//cout << c << endl;
	for (register int i = 1; i <= m; ++i) {
		for (register int j = 0; j < cost[i]; ++j) {  
			h[j] = 1;
			t[j] = 0;
		}
		for (register int j = 0, mo = 0; j <= c; ++j, mo = mo + 1 == cost[i] ? 0 : mo + 1) {
			while (h[mo] <= t[mo] && j - q[mo][h[mo]] > cost[i] * tot[i]) {  
				++h[mo];
			}
			register int tmp = f[i - 1][j] - j / cost[i] * lim[i];  
			while (h[mo] <= t[mo] && tmp >= f[i - 1][q[mo][t[mo]]] - q[mo][t[mo]] / cost[i] * lim[i]) {
				--t[mo];  
			}
			q[mo][++t[mo]] = j;  
			f[i][j] = f[i - 1][q[mo][h[mo]]] - q[mo][h[mo]] / cost[i] * lim[i] + j / cost[i] * lim[i];
		}
	}
	/*for (int j = 1; j <= c; ++j) {
		f[i][j] = max(f[i][j], f[i][j - 1]);  
	}*/
	//cout << f[1][4] << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> testcase;
	for (; testcase; --testcase) {
		cin >> n >> m >> p;
		assert(p <= 50000);	
		for (int i = 1; i <= n; ++i) {
			cin >> val[i] >> size[i] >> sum[i];
		}
		dp1(p + 200);// cout << cc << endl;
		for (int i = 1; i <= m; ++i) {
			cin >> lim[i] >> cost[i] >> tot[i];
		}
		dp2(); //cout << cc << endl;
		//return 0;
		int need = dp[n][p];
		for (int i = 0; i <= 50000; ++i) {
			if (f[m][i] >= need) {
				cout << i << endl;
				need = -1;
				break;
			}
		}
		if (need > 0) {
			cout << "TAT" << endl;
		}
	}
}
