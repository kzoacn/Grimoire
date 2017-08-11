#include<bits/stdc++.h>
using namespace std;
const double eps = 1e-9;
const int N = 22222;
vector<int> g[N];
double A[N], B[N], C[N];
double eq[222][222], p[N];
double P;
int n, m;
int a[N];
bool dfs(int u, int fa) {
	int deg = g[u].size();
	double tmp = 1;
	bool bad = 0;
	A[u] = (1 - P) / deg;
	B[u] = 1;
	C[u] = 1 - P;
	for (int i = 0; i < deg; ++i) {
		int v = g[u][i];
		if (v == fa) continue;
		dfs(v, u);
//		if (!dfs(v, u)) assert(0);
		B[u] += (1 - P) / deg * B[v];
		C[u] += (1 - P) / deg * C[v];
		tmp -= (1 - P) / deg * A[v];
	}
	if (u == n) {
		A[u] = B[u] = C[u] = 0;
		return 1;
	}
	//if (bad) return 0;
	if (fabs(tmp) < eps) return 0;
	A[u] /= tmp;
	B[u] /= tmp;
	C[u] /= tmp;
	//cout << u << " " << tmp << endl;
	return 1;
}
int cas;
void gauss(int n) {
	int i, j, k, r;
	for (i = 1; i <= n; ++i) {
		r = i;
		for (j = i + 1; j <= n; ++j) 
			if (fabs(eq[j][i]) > fabs(eq[r][i])) r = j;
		if (r != i) for (j = 1; j <= n + 1; ++j) swap(eq[r][j], eq[i][j]);
	
		for (k = i + 1; k <= n; ++k) {	
			double f = eq[k][i] / eq[i][i];
			for (j = i; j <= n + 1; ++j) eq[k][j] -= f * eq[i][j];
		}
	}
	for (i = n; i >= 1; --i) {
		for (j = i + 1; j <= n; ++j) eq[i][n + 1] -= eq[j][n + 1] * eq[i][j];
		eq[i][n + 1] /= eq[i][i];
	}
}
void work() {
	printf("Case #%d: ", ++cas);
	scanf("%d%d", &n, &m);
	//printf("%d %d\n", n, m);
	for (int i = 1; i <= n; ++i) g[i].clear();
	P = 0;
	bool ok = 0;
	for (int i = 1; i <= m; ++i) {
		scanf("%d%lf", &a[i], &p[i]);
		P += p[i];
		//printf("%d %f\n", a[i], p[i]);
		if (a[i] == n && fabs(p[i]) > eps) ok = 1;
	}
	for (int i = 1; i < n; ++i) {
		int x, y; scanf("%d%d", &x, &y);
		g[x].push_back(y);
		g[y].push_back(x);
	}
	if (P>1-1e-9 ) {
		if(!ok)puts("impossible");
		else puts("0");
		return;
	}
	for (int _ = 1; _ <= m; ++_) for (int i = 1; i <= m + 1; ++i) eq[_][i] = 0;
	for (int _ = 1; _ <= m; ++_) {
		int u = a[_];
		for (int i = 1; i <= n; ++i) A[i] = B[i] = C[i] = 0;
		dfs(u, 0);
		//cout << u << " "<< A[u] << " " << B[u] << " " << C[u] << endl;
		eq[_][_] = 1;
		for (int i = 1; i <= m + 1; ++i) eq[_][i] -= p[i] * B[u];
		eq[_][m + 1] = C[u];
	}
	
	gauss(m);
	/*cout << endl;
	for(int i = 1; i <= m; i++)
		cout << a[i] << " " << eq[i][i] << endl;*/
	for (int i = 1; i <= n; ++i) A[i] = B[i] = C[i] = 0;
	dfs(1, 0);
//	cout << A[1] << " " << B[1] << " " << C[1] << endl;
	double K = C[1];
	for (int i = 1; i <= m; ++i) K += B[1] * p[i] * eq[i][m + 1];
	if (!(K >= 0 || K <= 0)){
		puts("impossible");
		return;
	}
	printf("%.9f\n", K);
	
}
int main() {
	int T; scanf("%d", &T);
	while (T--) work();
	return 0;
}
