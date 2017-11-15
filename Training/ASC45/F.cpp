#include <bits/stdc++.h>
using namespace std;

const int MAXN = 111111 * 2;
int n, m, v[MAXN], u[MAXN], w[MAXN], ans[MAXN], id[MAXN];
int cnt, link[MAXN];

inline bool cmp(int p, int q) {
	return w[p] < w[q];
}

int main() {
    freopen("flights.in", "r", stdin);
    freopen("flights.out", "w", stdout);
	while (scanf("%d%d", &n, &m), n) {
		for (int i = 1; i <= m; ++i) {
			ans[i] = 0;
		}
		for (int i = 1; i <= n; ++i) {
			w[i] = 0;
		}
		cnt = 0;
		for (int i = 1; i <= m; ++i) {
			scanf("%d%d", &u[i], &v[i]);
			if (u[i] != 1 && v[i] != 1) {
				ans[i] = ++cnt;
				w[u[i]] += cnt;
				w[v[i]] += cnt;
				//cout << u[i] << " " << v[i] << " " << cnt << endl;
			}
		}
//-** (int i = 2; i <= n; ++i) cout << w[i] << " "; cout << endl;
		for (int i = 2; i <= n; ++i) {
			id[i - 1] = i;
		}
		sort(id + 1, id + n, cmp);
		for (int i = 1; i < n; ++i) {
			link[id[i]] = ++cnt;
		}
//for (int i = 1; i < n; ++i) cout << id[i] << " "; cout << endl;
		cout << "Yes" << endl;
		for (int i = 1; i <= m; ++i) {
			int now = ans[i] ? ans[i] : (u[i] > 1 ? link[u[i]] : link[v[i]]);
			printf("%d%s", now, i == m ? "\n" : " ");
		}
	}
}
