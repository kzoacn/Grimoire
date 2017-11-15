#include <bits/stdc++.h>
using namespace std;

int main() {
	cout << 1 << endl;
	int n = 100;
	cout << n << endl;
	for (int i = 1; i <= n; ++i) {
		int l = rand() % 1 + 1, r = rand() % 1 + 1;
		if (l > r) {
			cout << r << " " << l << endl;
		} else {
			cout << l << " " << r << endl;
		}
	}
}
