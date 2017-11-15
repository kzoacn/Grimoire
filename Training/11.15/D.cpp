#include <bits/stdc++.h>
using namespace std;

inline void add(int x, int y) {
	ans.push_back({x, y});
}

/*inline void print(int x, int y) {
	printf("%d %d %d\n", x + y, x, y);
}*/

inline void solve(int n, int k) {
	int m = n * k;
	if (n % 2 == 0) {
		add(n / 2 * k, n / 2 * k);
		solve(n / 2, k);
		return;
	}
	int f1 = 
	/*int f1 = f[m / 2] + 2], f2 = f[m];
	if (f1 < f2) {
		add(m / 2, m / 2 + 1);
		add(m / 2 + 1, 1);
		solve(1, m / 2);
		return;
	} else {
		solve()
		return;
	}

	if (from[n] == 0) {
		if (n % 2 == 0) {
			print(n / 2 * k, n / 2 * k);
		} else {
			print(n / 2 * k, (n / 2 + 1) * k);
			printf("")
		}
	}*/
}

int main() {
	for (int i = 1; i < N; ++i) {
		for (int j = i; j < N; j += i) {
			d[j].push_back(i);
		}
	}
	f[1] = 0;
	for (int i = 2; i < N; ++i) {
		if (i % 2 == 0) {
			f[i] = f[i / 2] + 1;
		} else {
			f[i] = f[i / 2] + 2;
		}
		for (auto u : d[i]) {
			if (f[u] + f[i / u] < f[i]) {
				from[i] = u;
				f[i] = f[u] + f[i / u];
			}
		}
	}
	
	cin >> cs;
	for (; cs; --cs) {
		int n;
		for (int i = 0; i < 4; ++i) {
			int x;
			scanf("%d", &x);
			n += 1 << x;
		}
		//cout << f[n] << endl;
		solve(n, 1);
		for (auto u : ans) {
			cout << u.first << " " << u.second << "\n";
		}
		cout.flush();
	}
}
