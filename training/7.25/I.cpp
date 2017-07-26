#include <bits/stdc++.h>
using namespace std;

int A, B, a, b;

inline int solve(int A, int B, int a, int b) {
	int ans = (A / a) * (B / b);
	if (B % b) {
		int n = A / a;
		int m = b / (B % b);
		ans += (n + m - 1) / m;
	}
	if (A % a) {
		int n = (B + b - 1) / b;
		int m = a / (A % a);
		ans += (n + m - 1) / m;
	}
	return ans;
}

int main() {
	cin >> A >> B >> a >> b;
	int ans = min(solve(A, B, a, b), solve(B, A, b, a));
	cout << ans << endl;
}
