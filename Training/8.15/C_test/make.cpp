#include <bits/stdc++.h>
using namespace std;

int main() {
	int n = 40;
	cout << 1 << endl;
	cout << n << endl;
	for (int i = 0; i < n; ++i) {
		int tp = i & 1;
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < n; ++k) {
				cout << 1;
			}
			cout << endl;
		}
	}
}
