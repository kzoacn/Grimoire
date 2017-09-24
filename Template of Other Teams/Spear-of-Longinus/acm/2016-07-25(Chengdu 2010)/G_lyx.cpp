#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int N = 20005;
const int M = 20005;

int Case;
int n, m;
int dfc, top, block;
int x[M], y[M], c[M];
int belong[N];
int dfn[N], low[N], stack[N];

vector<int> G[N];

void Tarjan(int x){
	dfn[x] = low[x] = ++dfc;
	stack[top++] = x;
	for (int i = 0; i < (int)G[x].size(); i++){
		int y = G[x][i];
		if (!dfn[y]){
			Tarjan(y);
			low[x] = min(low[x], low[y]);
		} else if (!belong[y]){
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

int Node(int x,int y){
	return x * 2 - 1 + y;
}

void Add(int x,int y){
	G[x].push_back(y);
}

bool Solve(int mid){
	int tot = n + n;
	dfc = top = block = 0;
	
	for (int i = 1; i <= tot; i++){
		G[i].clear();
		dfn[i] = 0;
		belong[i] = 0;
	}
	
	for (int i = 1; i <= mid; i++){
		if (c[i] == 0){
			Add(Node(x[i],0),Node(y[i],1));
			Add(Node(y[i],0),Node(x[i],1));
		}
		if (c[i] == 1){
			Add(Node(x[i],0),Node(y[i],0));
			Add(Node(x[i],1),Node(y[i],1));
			Add(Node(y[i],0),Node(x[i],0));
			Add(Node(y[i],1),Node(x[i],1));
		}
		if (c[i] == 2){
			Add(Node(x[i],1),Node(y[i],0));
			Add(Node(y[i],1),Node(x[i],0));
		}
	}
	
	for (int i = 1; i <= tot; i++)
		if (!belong[i]){
			Tarjan(i);
		}
	for (int i = 1; i <= n; i++)
		if (belong[i * 2] == belong[i * 2 - 1]) return 0;
	return 1;
}

int main(){
		
	scanf("%d", &Case);
	while (Case > 0){
		Case--;
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; i++){
			scanf("%d%d%d", &x[i], &y[i], &c[i]);
			x[i]++; y[i]++;
		}
		int Le = 0, Ri = m;
		int Ans = 0;
		while (Le <= Ri){
			int Mid = (Le + Ri) >> 1;
			if (Solve(Mid)){
				Ans = Mid;
				Le = Mid + 1;
			} else
				Ri = Mid - 1;
		}
		printf("%d\n", Ans);
	}
	
	return 0;
}