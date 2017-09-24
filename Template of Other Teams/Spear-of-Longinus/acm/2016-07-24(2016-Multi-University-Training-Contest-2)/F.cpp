#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int N = 600005;
const int M = 200005;
const int Mo = 1000000007;

vector<int> G[N], E[N];
int Case, n, m, tot, dfc, Root, block, Total, cnt, Cut;
int w[N];
int g[N], adj[M * 2], nxt[M * 2];
int dfn[N], belong[N], low[N], Real_dep[N], stack[N], dep[N], fa[N], mult[N], sum[N], root[N], size[N];
bool Vis[N], iscut[N];

void Ins(int x, int y){
	adj[++tot] = y; nxt[tot] = g[x]; g[x] = tot;
	adj[++tot] = x; nxt[tot] = g[y]; g[y] = tot;
}

int qm(int x, int y){
	if (!y) return 1;
	int Ret = qm(x, y >> 1);
	Ret = (1LL * Ret * Ret) % Mo;
	if (y & 1) Ret = (1LL * Ret * x) % Mo;
	return Ret;
}

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
		if (i  ^ lst != 1) low[x] = min(low[x], dfn[adj[i]]);
	}
	if (x == Root && son == 1) iscut[x] = 0, belong[x] = E[x][0];
	if (x == Root && son == 0){
		++block;
		belong[x] = block + n;
	}
}

void Prepare(int x,int Fa){
	Vis[x] = 1;
	fa[x] = Fa;
	sum[x] = 0;
	mult[x] = w[x];
	root[x] = Root;
	for (int i = 0; i < (int)G[x].size(); i++){
		int y = G[x][i];
		if (y == Fa) continue;
		Prepare(y, x);
		sum[x] = (sum[x] + mult[y]) % Mo;
		mult[x] = (1LL * mult[x] * mult[y]) % Mo;
	}
}

int main(){
	
	scanf("%d", &Case);
	while (Case > 0){
		Case--;
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
		
		tot = 1;
		block = 0;
		cnt = 0;
		for (int i = 1; i <= n * 3; i++){
			g[i] = 0;
			iscut[i] = 0;
			G[i].clear();
			E[i].clear();
			belong[i] = 0;
			size[i] = 0;
			low[i] = dfn[i] =0;
		}
		
		for (int i = 1; i <= m; i++){
			int x, y;
			scanf("%d%d", &x, &y);
			Ins(x,y);
		}
		
		dfc = 0;
		for (int i = 1; i <= n; i++)
			if (dfn[i] == 0){
				Root = i;
				Dfs(i, 0);
			}
		/*for(int i = 1; i <= n; i++) {
			printf("!!!%d\n", i);
			for(int j = 0; j < E[i].size(); j++) {
				printf("%d ", E[i][j]);
			} 
			puts("");
		}*/
		/*for (int i = 1; i <= n; i++){
			printf("belong[%d] = %d  iscut[%d] = %d\n", i, belong[i], i, iscut[i]);
		}*/
		//printf("%d\n", dfn[3]);
		
		for (int i = n + 1; i <= n + block; i++)
			w[i] = 1;
		Cut = 0;
		//printf("%d %d\n", n, block);
		for (int i = 1; i <= n; i ++)
			if (iscut[i]){
				++Cut;
				belong[i] = n + block + Cut;
				for (int j = 0; j < E[i].size(); j++){
					G[n + block + Cut].push_back(E[i][j]);
					G[E[i][j]].push_back(n + block + Cut);
				}
				w[n + block + Cut] = w[i];
			} else {
				w[belong[i]] = (1LL * w[belong[i]] * w[i]) % Mo;
			}
		
		
		for (int i = 1; i <= n + block + Cut; i ++) Vis[i] = 0;
		
		for (int i = 1; i <= n; i++)
			size[belong[i]]++;
		
		/*for (int i = 1; i <= n; i++){
			printf("belong[%d] = %d  iscut[%d] = %d\n", i, belong[i], i, iscut[i]);
		}*/
		
		Total = 0;
		for (int i = 1; i <= n + block + Cut; i ++){
			if (belong[i] || iscut[i]) continue;
			if (Vis[i]) continue;
			Root = i;
			Prepare(i, 0);
			Total = (Total + mult[Root]) % Mo;
		}
		
		/*for (int i = 1; i <= n + block + Cut; i ++){
			printf("%d fa = %d  mult = %d sum = %d  w = %d\n",i,fa[i],mult[i],sum[i],w[i]);
		}*/
		
		int Ans = 0;
		
		for (int i = 1; i <= n; i++){
			if (g[i] == 0){
				int Ret = (Total - mult[root[belong[i]]] + Mo) % Mo;
				
				//printf("i = %d Ret = %d\n", i, Ret);
				Ans = (Ans + (1LL * Ret % Mo * i) % Mo) % Mo;
				continue;
			}
			if (!iscut[i]){
				int This = mult[root[belong[i]]];
				This = (1LL * This * qm(w[i], Mo - 2)) % Mo;
				//if (size[belong[i]] == 1 && root[belong[i]] == belong[i]) This = 0;
				int Ret = (Total - mult[root[belong[i]]] + Mo) % Mo;
				
				//printf("i = %d This = %d Ret = %d\n", i, This , Ret);
				Ans = (Ans + (1LL * (This + Ret) % Mo * i) % Mo) % Mo;
				
			} else {
				int This = (sum[belong[i]] + (1LL * mult[root[belong[i]]] * qm(mult[belong[i]], Mo - 2)) % Mo) % Mo;
				if (belong[i] == root[belong[i]]) This = sum[belong[i]];
				int Ret = (Total - mult[root[belong[i]]] + Mo) % Mo;
				
				//if (belong[i] == root[belong[i]]) This = 0;
				//printf("i = %d Ans = %d\n", i, This + Ret);
				Ans = (Ans + (1LL * (This + Ret) % Mo * i) % Mo) % Mo;
			}
		}
		
		printf("%d\n", (Ans + Mo) % Mo);
		
	}
	
	return 0;
}
