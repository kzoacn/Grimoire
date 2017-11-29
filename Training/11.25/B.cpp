#include <bits/stdc++.h>

#define left LEFT123

using namespace std;

const int MAXN = 2111;
const int INF = 1e9;
int value[MAXN][2], cost[MAXN][MAXN];
int cnt[MAXN], trigger[MAXN], val[MAXN], fa[MAXN], left[MAXN], sum[MAXN], ans[MAXN];
bool used[MAXN];
vector<int> to[MAXN], offspr[MAXN];
int cs, n;

struct Node {
	int x, y, r;
} p[MAXN];

inline bool inside(const Node &p, const Node &q) {
	return (p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y) <= p.r * p.r && p.r > q.r;
}

int main() {
	cin >> cs;
	for (; cs; --cs) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d%d%d%d", &p[i].x, &p[i].y, &p[i].r, &value[i][0], &value[i][1]);
			to[i].clear();
			offspr[i].clear();
			cnt[i] = 0;
		}
		
		int total = 0;
		for (int i = 1; i <= n; ++i) {
			int mx = INF;
			fa[i] = 0;
			for (int j = 1; j <= n; ++j) {
				if (i == j || !inside(p[j], p[i])) {
					continue;
				}
//cout << j << " contain " << i << endl;
				++cnt[i];
				if (p[j].r < mx) {
					fa[i] = j;
					mx = p[j].r;
				}
				offspr[j].push_back(i);
			}
			if (fa[i]) {
				to[fa[i]].push_back(i);
			}
		}
		for (int i = 1; i <= n; ++i) {
			val[i] = trigger[i] = cost[i][0] = 0;
			for (int j = 1, nowval = 0; j <= cnt[i]; ++j) {
				nowval += value[i][1 - j % 2];
				if (nowval > val[i]) {
					val[i] = nowval;
					trigger[i] = j;
				}
				cost[i][j] = nowval;
			}
//cout << i << " " << cnt[i] << " " << trigger[i] << " " << val[i] << endl;
			total += val[i];
		}
		
		cout << total << endl;
//return 0;
		memset(used, false, sizeof(used));
		memset(sum, 0, sizeof(sum));
		for (int i = 1; i <= n; ++i) {
			left[i] = cnt[i];
		}
		for (int i = 1; i <= n; ++i) {
			if (left[i] == trigger[i]) {
				for (int u = fa[i]; u; u = fa[u]) {
					++sum[u];
				}
			}
		}
		for (int i = 1; i <= n; ++i) {
//cout << "sum: ";
//for (int i = 1; i <= n; ++i) cout << sum[i] << " "; cout << endl;
			for (int j = 1; j <= n; ++j) {
//if (i == 2)cout << j << " " << sum[j] << " " << left[j] << " " << cost[j][left[j]] << " " << val[j] << //endl;
				if (used[j] || cost[j][left[j]] != val[j]) {
					continue;
				}
//cout << "succeed: " << j << endl;
				if (sum[j] == 0) {
				//cout << i << "asdf" << endl;
					//printf("%d%s", j, i == n ? "\n" : " ");
					ans[i] = j;
					used[j] = true;
					for (int u = fa[j]; u; u = fa[u]) {
						sum[u] -= left[j] == trigger[j];
					}
					for (auto k : offspr[j]) {
						if (!used[k] && --left[k] == trigger[k]) {
							for (int u = fa[k]; u; u = fa[u]) {
								++sum[u];
							}
						}
					}					
					break;
				}
			}
		}
		for (int i = 1; i <= n; ++i) cout << ans[i] << " ";
		cout << "\n";
	}
}
