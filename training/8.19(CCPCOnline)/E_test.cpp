#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
int testcase, n;

int main() {
	cin >> testcase;
	for (; testcase; --testcase) {
		scanf("%d", &n);
		LL ans = -1;
		if (n == 1 || n == 2) {
			ans = 4;
		} else {
			ans = ((n + 5) * 2LL + 2) / 3;
		}
		printf("%d\n", (int)ans);
	}
}
