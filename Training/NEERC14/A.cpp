#include <bits/stdc++.h>

using namespace std;

int n, m;

int main() {
	freopen("alter.in", "r", stdin);
	freopen("alter.out", "w", stdout);
	
	cin >> n >> m;
	cout << (n / 2) + (m / 2) << endl;
	for (int i = 2; i <= m; i += 2)
		cout << 1 << " " << i << " " << n << " " << i << endl;
	for (int i = 2; i <= n; i += 2)
		cout << i << " " << 1 << " " << i << " " << m << endl;
	
	return 0;
}
