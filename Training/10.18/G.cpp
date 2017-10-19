#include <bits/stdc++.h>

namespace SegTree {
	int tag[300005 << 2];
	
	void init() {
		memset(tag, 0, sizeof tag);
	}
	
	void modify(int k, int l ,int r, int L, int R, int val) {
		if (L <= l && r <= R) {
			tag[k] = std::max(tag[k], val);
			return;
		}
		int mid = (l + r) >> 1;
		if (L <= mid) modify(k << 1, l, mid, L, R, val);
		if (mid < R) modify(k << 1 | 1, mid + 1, r, L, R, val);
	}
	
	int query(int k, int l, int r, int pos) {
		if (l == r) return tag[k];
		int mid = (l + r) >> 1;
		if (pos <= mid) return std::max(tag[k], query(k << 1, l, mid, pos));
		return std::max(tag[k], query(k << 1 | 1, mid + 1, r, pos));
	}
}

namespace ACAM {
	int to[300005][26], fail[300005]/*father*/, tot;
	int root;
	
	int newnode() {
		++tot;
		memset(to[tot], 0, sizeof to[tot]);
		fail[tot] = 0;
		return tot;
	}
	
	void init() {
		tot = 0;
		root = newnode();
	}
	
	void insert(int &k, char *s) {
		if (!k) k = newnode();
		if (!*s) return;
		insert(to[k][*s - 'a'], s + 1);
	}
	
	int head[300005], nxt[300005], eto[300005], ed;
	int dfn[300005], dfn_tot, sz[300005];
	
	void AddEdge(int u, int v) {
		nxt[++ed] = head[u]; head[u] = ed; eto[ed] = v;
	}
	
	void DFS(int now) {
		dfn[now] = ++dfn_tot;
		sz[now] = 1;
		for (int i = head[now]; i; i = nxt[i]) {
			DFS(eto[i]);
			sz[now] += sz[eto[i]];
		}
	}
	
	void build() {
		static std::queue<int> que;
		
		memset(head, 0, sizeof head); ed = 0;
		dfn_tot = 0;
		
		for (int i = 0; i < 26; ++i) {
			if (to[root][i]) {
				fail[to[root][i]] = root;
				AddEdge(root, to[root][i]);
				que.push(to[root][i]);
			}
			else to[root][i] = root;
		}
		while (!que.empty()) {
			int now = que.front(); que.pop();
			for (int i = 0; i < 26; ++i) {
				if (to[now][i]) {
					fail[to[now][i]] = to[fail[now]][i];
					AddEdge(fail[to[now][i]], to[now][i]);
					que.push(to[now][i]);
				}
				else to[now][i] = to[fail[now]][i];
			}
		}
		
		DFS(1);
	}
	
	int query(std::string s) {
		int res = 0, k = root;
		for (int i = 0; i <= s.length(); ++i) {
			res = std::max(res, SegTree::query(1, 1, tot, dfn[k]));
			if (i == s.length()) break;
			k = to[k][s[i] - 'a'];
		}
		return res;
	}
	
	void add(std::string s, int w) {
		int k = root;
		for (char c: s) {
			k = to[k][c - 'a'];
		}
		SegTree::modify(1, 1, tot, dfn[k], dfn[k] + sz[k] - 1, w);
	}
}

int n, w[20005];
std::string s[20005];

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		static char ss[300005];
		
		ACAM::init();
		
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%s%d", ss, w + i);
			s[i] = std::string(ss);
			ACAM::insert(ACAM::root, ss);
		}
		
		ACAM::build();
		SegTree::init();
		
		int ans = 0;
		for (int i = 1; i <= n; ++i) {
			static int tmp;
			ans = std::max(ans, tmp = w[i] + ACAM::query(s[i]));
			ACAM::add(s[i], tmp);
		}
		
		printf("Case #%d: %d\n", kase, ans);
	}
	
	return 0;
}
