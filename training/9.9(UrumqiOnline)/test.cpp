#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int main() {
	/*for (int i = 1; i <= 1000000000; ++i) {
		long long n = 1LL * i * (i + 1) / 2;
		long long d = sqrt(n);
		if (d * d == n) {
			cout << i << " " << n << " " << d << endl;
		}
	}*/
	
	for (LL i = 1; i <= 1e9; ++i) {
		LL p = i * 2 - 1;
		LL r = p * p;
		LL q = sqrt((r + 1) / 2);
		if (q * q * 2LL == r + 1) {
			cout << r << endl;
		}
	}
	
	for (LL i = 2; i <= 1e8; ++i) {
		LL q = i * 2 - 1;
		LL r = q * q - 1;
		LL p = sqrt(r / 2);
		if (p * p * 2LL == r) {
			cout << r << endl;
		}
	}
}
