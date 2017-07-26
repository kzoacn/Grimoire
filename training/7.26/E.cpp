#include <bits/stdc++.h>
using namespace std;

const int MAXN = 111111;
const int MAXM = 111111;
const int MAXQ = 111111;
int testcase, n, m, Q, fa[MAXN], size[MAXN], ans[MAXM];

inline int get_fa(int u) {
	return u == fa[u] ? u : fa[u] = get_fa(fa[u]);
}

struct Edge {
	int u, v, w;
} e[MAXM];

inline bool cmp(const Edge &p, const Edge &q) {
	return p.w < q.w;
}

struct Ques {
	int w, id;
} ques[MAXQ];

inline bool cmp_Q(const Ques &p, const Ques &q) {
	return p.w < q.w;
}

inline int calc(int size) {
	return size * (size - 1);
}

int main() {
	scanf("%d", &testcase);
	for (; testcase; --testcase) {
		scanf("%d%d%d", &n, &m, &Q);
		for (int i = 1; i <= n; ++i) {
			fa[i] = i;
			size[i] = 1;
		}
		for (int i = 1; i <= m; ++i) {
			scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
		}
		
		sort(e + 1, e + m + 1, cmp);
		for (int i = 1; i <= Q; ++i) {
			scanf("%d", &ques[i].w);
			ques[i].id = i;
		}
		sort(ques + 1, ques + Q + 1, cmp_Q);
		
		int tot = 0, j = 1;
		for (int i = 1; i <= Q; ++i) {
			while (j <= m && e[j].w <= ques[i].w) {
				int u = e[j].u, v = e[j].v;
				u = get_fa(u);
				v = get_fa(v);
				if (u != v) {
					tot -= calc(size[u]) + calc(size[v]);
					tot += calc(size[u] + size[v]);
					fa[u] = v;
					size[v] += size[u];
				}
				++j;
			}
			ans[ques[i].id] = tot;
		}
		for (int i = 1; i <= Q; ++i) {
			printf("%d\n", ans[i]);
		}
	}
}
