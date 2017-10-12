#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <cmath>
#include <algorithm>
#include <stack>

using namespace std;

int l, n, cnt, testcase;
const int MAXN = 10000000 + 10;
char s[MAXN], f[MAXN];
int a[MAXN];
map<string, int> M;
stack<int> Q;
vector<string> vec;
vector<string> ans;
vector<vector<int> > pos;

inline void space(int &i) {
	while (i <= l && s[i] == ' ') {
		++i;
	}
}

inline bool islam(int &i) {
	if (s[i] == 'l' && s[i + 1] == 'a' && s[i + 2] == 'm'
		&& s[i + 3] == 'b' && s[i + 4] == 'd' && s[i + 5] == 'a') {
		i += 6;
		return true;
	}
	return false;
}
#include <iostream>

inline int get_name(int &i) {
	space(i);
	string str = "";
	for (; i <= l && ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || s[i] == '-'); ++i) {
		str += s[i];
	}
	map<string, int>::iterator it = M.find(str);
	if (it != M.end()) {
		return it -> second;
	} else {
		vec.push_back(str);
		pos.push_back(vector<int>());
		return M[str] = ++cnt;
	}
}

inline void get_a() {
	n = cnt = 0;
	vector<string>().swap(vec);
	vec.push_back(string());
	vector<vector<int> >().swap(pos);
	pos.push_back(vector<int>());
	while (!Q.empty()) {
		Q.pop();
	}
	int i = 1;
	while (i <= l) {
	//cout << i << " " << l << " " << s[i] << endl;
		space(i);
		if (i > l) {
			break;
		}
		if (s[i] == '(') {
			a[++n] = 0;
			Q.push(n);
			f[n] = 1;
			++i;
			continue;
		}
		if (s[i] == ')') {
	//cout << i << " " << l << " " << s[i] << " " << Q.endl;
			a[++n] = 0;
			a[Q.top()] = n;
			Q.pop();
			f[n] = 2;
			++i;
			continue;
		}
		if (i + 5 <= l && islam(i)) {
			space(i);
			++i;
			int now = get_name(i);
			a[++n] = -now;
			pos[now].push_back(n);
			f[n] = 0;
			space(i);
			++i;
			continue;
		}
		int now = get_name(i);
		a[++n] = now;
		f[n] = 0;
		pos[now].push_back(n);
	}
//cout << cnt << endl;
/*cout << n << " - ";
for (int i = 1; i <= n; ++i) cout << a[i] << " ";
cout << endl;
cout << endl;*/
}

int main() {
	scanf("%d", &testcase);
	for (int cs = 1; cs <= testcase; ++cs) {
		scanf(" ");
		gets(s + 1);
		l = strlen(s + 1);
		//cerr << s + 1 << endl;
		
		map<string, int>().swap(M);
		get_a();
		
		//for (auto u : pos[2]) cout << u << " "; cout << endl;
		vector<string>().swap(ans);
		for (int i = 1, j; i <= cnt; ++i) {
			j = 0;
			while (j < n) {
			//cout << i << " " << j << endl;
			//if (j == 1) return 0;
				vector<int>::iterator it = upper_bound(pos[i].begin(), pos[i].end(), j);
				if (it == pos[i].end()) {
					break;
				}
				j = *it;
				//cout << (*it) << endl;
				if (a[j] > 0) {
					ans.push_back(vec[i]);
					break;
				}
				if (f[j + 1] == 1) {
					j = a[j + 1];
				} else {
					++j;
				}
			}
		}
		sort(ans.begin(), ans.end());
		
		printf("Case #%d:", cs);
		for (auto u : ans) {
			putchar(' ');
			for (auto c : u) {
				putchar(c);
			}
		}
		puts("");
	}
}
