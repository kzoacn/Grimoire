#include <bits/stdc++.h>

int n, m;

int deg[10], hfdeg[10];

struct Edge {
	int u, v;
	
	void scan() {
		scanf("%d%d", &u, &v);
	}
	
	bool operator < (const Edge &oth) const {
		return std::min(deg[u], deg[v]) < std::min(deg[oth.u], deg[oth.v]);
	}
} e[50];

int ans;
int cnt[2][10];

void DFS(int now) {
	if (now == m + 1) {
		++ans;
		return;
	}
	int u = e[now].u, v = e[now].v;
	for (int i = 0; i < 2; ++i) {
		++cnt[i][u], ++cnt[i][v];
		
		if (cnt[i][u] <= hfdeg[u] && cnt[i][v] <= hfdeg[v])
			DFS(now + 1);
		
		--cnt[i][u], --cnt[i][v];
	}
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		memset(deg, 0, sizeof deg);
		memset(cnt, 0, sizeof cnt);
		
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; ++i) {
			e[i].scan();
			++deg[e[i].u];
			++deg[e[i].v];
		}
		
		bool flag = 0;
		for (int i = 1; i <= n; ++i) {
			if (deg[i] & 1) {
				flag = 1; break;
			}
			hfdeg[i] = deg[i] / 2;
		}
		if (flag) {
			puts("0"); continue;
		}
		
		std::sort(e + 1, e + m + 1);
		
//		std::cerr << "yes we can" << std::endl;
		
		ans = 0;
		DFS(1);
		
		printf("%d\n", ans);
	}
	
	return 0;
}
