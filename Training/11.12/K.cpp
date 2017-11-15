#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef long double LD;

const int MOD = 1e9 + 7;

const int D = 15;
int a[111111], cnt[111111], f[111111];
int n;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	int testcase;
	cin >> testcase;
	for (int cs = 1; cs <= testcase; ++cs) {
		cin >> n;
		for (int i = 1; i <= n; ++i) {
			cin >> a[i];
			cnt[a[i]]++;
		}
		
		for (int i = 0; i < 1 << D; ++i) {
			f[i] = 0;
		}
		for (int i = 1; i < 1 << D; ++i) {
			int x = i & -i;
			f[i] = f[i ^ x];
//cout << i << " " << f[i] << endl;
			int tmp = i ^ x;
			for (int j = tmp; ; j = tmp & (j - 1)) {
				f[i] = (f[i] + 1LL * cnt[j ^ x] * (f[tmp ^ j] + 1)) % MOD;
				if (j == 0) {
					break;
				}
			}
//cout << i << " " << f[i] << endl;
		}
		
		/*LL ans = 0;
		for (int i = 1; i < 1 << D; ++i) {
			ans = ans + f[i];
		}*/
		LL ans = (f[(1 << D) - 1] - n) % MOD;
		ans = (ans + MOD) % MOD;
		
		cout << "Case #" << cs << ": " << ans << endl;
		for (int i = 1; i <= n; ++i) {
			cnt[a[i]] = 0;
		}
	}
}
