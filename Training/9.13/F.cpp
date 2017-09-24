#include <bits/stdc++.h>

int n;
char s[100005];

std::string ss[100005];

namespace ACAM {
	int to[100005][26], fail[100005], depth[100005], node_cnt;
	
	int root;
	
	int newnode(int dep) {
		++node_cnt;
		memset(to[node_cnt], 0, sizeof to[node_cnt]);
		fail[node_cnt] = 0;
		depth[node_cnt] = dep;
		return node_cnt;
	}
	
	void init() {
		node_cnt = 0;
		root = 0;
	}
	
	void insert(int &now, char *s, int dep) {
		if (!now) now = newnode(dep);
		if (!*s) return;
		insert(to[now][*s - 'a'], s + 1, dep + 1);
	}
	
	void build() {
		static std::queue<int> que;
		
		fail[root] = root;
		for (int i = 0; i < 26; ++i) {
			if (to[root][i]) {
				fail[to[root][i]] = root;
				que.push(to[root][i]);
			}
			else to[root][i] = root;
		}
		while (!que.empty()) {
			int now = que.front(); que.pop();
			for (int i = 0; i < 26; ++i) {
				if (to[now][i]) {
					fail[to[now][i]] = to[fail[now]][i];
					que.push(to[now][i]);
				}
				else {
					to[now][i] = to[fail[now]][i];
				}
			}
		}
	}
}

namespace SAM {
	int to[100005 << 1][26], parent[100005 << 1], step[100005 << 1], node_cnt;
	int sam_len;
	
	int root[100005], np;
	
	int newnode(int STEP) {
		++node_cnt;
		memset(to[node_cnt], 0, sizeof to[node_cnt]);
		parent[node_cnt] = 0;
		step[node_cnt] = STEP;
		return node_cnt;
	}
	
	void init() {
		node_cnt = 0;
	}
	
	void newsam(int t) {
		root[t] = np = newnode(sam_len = 0);
	}
	
	void extend(int t, char ch) {
		int x = ch - 'a';
		int last = np; np = newnode(++sam_len);
		for (; last && !to[last][x]; last = parent[last])
			to[last][x] = np;
		if (!last) parent[np] = root[t];
		else {
			int q = to[last][x];
			if (step[q] == step[last] + 1) parent[np] = q;
			else {
				int nq = newnode(step[last] + 1);
				memcpy(to[nq], to[q], sizeof to[q]);
				parent[nq] = parent[q];
				parent[q] = parent[np] = nq;
				for (; last && to[last][x] == q; last = parent[last])
					to[last][x] = nq;
			}
		}
	}
}

int solve(int u, int v) {
	int ans = 0;
	
	int acam_now = ACAM::root;
	int sam_now = SAM::root[u];
	int sam_len = 0;
	
	for (char ch: ss[v]) {
		int x = ch - 'a';
		acam_now = ACAM::to[acam_now][x];
		while (SAM::parent[sam_now] && !SAM::to[sam_now][x]) {
			sam_now = SAM::parent[sam_now];
			sam_len = std::min(sam_len, SAM::step[sam_now]);
		}
		if (SAM::to[sam_now][x]) {
			sam_now = SAM::to[sam_now][x];
			++sam_len;
		}
		
//		std::cerr << ACAM::depth[acam_now] << " " << SAM::step[sam_now] << " " << sam_len << std::endl;
		
		while (acam_now && ACAM::depth[acam_now] > sam_len)
			acam_now = ACAM::fail[acam_now];
		
		ans = std::max(ans, ACAM::depth[acam_now]);
	}
	return ans;
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		ACAM::init();
		SAM::init();
		
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%s", s);
			ss[i] = std::string(s);
			ACAM::insert(ACAM::root, s, 0);
			SAM::newsam(i);
			for (char *c = s; *c; ++c)
				SAM::extend(i, *c);
		}
		
		ACAM::build();
		
		int m; scanf("%d", &m);
		for (int u, v; m--; ) {
			scanf("%d%d", &u, &v);
			printf("%d\n", solve(u, v));
		}
	}
	
	return 0;
}
