#include <bits/stdc++.h>

using namespace std;

const int MAXN = 55;

int n, m1, m2;

int L[MAXN], R[MAXN];
bool cant[MAXN][MAXN];

vector<int> G[MAXN];
int lnk[MAXN], vis[MAXN], T;

bool cho[MAXN];

bool Find(int u) {
	for (int v: G[u]) {
		if (vis[v] == T) continue;
		vis[v] = T;
		if (!cho[v] && (!lnk[v] || Find(lnk[v]))) {
			lnk[v] = u; return 1;
		}
	}
	return 0;
}

int Hungary(int fir = 1) {
	int res = 0;
	memset(lnk, 0, sizeof lnk);
	for (int i = fir; i <= n; ++i) {
		++T; res += Find(i);
	}
	return res;
}

int ans[MAXN];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	while (cin >> n >> m1 >> m2) {
		memset(cant, 0, sizeof cant);
		memset(cho, 0, sizeof cho);
		
		for (int i = 1; i <= n; ++i) {
			L[i] = 1; R[i] = n;
		}
		for (int i = 1; i <= m1; ++i) {
			static int l, r, x;
			
			cin >> l >> r >> x;
			L[x] = max(L[x], l);
			R[x] = min(R[x], r);
			for (int j = 1; j < x; ++j)
				for (int t = l; t <= r; ++t)
					cant[j][t] = 1;
		}
		for (int i = 1; i <= m2; ++i) {
			static int l, r, x;
			
			cin >> l >> r >> x;
			L[x] = max(L[x], l);
			R[x] = min(R[x], r);
			for (int j = x + 1; j <= n; ++j)
				for (int t = l; t <= r; ++t)
					cant[j][t] = 1;
		}
		
		for (int i = 1; i <= n; ++i)
			G[i].clear();
		
		for (int i = 1; i <= n; ++i) {
			if (L[i] > R[i]) {
				cout << -1 << endl; goto NEXT;
			}
			for (int j = 1; j < L[i]; ++j) cant[i][j] = 1;
			for (int j = R[i] + 1; j <= n; ++j) cant[i][j] = 1;
			for (int j = L[i]; j <= R[i]; ++j) if (!cant[i][j])
				G[j].push_back(i);
		}
		
		if (Hungary() != n) {
			cout << -1 << endl; goto NEXT;
		}
		
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) if (!cho[j] && !cant[j][i]) {
				cho[j] = 1;
				ans[i] = j;
				if (Hungary(i + 1) == n - i) break;
				cho[j] = 0;
			}
		}
		
		for (int i = 1; i <= n; ++i)
			cout << ans[i] << " \n"[i == n];
		
		NEXT:;
	}
	
	return 0;
}
