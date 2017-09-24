#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1111111;
queue<int> Q;
vector<int> to[MAXN];
int deg[MAXN];
double lim[MAXN], lev[MAXN];
int n, m, S, T;
double y;

int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		scanf("%lf%lf", &lim[i], &lev[i]);
	}
	for (int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v;
		to[u].push_back(v);
		++deg[v];
	}
	cin >> S >> y >> T;
	lev[S] += y;
	while (!Q.empty()) {
		Q.pop();
	}
	for (int i = 1; i <= n; ++i) {
		if (deg[i] == 0) {
			Q.push(i);
		}
	}
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		if (u == T) {
			lev[u] = min(lev[u], lim[u]);
			break;
		}
		double div = (lev[u] - lim[u]) / (int)to[u].size();
		if (div < 0) {
			div = 0;
		}
		lev[u] -= div * (int)to[u].size();
//cout << u << " " << div << endl;
		for (auto v : to[u]) {
			lev[v] += div;
			if (--deg[v] == 0) {
				Q.push(v);
			}
		}
	}
	//cout << lev[2] << " " << lev[3] << endl;
	printf("%.10f\n", lev[T]);
}
