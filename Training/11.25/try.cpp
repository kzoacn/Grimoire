#include <bits/stdc++.h>
using namespace std;

double a;

int main() {
	cin >> a;
	for (int T = 1; T <= 1e3; ++T) {
		a = (a > 0) ? 1 - 2 * a : (-2 * a - 1);
		cout << T << " " << a << endl;
	}
}
