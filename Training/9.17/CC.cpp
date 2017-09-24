#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 10;
string s, now;
int cs, n, cnt, head, tail, root;
int seq[MAXN], f[MAXN], exist[MAXN];

struct Trie {
	int c[26], fail, from, mark;
} tr[MAXN];

inline void clear(int i) {
	memset(tr[i].c, 0, sizeof(tr[i].c));
	tr[i].fail = tr[i].from = tr[i].mark = 0;
}

inline int add_string(int id, const string &s) {
	int u = root;
	for (auto ch : s) {
		if (tr[u].c[ch - 'a']) {
			u = tr[u].c[ch - 'a'];
		} else {
			u = tr[u].c[ch - 'a'] = ++cnt;
			clear(cnt);
		}
	}
	if (!tr[u].from) {
		tr[u].from = id;
		return 1;
	} else {
		return 0;
	}
}

inline void build_fail() {
	head = 1, tail = 0;
	for (int i = 0; i < 26; ++i) {
		if (tr[1].c[i]) {
			seq[++tail] = tr[1].c[i];
			tr[tr[1].c[i]].fail = 1;
		} else {
			tr[1].c[i] = 1;
		}
	}
	for (; head <= tail; ++head) {
		int u = seq[head];
		for (int i = 0; i < 26; ++i) {
			if (tr[u].c[i]) {
				tr[tr[u].c[i]].fail = tr[tr[u].fail].c[i];
				seq[++tail] = tr[u].c[i];
			} else {
				tr[u].c[i] = tr[tr[u].fail].c[i];
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	cin >> cs;
	for (; cs; --cs) {
		root = 1;
		cnt = 1;
		clear(1);
		
		cin >> n;
		string().swap(s);
		string().swap(now);
		for (int i = 1; i <= n; ++i) {
			cin >> now;
			if (now.length() > s.length()) {
				s = now;
			}
			exist[i] = add_string(i, now);
			f[i] = 0;
		}
		//cout << cnt << endl;
		
		build_fail();
		int u = root;
		for (auto ch : s) {
			u = tr[u].c[ch - 'a'];
			//cerr << u << endl;
			tr[u].mark = 1;
		}
		//cerr << tail << endl;
		for (int i = tail; i; --i) {
			int u = seq[i];
			tr[tr[u].fail].mark |= tr[u].mark;
		}
		//cerr << cnt << endl;
		//cerr << "adsf" << endl;
		//return 0;
		for (int i = 1; i <= cnt; ++i) {
			int u = i;
		//cerr << tr[u].from << " " << tr[u].mark << " " << u << endl;
			if (tr[u].from && tr[u].mark) {
				f[tr[u].from] = 1;
			}
		}//return 0;
		bool flag = true;
		///cerr << n << endl;
		for (int i = 1; i <= n; ++i) {
		//cerr << i << endl;
		//cerr << exist[i] << " " << f[i] << endl;
			if (exist[i] && !f[i]) {
				flag = false;
			}
		}
		/*return 0;*/
		if (flag) {
			cout << s << "\n";
		} else {
			cout << "No\n";
		}
	}
}
