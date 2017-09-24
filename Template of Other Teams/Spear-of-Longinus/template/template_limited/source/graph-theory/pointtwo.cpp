///求割点，割点向每个点双连通分量连边
void Dfs(int x, int lst){
	dfn[x] = ++dfc;
	low[x] = dfn[x];
	stack[++cnt] = x;
	int son = 0;
	
	for (int i = g[x]; i; i = nxt[i]){
		if (!dfn[adj[i]]){
			++son;
			Dfs(adj[i], i);
			low[x] = min(low[x], low[adj[i]]);
			if (low[adj[i]] >= dfn[x]){
				int Tmp;
				iscut[x] = 1;
				++block;
				E[x].push_back(block + n);
				do{
					Tmp = stack[cnt --];
					belong[Tmp] = block + n;
					
					E[Tmp].push_back(block + n);
				}while (Tmp != adj[i]);
			}
		}
		else
		if ((i  ^ lst) != 1) low[x] = min(low[x], dfn[adj[i]]);
	}
	if (x == Root && son == 1) iscut[x] = 0, belong[x] = E[x][0];
	if (x == Root && son == 0){
		++block;
		belong[x] = block + n;
	}
}
	tot = 1;//!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	block = 0;
	cnt = 0;
	dfc = 0;
	for (int i = 1; i <= n; i++)
		if (dfn[i] == 0){
			Root = i;
			Dfs(i, 0);
		}

