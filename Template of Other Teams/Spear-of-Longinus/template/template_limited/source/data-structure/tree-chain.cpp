
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
