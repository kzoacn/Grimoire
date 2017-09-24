#include <bits/stdc++.h>

#define __advance __attribute__((optimize("O3")))

int L, P;

__advance int Find(int *f, int x) {
	return f[x] == x ? x : f[x] = Find(f, f[x]);
}

int fa_u[10005], fa_d[10005];

int sorted[10005], overlap[5005][2], over[10005];

__advance void selfloop_toke() {
	for (int i = Find(fa_u, 0); P && i <= *sorted; i = Find(fa_u, i + 1)) {
		int x = i, y = over[i];
		
		if (x > y) std::swap(x, y);
		
		if (Find(fa_d, x + 1) >= y || (Find(fa_d, y + 1) == *sorted + 1 && Find(fa_d, 0) >= x)) {
			--P;
			fa_u[i] = Find(fa_u, i + 1);
			fa_d[over[i]] = Find(fa_d, over[i] + 1);
			
			over[i] = -1;
		}
	}
}

__advance void passing_toke() {
	if (P < 2) return;
	
	int k = -1;
	for (int i = Find(fa_u, 0), j = Find(fa_u, i + 1); P && j <= *sorted; i = Find(fa_u, i + 1), j = Find(fa_u, j + 1)) {
		if (Find(fa_d, i + 1) > j || (Find(fa_d, j + 1) == *sorted + 1 && Find(fa_d, 0) > i)) {
			P -= 2;
			fa_u[j] = Find(fa_u, j + 1);
			fa_u[i] = Find(fa_u, i + 1);
			fa_d[over[j]] = Find(fa_d, over[j] + 1);
			fa_d[over[i]] = Find(fa_d, over[i] + 1);
			
			over[i] = over[j] = -1;
			j = Find(fa_u, j + 1);
		}
		k = j;
	}
	
	if (P < 2) return;
	
	int i = Find(fa_u, 0), j = k;
	if (Find(fa_d, i + 1) > j || (Find(fa_d, j + 1) == *sorted + 1 && Find(fa_d, 0) > i)) {
		P -= 2;
		fa_u[j] = Find(fa_u, j + 1);
		fa_u[i] = Find(fa_u, i + 1);
		fa_d[over[j]] = Find(fa_d, over[j] + 1);
		fa_d[over[i]] = Find(fa_d, over[i] + 1);
		
		over[i] = over[j] = -1;
		j = Find(fa_u, j + 1);
	}
}

__advance int main() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d%d", &L, &P);
		
		*sorted = 0;
		for (int x, y, i = 1; i <= P; ++i) {
			scanf("%d%d", &x, &y);
			
			overlap[i][0] = x;
			overlap[i][1] = y;
			
			sorted[++*sorted] = x;
			sorted[++*sorted] = y;
		}
		
		std::sort(sorted + 1, sorted + *sorted + 1);
		*sorted = std::unique(sorted + 1, sorted + *sorted + 1) - sorted - 1;
		
		for (int i = 0; i <= *sorted; ++i)
			fa_u[i] = fa_d[i] = i + 1;
		fa_u[*sorted + 1] = fa_d[*sorted + 1] = *sorted + 1;
		
		memset(over, -1, sizeof over);
		
		for (int i = 1; i <= P; ++i) {
			overlap[i][0] = std::lower_bound(sorted + 1, sorted + *sorted + 1, overlap[i][0]) - sorted;
			overlap[i][1] = std::lower_bound(sorted + 1, sorted + *sorted + 1, overlap[i][1]) - sorted;
			
			over[overlap[i][0]] = overlap[i][1];
			
			fa_u[overlap[i][0]] = overlap[i][0];
			fa_d[overlap[i][1]] = overlap[i][1];
		}
		
		while (P) {
			int last = P;
			passing_toke();
			selfloop_toke();
			
			if (P == last) break;
		}
		
		printf("Case #%d: ", kase);
		puts(P == 0 ? "YES" : "NO");
	}
	
	return 0;
}
