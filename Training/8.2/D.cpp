#include <bits/stdc++.h>
using namespace std;

int X, Y, cs, a;

inline bool check(int x, int y, int a) {
	if (x % a > 1) {
		return false;
	}
	int l = y - 1 + x % a;
//cout << l << endl;
	if (l % a > 1) {
		return false;
	}
//cout << l << endl;
	l = x - 1 + l % a;
	if (l % a > 1) {
		return false;
	}
//cout << l << endl;
	l = y - 2 + l % a;
	return l % a == 0;
}

int main() {
	freopen("D.in", "r", stdin);
	
	cin >> X >> Y >> cs;
	//cout << check(6, 5, 3) << endl;return 0;
	for (; cs; --cs) {
		scanf("%d", &a);
		if (check(X, Y, a) || check(Y, X, a)) {
			puts("YES");
		} else {
			puts("NO");
		}
	}
}
