#include <bits/stdc++.h>

const int MAXN = 3e5 + 5;

int n;
std::vector<int> G[MAXN], sons[MAXN];
int lenfa[MAXN];

void DFS(int now, int fa) {
	bool isLeaf = 1;
	for (int to: G[now]) {
		if (to == fa) continue;
		DFS(to, now);
		sons[now].push_back(sons[to].back() + 1);
		isLeaf = 0;
	}
	if (isLeaf) {
		sons[now].push_back(0);
		return;
	}
	std::sort(sons[now].begin(), sons[now].end());
}

void DFS2(int now, int fa, int tmp) {
	lenfa[now] = tmp;
	for (int to: G[now]) {
		if (to == fa) continue;
		if (sons[now].size() > 1)
			DFS2(to, now, std::max(tmp + 1, sons[now][sons[now].size() - 2] + sons[now].back() - sons[to].back()));
		else DFS2(to, now, tmp + 1);
	}
}

int ans[MAXN];
std::vector<int> add[MAXN], sub[MAXN];
std::multiset<int> st;

int main() {
#ifndef LOCAL
	freopen("amoeba.in", "r", stdin);
	freopen("amoeba.out", "w", stdout);
#endif
	
	int A, B;
	
	scanf("%d%d%d", &n, &A, &B);
	for (int i = 1; i < n; ++i) {
		static int u, v;
		
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	DFS(1, 0);
	DFS2(1, 0, 0);
	
	for (int i = 1; i <= n; ++i) {
		sons[i].push_back(lenfa[i]);
		std::sort(sons[i].begin(), sons[i].end());
	}
	
	for (int i = 1; i <= n; ++i) {
		int last = 0;
		for (int j = 0; j < (int)sons[i].size(); ++j) {
			if (last > sons[i][j]) continue;
			
			add[last].push_back(sons[i].size() - j);
			sub[sons[i][j] + 1].push_back(sons[i].size() - j);
			last = sons[i][j] + 1;
		}
	}
	//std::cerr << "sdf" << std::endl;
	for (int i = 0; i < n; ++i) {
		for (int j: add[i])
			st.insert(j);
		for (int j: sub[i])
			st.erase(st.find(j));
		if (st.empty())
			ans[i] = 0;
		else ans[i] = *--st.end();
	}
	
	for (int i = A; i <= B; ++i)
		printf("%d\n", ans[i]);
	
	return 0;
}
