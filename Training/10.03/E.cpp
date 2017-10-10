#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000;
int id[MAXN], val[MAXN], n, Q;
string name[MAXN], s;
map<string, int> M;

inline bool cmp(int p, int q) {
	//p = id[p];
	//q = id[q];
	if (val[p] != val[q]) {
		return val[p] > val[q];
	} else {
		return name[p] < name[q];
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	while (cin >> n, n) {
		M.clear();
		for (int i = 1; i <= n; ++i) {
			cin >> name[i] >> val[i];
			M[name[i]] = val[i];
			id[i] = i;
		}
		
		sort(id + 1, id + n + 1, cmp);
		for (int i = 1; i <= n; ++i) {
			cout << name[id[i]] << " " << val[id[i]] << "\n";
		}
		
		cin >> Q;
		while (Q--) {
			cin >> s;
			int s1 = 0, s2 = 0, v = M[s];
			for (int i = 1; i <= n; ++i) {
				if (val[i] > v) {
					++s1;
				}
				if (val[i] == v && name[i] < s) {
					++s2;
				}
			}
			if (s2) {
				cout << s1 + 1 << " " << s2 + 1 << "\n";
			} else {
				cout << s1 + 1 << "\n";
			}
		}
	}
}
