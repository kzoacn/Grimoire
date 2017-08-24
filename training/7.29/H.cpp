#include <bits/stdc++.h>

int n;

bool edge[1005][1005];

int col[1005], vis[1005];
bool fir[1005];

int stk[1005], top;

void DFS(int now, int fa) {
	if (vis[now]) {
		if (vis[now] == 2) {
			return;
		}
		for (int i = top; i; --i) {
			if (col[stk[i]] == col[now]) break;
			fir[col[stk[i]]] = 0;
			col[stk[i]] = col[now];
		}
		return;
	}
	
	vis[now] = 1;
	stk[++top] = now;
	for (int i = 1; i <= n; ++i) {
		if (i != fa && i != now && edge[now][i]) DFS(i, now);
	}
	vis[now] = 2;
	--top;
}

int main() {
	while (~scanf("%d", &n) && n) {
		memset(edge, 0, sizeof edge);
		for (int w, i = 1; i < n; ++i) {
			for (int j = i + 1; j <= n; ++j) {
				scanf("%1d", &w);
				if (w == 1) edge[i][j] = 1, edge[j][i] = 0;
				else edge[i][j] = 0, edge[j][i] = 1;
			}
		}
		
		for (int i = 1; i <= n; ++i) {
			col[i] = i;
			fir[i] = 1;
			vis[i] = 0;
		}
		
		for (int i = 1; i <= n; ++i) {
			top = 0;
			if (!vis[i]) DFS(i, 0);
		}
		
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j) if (i != j)
				if (edge[i][j] && col[i] != col[j]) fir[col[j]] = 0;
		
		int ans = 0;
		for (int i = 1; i <= n; ++i)
			if (fir[col[i]]) ++ans;
		printf("%d\n", ans);
	}
	
	return 0;
}
