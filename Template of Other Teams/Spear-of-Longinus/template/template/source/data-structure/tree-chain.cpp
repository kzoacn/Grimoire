void Prep(int x){
	dep[x] = dep[fa[x]] + 1;
	size[x] = 1;
	son[x] = 0;
	for (int i = g[x]; i; i = nxt[i]){
		int y = adj[i];
		if (y == fa[x]) continue;
		fa[y] = x;
		Prep(y);
		size[x] += size[y];
		if (size[y] > size[son[x]]) son[x] = y;
	}
}
void Dfs(int x){
	dfn[x] = ++dfc;
	if (son[x] != 0){
		top[son[x]] = top[x];
		Dfs(son[x]);
	}
	for (int i = g[x]; i; i = nxt[i]){
		int y = adj[i];
		if (y != fa[x] && y != son[x]){
			top[y] = y;
			Dfs(y);
		}
		if (y != fa[x]){
			Bel[(i + 1) >> 1] = dfn[y];
			val[dfn[y]] = len[i];
		}
	}
}
int Ask(int x, int y){
	int Ret = -1000000001;
	while (top[x] != top[y]){
		if (dep[top[y]] > dep[top[x]]) swap(x, y);
		Ret = max(Ret, Query(1, 1, n, dfn[top[x]], dfn[x]));
		x = fa[top[x]];
	}
	if (dep[y] > dep[x]) swap(x, y);
	if (x != y)
		Ret = max(Ret, Query(1, 1, n, dfn[y] + 1, dfn[x]));
	return Ret;
}
//Hints : Ask部分具体的求值或者修改要稍作变动
