#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL INF = 1e18;
int testcase, l, r;
int a[111];
LL D;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> testcase;
	for (int cs = 1; cs <= testcase; ++cs) {
		cin >> D >> l >> r;
		for (int i = 1; i <= 32; ++i) a[i] = 0;
		int n = 0;
		for (; D; D >>= 1) {
			a[++n] = D & 1;
		}
		n = 32;
		/*if (ts >= l && ts <= r) {
			cout << "Case #" << cs << ": " << 
		}*/
		
		LL ans = INF;
		int s = 0;
		LL now = 0;
		for (int i = n; i; --i) {
			if (a[i] == 0 && s + 1 <= r) {
				LL temp = now * 2 + 1;
				int left = max(0, l - (s + 1));
				for (int j = i - 1; j > left; --j) {
					temp = temp * 2;
				}
				for (int j = left; j; --j) {
					temp = temp * 2 + 1;
				}
				if (temp < ans) {
					ans = temp;
				}
				//cout << i << " " << ans << endl;
			}
			s += a[i];
			now = now * 2 + a[i];
		}
		/*if (s >= l && s <= r) {
			ans = min(ans, now);
		}*/
		cout << "Case #" << cs << ": " << ans << endl;
	}
}
