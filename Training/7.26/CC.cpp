#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
LL N, s[111111];

int main() {
	cin >> N;
	s[1] = 1;
	s[2] = 2;
	s[3] = 2;
	long long ans = 5;
	int i = 3, j = 1;
	for (int k = 4; k <= N; ++k) {
//cout << "pointer: " << k << " " << i << " " << j << endl;
		s[k] = i;
		if (++j > s[i]) {
			++i;
			j = 1;
		}
		ans += s[k];
	}
	cout << ans << endl;
	cout << s[N] << endl;
	/*for (int i = 1; i <= N; ++i) {
	 	cout << i << " " << s[i] << endl;
	}*/
}
