#include <bits/stdc++.h>

const int MAXN = 1e5 + 5;

int n;
int dfn[2][MAXN], idfn[2][MAXN];

int fa[MAXN];

int DFS(int L0, int R0, int L1, int R1) {
//	std::cerr << L0 << " " << R0 << " " << L1 << " " << R1 << std::endl;
	if (L0 > R0) {
//		return 0;
		while (1) puts("cnbb");
	}
	
	if (R0 - L0 + 1 == 1) return 1;
	
	if (dfn[0][L0 + 1] != dfn[1][L1 + 1]) {
		fa[dfn[0][L0 + 1]] = fa[dfn[1][L1 + 1]] = dfn[0][L0];
		int mid0 = idfn[0][dfn[1][L1 + 1]], 
			mid1 = idfn[1][dfn[0][L0 + 1]];
		int size0 = mid0 - L0 - 1, 
			size1 = mid1 - L1 - 1;
		
//		std::cerr << size0 << " " << size1 << std::endl;
		
		return 1 + DFS(L0 + 1, mid0 - 1, mid1, mid1 + size0 - 1) + DFS(mid0, mid0 + size1 - 1, L1 + 1, mid1 - 1);
	}
	
	fa[dfn[0][L0 + 1]] = dfn[0][L0];
	
//	std::cerr << L0 << " " << R0 << " " << L1 << " " << R1 << std::endl;
	
	int size = DFS(L0 + 1, R0, L1 + 1, R1);
	if (size == R0 - L0) return size + 1;
	fa[dfn[0][L0 + size + 1]] = dfn[0][L0];
	return size + DFS(L0 + size + 1, R0, L1 + size + 1, R1) + 1;
}

void Solve() {
	int caseCnt; scanf("%d", &caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scanf("%d", &n);
		for (int tr = 0; tr < 2; ++tr) {
			for (int i = 1; i <= n; ++i) {
				scanf("%d", &dfn[tr][i]);
				idfn[tr][dfn[tr][i]] = i;
			}
		}
		
		memset(fa, 0, sizeof fa);
		
		DFS(1, n, 1, n);
		
		for (int i = 1; i <= n; ++i) {
			printf("%d%c", fa[i], " \n"[i == n]);
		}
	}
}

register char *_sp __asm__("rsp");

int main() {
	const int size = 16 << 20;
	static char *sys, *mine(new char[size] + size - 4096);
	sys = _sp; _sp = mine; Solve(); _sp = sys;
	
	return 0;
}
