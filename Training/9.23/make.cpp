#include <bits/stdc++.h>
using namespace std;

int a[1111111];

int main() {
	srand(time(0));
	int cs = 1, n = 100000;
	cout << cs << endl;
	for (; cs; --cs) {
		for (int i = 1; i <= n; ++i) {
			a[i] = i;
		}
		random_shuffle(a + 1, a + n + 1);
		cout << n << endl;
		for (int i = 1; i <= n; ++i) {
			printf("%d ", a[i]);
		}
		cout << endl;
	}
}
