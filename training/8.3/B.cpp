#include <bits/stdc++.h>

int n;
int head[100005], nxt[100005 << 1], to[100005 << 1], d[100005 << 1], ed;

void AddEdge(int u, int v, int w) {
	nxt[++ed] = head[u]; head[u] = ed; to[ed] = v; d[ed] = w;
}

int cnt[105], tot_cnt, last;

int DFS(int now, int fa, int edge_to_fa) {
	int res = 0;
	for (int i = head[now]; i; i = nxt[i]) {
		if (to[i] == fa) continue;
		res += DFS(to[i], now, d[i]);
	}
	
	memset(cnt, tot_cnt = 0, sizeof cnt); last = 100;
	for (int i = head[now]; i; i = nxt[i]) {
		if (to[i] == fa) continue;
		++cnt[d[i]];
		tot_cnt += d[i];
	}
	while (edge_to_fa--) {
		while (last && !cnt[last]) --last;
		if (!last) break;
		--cnt[last];
		if (last > 1) ++cnt[last - 1];
		--tot_cnt;
	}
	
	while (last && !cnt[last]) --last;
	if (!last) return res;
	if (tot_cnt - last < last) res += last;
	else res += (tot_cnt + 1) >> 1;
	return res;
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		memset(head, ed = 0, sizeof head);
		
		scanf("%d", &n);
		for (int u, v, w, i = 1; i < n; ++i) {
			scanf("%d%d%d", &u, &v, &w);
			AddEdge(u, v, w);
			AddEdge(v, u, w);
		}
		
		printf("Case #%d: %d\n", kase, DFS(1, 0, 0));
	}
	
	return 0;
}
