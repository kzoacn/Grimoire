#include <bits/stdc++.h>
using namespace std;

int main() {
	srand(time(0));
	int n = 70, m = 40;
	cout << n << " " << m << endl;
	for (int i = 1; i <= n; ++i ) {
		cout << rand() % 1000000000 + 1 << " " << rand() % 1000 + 1 << endl;
	}
}
