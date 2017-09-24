struct Edge{
	int To, id;
	Edge(){}
	Edge(int _To, int _id){
		To = _To;
		id = _id;
	}
};

int n, m, dfc, block, top;
vector<Edge> G[N];
vector<int> H[N];

int dfn[N], low[N], stack[N], belong[N];

void Tarjan(int x, int lst){
	dfn[x] = low[x] = ++dfc;
	stack[top++] = x;
	for (int i = 0; i < (int)G[x].size(); i++){
		int y = G[x][i].To;
		if (!dfn[y]){
			Tarjan(y, G[x][i].id);
			low[x] = min(low[x], low[y]);
		} else if (!belong[y] && G[x][i].id != lst){
			low[x] = min(low[x], dfn[y]);
		}
	}
	if (low[x] == dfn[x]){
		block++;
		do{
			int y = stack[--top];
			belong[y] = block;
		} while (stack[top] != x);
	}
}

//bridge
		for (int i = 1; i <= n; i++)
			for (int j = 0; j < G[i].size(); j++){
				int y = G[i][j].To;
				if (belong[i] == belong[y]) continue;
				H[belong[i]].push_back(belong[y]);
			}
