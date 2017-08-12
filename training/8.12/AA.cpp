#include <bits/stdc++.h>

using namespace std;

int n, m;

string word[100005], pre, suf;

bool isPre(string a, string b) {
	if (a.length() > b.length()) return 0;
	for (int i = 0; i < a.length(); ++i)
		if (a[i] != b[i]) return 0;
	return 1;
}

bool isSuf(string a, string b) {
	if (a.length() > b.length()) return 0;
	for (int i = 0; i < a.length(); ++i)
		if (a[a.length() - i - 1] != b[b.length() - i - 1]) return 0;
	return 1;
}

int main() {
	int caseCnt; cin >> caseCnt;
	for (int kase = 1; kase <= caseCnt; ++kase) {
		cin >> n >> m;
		for (int i = 1; i <= n; ++i) cin >> word[i];
		
		while (m--) {
			cin >> pre >> suf;
			
			int ans = 0;
			for (int i = 1; i <= n; ++i) {
				if (pre.length() + suf.length() <= word[i].length() && isPre(pre, word[i]) && isSuf(suf, word[i])) ++ans;
			}
			
			cout << ans << endl;
		}
	}
	
	return 0;
}
