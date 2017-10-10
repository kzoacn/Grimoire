#include <bits/stdc++.h>

namespace Heap {
	int pool[100005], cnt;
	
	void clear() {
		cnt = 0;
	}
	
	int top() {
		return pool[1];
	}
	
	void push(int x) {
		pool[++cnt] = x;
		std::push_heap(pool + 1, pool + cnt + 1, std::greater<int>());
	}
	
	void pop() {
		std::pop_heap(pool + 1, pool + cnt + 1, std::greater<int>());
		--cnt;
	}
	
	bool empty() {
		return cnt == 0;
	}
}

int n, m;
int head[100005], nxt[1000005], to[1000005], ideg[100005], ed;

void AddEdge(int u, int v) {
	nxt[++ed] = head[u]; head[u] = ed; to[ed] = v;
}

int num[2][100005], cnt[2];

int ans[100005], check_tmp[100005];

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		memset(head, 0, sizeof head); ed = 0;
		memset(ideg, 0, sizeof ideg);
		
		scanf("%d%d", &n, &m);
		
		bool no_sol = 0;
		
		int cur = 0;
		for (int i = 1; i <= m; ++i) {
			scanf("%d", cnt + cur);
			for (int j = 1; j <= cnt[cur]; ++j) {
				scanf("%d", num[cur] + j);
				if (j > 1) {
					if (num[cur][j - 1] > num[cur][j]) no_sol = 1;
					AddEdge(num[cur][j - 1], num[cur][j]);
					++ideg[num[cur][j]];
				}
			}
			if (i > 1) {
				int jj = cnt[cur ^ 1];
				for (int j = cnt[cur]; j; --j) {
					while (jj && num[cur][j] < num[cur ^ 1][jj]) --jj;
					if (!jj) no_sol = 1;
					else {
						AddEdge(num[cur][j], num[cur ^ 1][jj]);
						++ideg[num[cur ^ 1][jj]];
						--jj;
					}
				}
			}
			cur ^= 1;
		}
		
		if (no_sol) {
			printf("Case #%d: No solution\n", kase);
			continue;
		}
		
		Heap::clear();
		for (int i = 1; i <= n; ++i)
			if (!ideg[i]) Heap::push(i);
		
		for (int t = 1; t <= n; ++t) {
			int x = Heap::top();
			Heap::pop();
			check_tmp[t] = ans[t] = x;
			for (int i = head[x]; i; i = nxt[i]) {
				--ideg[to[i]];
				if (!ideg[to[i]]) Heap::push(to[i]);
			}
		}
		
		std::sort(check_tmp + 1, check_tmp + n + 1);
		if (std::unique(check_tmp + 1, check_tmp + n + 1) - check_tmp - 1 != n || check_tmp[1] != 1 || check_tmp[n] != n) no_sol = 1;
		
		printf("Case #%d: ", kase);
		if (no_sol) puts("No solution");
		else {
			for (int i = 1; i <= n; ++i)
				printf("%d%c", ans[i], " \n"[i == n]);
		}
	}
	
	return 0;
}
