#include <bits/stdc++.h>

std::vector<int> divisor[100005];

bool notprime[100005];
int prime[100005], mu[100005];

void pretreatment() {
	const int lim = 1e5;
	
	for (int i = 1; i <= lim; ++i)
		divisor[i].push_back(1);
	
	mu[1] = 1;
	for (int i = 2; i <= lim; ++i) {
		if (!notprime[i]) {
			prime[++*prime] = i;
			mu[i] = -1;
		}
		
		if (mu[i]) {
			for (int j = i; j <= lim; j += i)
				divisor[j].push_back(i);
		}
		
		for (int j = 1; j <= *prime && i * prime[j] <= lim; ++j) {
			notprime[i * prime[j]] = 1;
			if (i % prime[j] == 0) {
				mu[i * prime[j]] = 0;
				break;
			}
			mu[i * prime[j]] = -mu[i];
		}
	}
}

int n, w[100005];

int head[100005], nxt[100005 << 1], to[100005 << 1], ed;

void AddEdge(int u, int v) {
	nxt[++ed] = head[u]; head[u] = ed; to[ed] = v;
}

int dfn[100005], idfn[100005], sz[100005];

int DFS(int now, int fa) {
	dfn[now] = ++*dfn; idfn[dfn[now]] = now;
	sz[now] = 1;
	for (int i = head[now]; i; i = nxt[i]) {
		if (to[i] == fa) continue;
		sz[now] += DFS(to[i], now);
	}
	return sz[now];
}

int ans[100005], cnt[100005];

struct Query {
	int pos, id, tp;
	
	Query() {}
	Query(int pos, int id, int tp): pos(pos), id(id), tp(tp) {}
	
	bool operator < (const Query &rhs) const {
		return pos < rhs.pos;
	}
} qry[100005 << 1]; int tot;

int main() {
	pretreatment();
	
//	for (int i = 1; i <= 100; ++i) fprintf(stderr, "%d: %d\n", i, mu[i]);
	
	for (int kase = 1; ~scanf("%d", &n); ++kase) {
		memset(ans, 0, sizeof(ans));
		memset(head, 0, sizeof(head)); ed = 0;
		*dfn = 0; tot = 0;
		
		for (int u, v, i = 1; i < n; ++i) {
			scanf("%d%d", &u, &v);
			AddEdge(u, v);
			AddEdge(v, u);
		}
		for (int i = 1; i <= n; ++i) scanf("%d", w + i);
		
		DFS(1, 0);
		
		for (int i = 1; i <= n; ++i) {
			qry[++tot] = Query(dfn[i] - 1, i, -1);
			qry[++tot] = Query(dfn[i] + sz[i] - 1, i, 1);
			
//			fprintf(stderr, "%d: %d\n", i, dfn[i]);
		}
		
		std::sort(qry + 1, qry + tot + 1);
		
		for (int i = 0, j = 1; i <= 100000; ++i) {
			if (i) {
				for (auto k: divisor[w[idfn[i]]]) ++cnt[k];
			}
			while (j <= tot && qry[j].pos == i) {
				for (auto k: divisor[w[qry[j].id]]) ans[qry[j].id] += qry[j].tp * cnt[k] * mu[k];
				
//				fprintf(stderr, "%d: %d %d\n", qry[j].id, ans[qry[j].id], qry[j].tp);
				
				++j;
			}
		}
		
		printf("Case #%d: ", kase);
		for (int i = 1; i <= n; ++i)
			printf("%d%c", ans[i], " \n"[i == n]);
	}
	
	return 0;
}
