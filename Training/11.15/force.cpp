#include <bits/stdc++.h>
using namespace std;

inline int dfs(set<int> &S) {
	if (S.size() == 1 && *(S.begin()) == 1) {
		return 0;
	}
//cout << S.size() << " " << endl;
	set<int> tmp = S;
	int ans = 1e9;
	for (auto u : tmp) {
		for (int i = 1; i < u; ++i) {
			S = tmp;
			S.erase(u);
			S.insert(i);
			S.insert(u - i);
			ans = min(ans, dfs(S) + 1);
		}
	}
	return ans;
}

set<int> S;
int n;

int main() {
	for (n = 1; n <= 20; ++n) {
		S.clear();
		S.insert(n);
		cout << n << " " << dfs(S) << endl;
	}
}
