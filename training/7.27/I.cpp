#include <bits/stdc++.h>
using namespace std;

//priority_queue<pair<int, string>, vector<pair<int, string>, greater<pair<int, string> > > Q;
const int MAXN = 2333;
vector<string> vec[MAXN];
set<pair<int, string> > S;
map<string, int> M;
string s;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	int fir = 0;
	int day = 0;
	string prev("<text>"), last("</text>");
	while (cin >> s) {
	//cout << s << endl;
		if (s == prev) {
			++day;
			vec[day].clear();
			continue;
		}
		if (s == last) {
			continue;
		}
		if (s.size() < 4) {
			continue;
		}
		if (s[0] != '<') {
			vec[day].push_back(s);
			if (M.find(s) == M.end()) {
				M[s] = 1;
				S.insert(make_pair(-1, s));
			} else {
				int tmp = ++M[s];
				S.erase(make_pair(-(tmp - 1), s));
				S.insert(make_pair(-tmp, s));
			}
		} else {
//cout << s << endl;
			while (day - fir > 7) {
				++fir;
				for (auto u : vec[fir]) {
					if (M[u] == 1) {
						M.erase(u);
						S.erase(make_pair(-1, u));
					} else {
						int tmp = --M[u];
						S.erase(make_pair(-(tmp + 1), u));
						S.insert(make_pair(-tmp, u));
					}
				}
			}
			
			int number;
			cin >> number;
			cin >> s;
			cout << "<top " << number << ">\n";
//cout << S.size() << " " << number << endl;
			if ((int)S.size() <= number) {
				for (auto u : S) {
					cout << u.second << " " << -(u.first) << "\n";
				}
			} else {
				int occur = 0;
				auto it = S.begin();
				for (; number; --number) {
					cout << it -> second << " " << -(it -> first) << "\n";
					occur = it -> first;
					++it;
				}
				while (it != S.end() && it -> first == occur) {
					cout << it -> second << " " << -(it -> first) << "\n";
					++it;
				}
			}
			cout << "</top>\n";
		}
	}
}
