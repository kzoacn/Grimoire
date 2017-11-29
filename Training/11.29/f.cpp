#include <bits/stdc++.h>
using namespace std;

int n, m;

string nine(int n) {
	string s = "";
	for (int i = 0; i < n; ++i) {
		s += "9";
	}
	return s;
}
int main() {
	freopen("continued.in", "r", stdin);
	freopen("continued.out", "w", stdout);
	
	cin >> n >> m;
	vector<string> ans;
	if (n < m) {
		string tmp = "";
		for (int i = 0; i < m - n; ++i) {
			tmp += "9";
		}
		ans.push_back("0");
		ans.push_back(tmp);
		ans.push_back("1");
		tmp = "";
		for (int i = 0; i < n; ++i) {
			tmp += "9";
		}
		ans.push_back(tmp);
	} else {
		string tmp = "";
		for (int i = 0; i <= n - m; ++i) {
			tmp += "0";
		}
		for (int i = n - m; i >= 0; i -= m) {
			tmp[i] = '1';
		}
		reverse(tmp.begin(), tmp.end());
		ans.push_back(tmp);
		int k = n % m;
		tmp = nine(m - k);
		ans.push_back(tmp);
		if (k) {
			ans.push_back("1");
			tmp = nine(k);
			ans.push_back(tmp);
		}
	}
	
	cout << (int)ans.size() - 1 << endl;
	for (auto u : ans) {
		cout << u << " ";
	}
	cout << endl;
}
