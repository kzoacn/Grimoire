#include <bits/stdc++.h>
using namespace std;

int main() {
	srand(time(0));
	int cs = 10;
	cout << cs << endl;
	for (; cs; --cs) {
		int n = 2000, m = 2000;
		cout << n << " " << m << endl;
		for (int i = 1; i <= n; ++i) {
			cout << rand() % 2000 + 1 << " ";
		}
		cout << endl;
		for (int i = 1; i <= m; ++i) {
			cout << rand() % 2000 + 1 << " ";
		}
		cout << endl;
	}
}
