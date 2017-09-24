int n, m, x, y, ans1, ans2, tot1, tot2, flag, size, ind2, dfn[N], low[N], block[M], vis[N];
vector<int> a[N];
pair<int, int> stack[M];
void tarjan(int x, int p) { // 坚固的点双连通分量
	dfn[x] = low[x] = ++ind2;
	for (int i = 0; i < a[x].size(); ++i)
		if (dfn[x] > dfn[a[x][i]] && a[x][i] != p){
			stack[++size] = make_pair(x, a[x][i]);
			if (i == a[x].size() - 1 || a[x][i] != a[x][i + 1])
				if (!dfn[a[x][i]]){
					tarjan(a[x][i], x);
					low[x] = min(low[x], low[a[x][i]]);
					if (low[a[x][i]] >= dfn[x]){
						tot1 = tot2 = 0;
						++flag;
						for (; ; ){
							if (block[stack[size].first] != flag) {
								++tot1;
								block[stack[size].first] = flag;
							}
							if (block[stack[size].second] != flag) {
								++tot1;
								block[stack[size].second] = flag;
							}
							if (stack[size].first == x && stack[size].second == a[x][i]) break;
							++tot2; --size;
						}
						for (; stack[size].first == x && stack[size].second == a[x][i]; --size)
							++tot2;
						if (tot2 < tot1) ans1 += tot2;
						if (tot2 > tot1) ans2 += tot2;
					}
				}
				else low[x] = min(low[x], dfn[a[x][i]]);
		}
}
int main(){
	for (; ; ){
		scanf("%d%d", &n, &m);
		if (n == 0 && m == 0) return 0;
		for (int i = 1; i <= n; ++i) {
			a[i].clear();
			dfn[i] = 0;
		}
		for (int i = 1; i <= m; ++i){
			scanf("%d%d",&x, &y);
			++x, ++y;
			a[x].push_back(y);
			a[y].push_back(x);
		}
		for (int i = 1; i <= n; ++i)
			sort(a[i].begin(), a[i].end());
		ans1 = ans2 = ind2 = 0;
		for (int i = 1; i <= n; ++i)
			if (!dfn[i]) {
				size = 0;
				tarjan(i, 0);
			}
		printf("%d %d\n", ans1, ans2);
	}
	return 0;
}
