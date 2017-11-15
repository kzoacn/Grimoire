#include <bits/stdc++.h>

using namespace std;

const char unknown[100] = "Let's go to the library!!";

map<string, int> ansSet;
map<int, vector<string> > invAnsSet;

int n, m;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	int caseCnt; cin >> caseCnt;
	for (int kase = 1; kase <= caseCnt; ++kase) {
		static string tmp;
		
		ansSet.clear();
		invAnsSet.clear();
		
		cin >> n >> m;
		int c; cin >> c;
		for (int i = 1; i <= c; ++i) {
			cin >> tmp;
			ansSet.insert(make_pair(tmp, 0));
		}
		
		for (int i = 0; i < m; ++i) {
			cin >> c;
			for (int j = 1; j <= c; ++j) {
				cin >> tmp;
				ansSet[tmp] |= (1 << i);
			}
		}
		
		for (map<string, int>::iterator it = ansSet.begin(); it != ansSet.end(); ++it) {
			if (!invAnsSet.count(it->second)) invAnsSet.insert(make_pair(it->second, vector<string>()));
			invAnsSet[it->second].push_back(it->first);
		}
		
		for (int i = 1; i <= n; ++i) {
			static int x;
			int S = 0;
			for (int j = 0; j < m; ++j) {
				cin >> x;
				S |= (x << j);
			}
			if (!invAnsSet.count(S) || invAnsSet[S].size() != 1u) cout << unknown << endl;
			else cout << invAnsSet[S][0] << endl;
		}
	}
	
	return 0;
}
