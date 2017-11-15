#include <bits/stdc++.h>

using namespace std;

const int MAXN = 400 + 5;

const int INF = 0x3f3f3f3f;

int n, k, W;
int w[MAXN][MAXN], c[MAXN][MAXN];

int permu[(1 << 10) + 5];

int dp[MAXN][MAXN];
vector<pair<int, int> > moveSeq;

void DP(int S) {
	memset(dp, 0x3f, sizeof dp);
	
//	if (!(S & c[1][1])) return;
	
	dp[0][1] = dp[1][0] = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			if (!(c[i][j] & S)) continue;
			dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]) + w[i][j], INF);
		}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> n >> k >> W;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			cin >> w[i][j];
	
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			cin >> c[i][j];
			c[i][j] = 1 << (c[i][j] - 1);
		}
	
	for (int i = 1; i < (1 << k); ++i)
		permu[++*permu] = i;
	
	sort(permu + 1, permu + *permu + 1, [](int x, int y){return __builtin_popcount(x) < __builtin_popcount(y);});
	
	int ans = -1;
	
	for (int i = 1; i <= *permu; ++i) {
		int S = permu[i];
		
		
		DP(S);
		
//		cout << S << " " << dp[n][n] << endl;
		
		if (dp[n][n] <= W) {
			ans = __builtin_popcount(S);
			int x = n, y = n;
			moveSeq.push_back(make_pair(x, y));
			while (x != 1 || y != 1) {
				if (x > 1 && (S & c[x - 1][y]) && dp[x][y] - w[x][y] == dp[x - 1][y])
					moveSeq.push_back(make_pair(--x, y));
				else if (y > 1 && (S & c[x][y - 1]) && dp[x][y] - w[x][y] == dp[x][y - 1])
					moveSeq.push_back(make_pair(x, --y));
			}
			break;
		}
	}
	
	if (ans == -1)
		return cout << "-1" << endl, 0;
	
	cout << ans << endl;
	for (int i = moveSeq.size() - 1; i >= 0; --i)
		cout << moveSeq[i].first << " " << moveSeq[i].second << " \n"[i == 0];
	
	return 0;
}
