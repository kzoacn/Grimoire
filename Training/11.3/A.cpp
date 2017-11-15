#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int MAXN = 1005, MAXM = 10005, MAXD = 10000;
const LL INF = 0x3f3f3f3f3f3f3f3fLL;

struct Addiction {
	string name;
	int strength;
	
	bool operator < (const Addiction &rhs) const {
		return strength < rhs.strength;
	}
} addi[MAXN];

int n, d;
LL dp[MAXM];

vector<string> Ans;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	cin >> n >> d;
	for (int i = 1; i <= n; ++i)
		cin >> addi[i].name >> addi[i].strength;
	
	sort(addi + 1, addi + n + 1);
	
	memset(dp, 0x3f, sizeof dp);
	dp[0] = 0;
	
	int last = 0; LL ans = 0;
	for (int i = 1; i <= n; ++i) {
		LL tmp = INF;
		for (int j = addi[i].strength; j >= addi[i].strength - d && j >= 0; --j)
			tmp = min(tmp, dp[j] + 1);
		if (tmp == INF) break;
		ans += tmp;
		last = i;
		for (int j = MAXD; j >= addi[i].strength; --j)
			dp[j] = min(dp[j], dp[j - addi[i].strength] + tmp);
	}
	
	cout << last << " " << ans << endl;
	for (int i = 1; i <= last; ++i)
		Ans.push_back(addi[i].name);
	
	sort(Ans.begin(), Ans.end());
	for (string i: Ans)
		cout << i << endl;
	
	return 0;
}
