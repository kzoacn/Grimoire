#include <bits/stdc++.h>
using namespace std;

const int MAXN = 111111;
int n, m, cnt;
bool used[MAXN];
int adj[MAXN], fa[MAXN], from[MAXN], deg[MAXN], col[MAXN], size[MAXN];
vector<pair<int, int> > change[MAXN];
vector<pair<int, long long> > ans;

struct Edge {
	int v, nxt;
} e[MAXN << 1];

inline void addedge(int u, int v) {
	e[++cnt].v = v;
	e[cnt].nxt = adj[u];
	adj[u] = cnt;
}

inline int get_fa(int u) {
	return fa[u] == u ? u : fa[u] = get_fa(fa[u]);
}

int main() {
	while (cin >> n >> m) {
		memset(adj, 0, sizeof(adj));
		cnt = 0;
		for (int i = 1, u, v; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			addedge(u, v);
			addedge(v, u);
		}
		
		for (int i = 1; i <= n; ++i) {
			from[i] = i;
			deg[i] = 0;
			change[i].clear();
			change[i].push_back({i, 1});
		}
		for (int i = 1; i <= n; ++i) {
			for (int p = adj[i]; p; p = e[p].nxt) {
				from[e[p].v] = from[i];
				change[e[p].v].push_back({from[i], i});
			}
		}
		for (int i = 1; i <= n; ++i) {
			change[i].push_back({n + 1, n + 1});
		}
		
		for (int i = 1; i <= n; ++i) {
			fa[i] = i;
			size[i] = 1;
			deg[from[i]]++;
		}
		for (int i = 1; i <= n; ++i) {
			int u = get_fa(i), v = get_fa(from[i]);
			if (u != v) {
				fa[u] = v;
				size[v] += size[u];
			}
		}
		queue<int> Q;
		for (int i = 1; i <= n; ++i) {
			if (!deg[i]) {
				Q.push(i);
			}
		}
		while (Q.size()) {
			int u = Q.front();
			Q.pop();
			if (--deg[from[u]] == 0) {
				Q.push(from[u]);
			}
		}
		memset(used, false, sizeof(used));
		ans.clear();
		int idx = 0;
		for (int i = 1; i <= n; ++i) {
			if (!deg[i] || used[i]) {
				continue;
			}
			int u = i;
			static vector<int> vec;
			vec.clear();
			while (!used[u]) {
				used[u] = true;
				vec.push_back(u);
				u = from[u];
			}
			col[get_fa(i)] = idx++;
			ans.push_back({vec.size(), 0});
		}
		
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j + 1 < change[i].size(); ++j) {
				int who = col[get_fa(change[i][j].first)];
				ans[who].second += change[i][j + 1].second - change[i][j].second;
			}
		}
		
		vector<double> ret;
		for (auto u : ans) {
			for (int i = 0; i < u.first; ++i) {
				ret.push_back(u.second * 1.0 / n / u.first);
			}
		}
		sort(ret.begin(), ret.end());
		for (int i = ret.size() - 1; i >= 0; --i) {
			printf("%.6f\n", ret[i]);
		}
	}
}
