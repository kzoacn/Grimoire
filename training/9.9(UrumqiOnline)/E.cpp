#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

LL a[] = {
1,
49,
1681,
57121,
1940449,
65918161,
2239277041,
76069501249,
2584123765441,
87784138523761,
2982076586042449,
8,
288,
9800,
332928,
11309768,
384199200,
13051463048,
443365544448,
15061377048200,
511643454094368,
17380816062160328
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	int n = 22;
	sort(a, a + n);
	int testcase;
	cin >> testcase;
	for (int cs = 1; cs <= testcase; ++cs) {
		LL N;
		cin >> N;
		LL r = -1;
		for (int i = 0; i < n; ++i) {
			if (a[i] >= N) {
				r = a[i];
				break;
			}
		}
		cout << "Case #" << cs << ": " << r << "\n";
	}
}
