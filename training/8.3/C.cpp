#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
int testcase, a, b, c, d, e, m;

int main() {
	cin >> testcase;
	for (int cs = 1; cs <= testcase; ++cs) {
		scanf("%d%d%d%d%d%d", &a, &b, &c, &d, &e, &m);
		LL s = a + b + c + d + e;
		if (s >= m) {
			printf("Case #%d: %d\n", cs, 0);
			continue;
		}
		if (s <= 0) {
			printf("Case #%d: %d\n", cs, -1);
			continue;
		}
		for (int i = 1; i <= 30; ++i) {
			s *= 2;
			if (s >= 1LL * m) {
				printf("Case #%d: %d\n", cs, i);
				break;
			}
		}
	}
}
