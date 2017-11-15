#include <bits/stdc++.h>

typedef std::pair<int, int> PII;
#define mkpair std::make_pair

const int MAXN = 1e5 + 5;

int n, m;

std::vector<int> G[MAXN];

namespace PBCC {
	int dfn[MAXN], low[MAXN], bcc_id[MAXN], bcc_cnt, stamp;
	bool iscut[MAXN];
	
	std::vector<PII> bcc[MAXN], bccp[MAXN];
	
	PII stk[MAXN]; int stk_top;
	
	void Tarjan(int now, int fa) {
		int child = 0;
		dfn[now] = low[now] = ++stamp;
		for (int to: G[now]) {
			if (!dfn[to]) {
				stk[++stk_top] = mkpair(now, to); ++child;
				Tarjan(to, now);
				low[now] = std::min(low[now], low[to]);
				if (low[to] >= dfn[now]) {
					iscut[now] = 1;
					bcc[++bcc_cnt].clear();
					while (1) {
						PII tmp = stk[stk_top--];
						bcc_id[tmp.first] = bcc_id[tmp.second] = bcc_cnt;
						bcc[bcc_cnt].push_back(tmp);
						if (tmp.first == now && tmp.second == to)
							break;
					}
				}
			}
			else if (dfn[to] < dfn[now] && to != fa) {
				stk[++stk_top] = mkpair(now, to);
				low[now] = std::min(low[now], dfn[to]);
			}
		}
		if (!fa && child == 1)
			iscut[now] = 0;
	}
	
	void main() {
		memset(dfn, 0, sizeof dfn);
		memset(low, 0, sizeof low);
		memset(iscut, 0, sizeof iscut);
		memset(bcc_id, 0, sizeof bcc_id);
		stamp = bcc_cnt = stk_top = 0;
		
		for (int i = 1; i <= n; ++i)
			if (!dfn[i]) Tarjan(i, 0);
	}
}

int label[MAXN], deg[MAXN];

std::vector<int> g[MAXN];

std::vector<int> cyc, path;

int vis[MAXN], onCycle[MAXN];

bool getCycle(int now, int fa, int fir) {
	if (fa != -1 && now == fir) {
		cyc.push_back(fir);
		return 1;
	}
	if (vis[now]) return 0;
	cyc.push_back(now);
	vis[now] = 1;
	for (int to: g[now])
		if (to != fa && getCycle(to, now, fir)) return 1;
	cyc.pop_back();
	vis[now] = 2;
	return 0;
}

std::set<PII> cycEdge;

int getPath(int now, int fa, int fir) {
	if (vis[now]) return -1;
	path.push_back(now);
	if (now != fir && onCycle[now])
		return now;
	vis[now] = 1;
	for (int to: g[now]) {
		static int x;
		
		if (to == fa || cycEdge.count(mkpair(now, to)) || cycEdge.count(mkpair(to, now))/*(onCycle[now] && onCycle[to])*/) continue;
		
		if ((x = getPath(to, now, fir)) != -1) return x;
	}
	path.pop_back();
	return -1;
}

int main() {
#ifndef LOCAL
	freopen("grand.in", "r", stdin);
	freopen("grand.out", "w", stdout);
#endif
	
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; ++i) {
			label[i] = 0;
			G[i].clear();
			vis[i] = onCycle[i] = 0;
		}
		
		for (int i = 1; i <= m; ++i) {
			static int u, v;
			
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		
		PBCC::main();
		
		bool flag = 0;
		
		for (int id = 1; id <= PBCC::bcc_cnt; ++id) {
			int fir;
			for (PII e: PBCC::bcc[id]) {
				int u = e.first, v = e.second;
				if (label[u] != id) {
					deg[u] = 0; g[u].clear();
					label[u] = id;
				}
				if (label[v] != id) {
					deg[v] = 0; g[v].clear();
					label[v] = id;
				}
				
				++deg[u]; ++deg[v];
				g[u].push_back(v);
				g[v].push_back(u);
				
				if (deg[u] >= 3 || deg[v] >= 3) {
					flag = 1;
					fir = deg[u] >= 3 ? u : v;
				}
			}
			if (!flag) continue;
			
			cyc.clear();
			path.clear();
			
			for (int i = 1; i <= n; ++i)
				vis[i] = 0;
			
			getCycle(fir, -1, fir); // end with fir
			cycEdge.clear();
			for (int i: cyc)
				onCycle[i] = 1;
			for (int i = 1; i < (int)cyc.size(); ++i)
				cycEdge.insert(mkpair(cyc[i - 1], cyc[i]));
			
			for (int i = 1; i <= n; ++i)
				vis[i] = 0;
			
			int x = getPath(fir, -1, fir);
			assert(x != -1);
			/*
			std::cerr << "Cycle: " << std::endl;
			for (int i: cyc)
				std::cerr << i << " ";
			std::cerr << std::endl;
			std::cerr << "====" << std::endl;
			
			std::cerr << "Path: " << std::endl;
			for (int i: path)
				std::cerr << i << " ";
			std::cerr << std::endl;
			std::cerr << "====" << std::endl;
			*/
			
			int szl = 0;
			for (auto i = cyc.begin(); i != cyc.end(); ++i) {
				++szl;
				if (*i == x) break;
			}
			
			printf("%d %d\n", fir, x);
			printf("%d ", szl);
			for (auto i = cyc.begin(); i != cyc.end(); ++i) {
				printf("%d%c", *i, " \n"[*i == x]);
				if (*i == x) break;
			}
			printf("%d ", (int)cyc.size() - szl + 1);
			for (auto i = cyc.rbegin(); i != cyc.rend(); ++i) {
				printf("%d%c", *i, " \n"[*i == x]);
				if (*i == x) break;
			}
			printf("%d ", (int)path.size());
			for (int i: path)
				printf("%d%c", i, " \n"[i == x]);
//			std::cerr << "uhh?" << std::endl;
			
			break;
		}
		
		if (!flag) puts("-1");
	}
	
	return 0;
}

/*

Cycle: 
1 2 3 1 
====
1 2
1 2
3 1 1 3 2
1 1 2
uhh?
-1

*/
