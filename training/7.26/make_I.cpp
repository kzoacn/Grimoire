#include <bits/stdc++.h>
using namespace std;

int main() {
	srand(time(0));
	int cs = 10;
	cout << cs << endl;
	for (; cs; --cs) {
		int n = 200, m = 200, p = 50000;
		cout << n << " " << m << " " << p << endl;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < 3; ++j) {
				cout << rand() % 100 + 1 << " ";
			}
			cout << endl;
		}
		for (int i = 1; i <= m; ++i) {
			for (int j = 0; j < 3; ++j) {
				cout << rand() % 100 + 1 << " ";
			}
			cout << endl;
		}
	}
}
