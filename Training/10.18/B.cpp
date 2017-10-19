#include <bits/stdc++.h>

using namespace std;

int LOG2(long long x) {
	for (int i = 0; i <= 60; ++i)
		if ((1ll << i) > x) return i;
	
	assert(0);
	return -1;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	int caseCnt; cin >> caseCnt;
	for (int kase = 1; kase <= caseCnt; ++kase) {
		static int n, m, k;
		
		cin >> n >> m >> k;
		
		cout << "Case #" << kase << ": " << 1ll * n * m * k - 1 << " " << LOG2(n - 1) + LOG2(m - 1) + LOG2(k - 1) << endl;
//		cout << "Case #" << kase << ": " << 1ll * n * m * k - 1 << " " << LOG2(1ll * n * m * k - 1) << endl;
	}
	
	return 0;
}
