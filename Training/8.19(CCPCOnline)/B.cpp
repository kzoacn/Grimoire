#include <bits/stdc++.h>

typedef long long ll;

int n, m, q;

int a[25], b[25];

int e[25][25], ee[25][25];

int ida[25], idb[25];
int nn, mm;

int t[1 << 20], T = 0;

ll DFS(int S, int now, int S2) {
	while (now < nn && !(S & (1 << now))) ++now;
	if (now == nn) return 0;
	
	ll res = DFS(S, now + 1, S2);
	for (int i = 0; i < mm; ++i) if (e[ida[now]][idb[i]] && !(S2 & (1 << i))) {
		S2 ^= 1 << i;
		if (t[S2] != T) {
			t[S2] = T; ++res;
		}
		DFS(S, now + 1, S2);
		S2 ^= 1 << i;
	}
	return res;
}

ll calc() {
	ll res = 0;
	for (int S = 0; S < (1 << nn); ++S) {
		++T;
		
		res += DFS(S, 0, 0) + 1;
	}
	return res;
}

int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d%d%d", &n, &m, &q);
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j)
				scanf("%1d", e[i] + j);
		for (int i = 0; i < n; ++i) scanf("%d", a + i);
		for (int i = 0; i < m; ++i) scanf("%d", b + i);
		
		printf("Case #%d:", kase);
		
		for (int g; q--; ) {
			scanf("%d", &g);
			
			nn = mm = 0;
			for (int i = 0; i < n; ++i) if (a[i] % g == 0) {
				ida[nn++] = i;
			}
			for (int i = 0; i < m; ++i) if (b[i] % g == 0) {
				idb[mm++] = i;
			}
			
			printf(" %lld", calc());
		}
		puts("");
	}
	
	return 0;
}
