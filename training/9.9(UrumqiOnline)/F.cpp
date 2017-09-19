#include <bits/stdc++.h>

int n, m;

int head[10005], nxt[100005 << 1], to[100005 << 1], ed;

void AddEdge(int u, int v) {
	nxt[++ed] = head[u]; head[u] = ed; to[ed] = v;
}

int stamp, scc_cnt;
int dfn[10005], low[10005], scc[10005];
int stk[10005], top;

void Tarjan(int now) {
	dfn[now] = low[now] = ++stamp;
	stk[top++] = now;
	for (int i = head[now]; i; i = nxt[i]) {
		if (!dfn[to[i]]) {
			Tarjan(to[i]);
			low[now] = std::min(low[now], low[to[i]]);
		}
		else if (!scc[to[i]])
			low[now] = std::min(low[now], dfn[to[i]]);
	}
	if (low[now] == dfn[now]) {
		++scc_cnt;
		do {
			scc[stk[--top]] = scc_cnt;
		} while (stk[top] != now);
	}
}

int ideg[10005], odeg[10005];
int izero, ozero;

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		memset(head, 0, sizeof head); ed = 0;
		
		scanf("%d%d", &n, &m);
		for (int u, v, i = 1; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			AddEdge(u, v);
		}
		
		stamp = scc_cnt = top = 0;
		memset(dfn, 0, sizeof dfn);
		memset(scc, 0, sizeof scc);
		for (int i = 1; i <= n; ++i)
			if (!dfn[i]) Tarjan(i);
		
		if (scc_cnt == 1) {
			puts("0");
			continue;
		}
		
//		std::cerr << scc_cnt << std::endl;
		
		memset(ideg, 0, sizeof ideg);
		memset(odeg, 0, sizeof odeg);
		izero = ozero = scc_cnt;
		for (int u = 1; u <= n; ++u) {
			for (int i = head[u]; i; i = nxt[i]) {
				int v = to[i];
				
				if (scc[u] == scc[v]) continue;
				
				if (ideg[scc[v]] == 0) --izero;
				++ideg[scc[v]];
				
				if (odeg[scc[u]] == 0) --ozero;
				++odeg[scc[u]];
			}
		}
		
		printf("%d\n", std::max(izero, ozero));
	}
	
	return 0;
}
