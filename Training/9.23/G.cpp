#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

LL f(LL x) {
	return x % 2 == 0 ? x + 1 : x + 1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	LL n, m;
	while (cin >> n >> m) {
		LL g = __gcd(n - 1, m - 1);
		LL a = (n - 1) / g, b = (m - 1) / g;
		LL ans = (g - 1) * a * b + f(a) + f(b) - 2;
		cout << ans << "\n";
	}
}
