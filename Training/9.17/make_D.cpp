#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

int main() {
	srand(time(0) ^ getpid());
	int n = 1;
	cout << n << endl;
	for (int i = 1; i <= n; ++i) {
		cout << rand() % 100000 + 1 << endl;
	}
}
