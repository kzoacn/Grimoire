#include <bits/stdc++.h>

struct Peo {
	std::string Name;
	int t, v;
	
	Peo() {}
	
	bool operator < (const Peo &rhs) const {
		return v == rhs.v ? t < rhs.t : v > rhs.v;
	}
	
	void scan(int tt) {
		static char s[205];
		
		scanf("%s%d", s, &v); Name = std::string(s);
		t = tt;
	}
} peo[150005]; std::set<Peo> st;

std::string ans[150005];

struct Event {
	int t, p;
	
	bool operator < (const Event &rhs) const {
		return t < rhs.t;
	}
	
	void scan() {
		scanf("%d%d", &t, &p);
	}
} event[150005];

int n, m, q;

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d%d%d", &n, &m, &q);
		for (int i = 1; i <= n; ++i) {
			peo[i].scan(i);
		}
		for (int i = 1; i <= m; ++i) event[i].scan();
		std::sort(event + 1, event + m + 1);
		
		st.clear();
		int cur = 1, tot = 0;
		for (int t, p, i = 1; i <= m; ++i) {
			t = event[i].t, p = event[i].p;
			while (cur <= t && cur <= n) {
				st.insert(peo[cur++]);
			}
			while (p-- && !st.empty()) {
				ans[++tot] = st.begin()->Name;
				st.erase(st.begin());
			}
		}
//		printf("%d\n", tot);
		while (cur <= n) {
			st.insert(peo[cur++]);
		}
		while (!st.empty()) {
			ans[++tot] = st.begin()->Name;
			st.erase(st.begin());
		}
		int x;
		while (q--) {
			scanf("%d", &x);
			printf("%s%c", ans[x].c_str(), " \n"[q == 0]);
		}
	}
	
	return 0;
}
