#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

typedef long long LL;

const int N = 20005;
const int M = 40005;

int g[N], adj[M * 2], nxt[M * 2], len[M * 2], dfn[N], low[N], Start[N], Size[N], id[N];
bool bridge[M * 2], Vis[N], Can[N];
LL cnt[M * 2];
int n, m, dfc, tot, block;

void Ins(int x, int y, int z){
	adj[++tot] = y; nxt[tot] = g[x]; len[tot] = z; g[x] = tot;
}

void Tarjan(int x, int lst){
	dfn[x] = ++dfc;
	low[x] = dfn[x];
	Size[block]++;
	id[x] = block;
	
	for (int i = g[x]; i; i = nxt[i]){
		if (!dfn[adj[i]]){
			Tarjan(adj[i], i);
			low[x] = min(low[x], low[adj[i]]);
			if (low[adj[i]] > dfn[x]){
			
				bridge[i] = bridge[i ^ 1] = 1;
				cnt[i] = cnt[i ^ 1] = (dfc - dfn[adj[i]] + 1);
				//printf("%d %d %lld\n", x, adj[i], cnt[i]);
				
			}
		}
		else
		if ((i ^ lst) != 1) {
			low[x] = min(low[x], dfn[adj[i]]);
		}
	}
	
}

bool Solve(int x, LL val, LL up){
	LL Cur = Start[x];
	Vis[x] = 1;
	LL size = Size[id[x]];
	
	for (int i = g[x]; i; i = nxt[i]){
		if (!bridge[i]) continue;
		if (Vis[adj[i]]) continue;
		
		int y = adj[i];
		LL Tmp = 1LL * cnt[i] * (size - cnt[i]) * 1LL * len[i];
		
		if (!Solve(adj[i], Tmp, up)) return 0;
		if (!Can[adj[i]]) Cur += Tmp;
		
	}
	
	if (Cur > up) return 0;
	if (Cur + val <= up) {
		Can[x] = 1;
	}
	
	return 1;
}

bool Check(LL up){
	
	for (int i = 1; i <= n; i++) Vis[i] = 0, Can[i] = 0;
	
	for (int i = 1; i <= n; i++){
		if (Vis[i]) continue;
		if ( !Solve(i, 0, up) ) return 0; 
	}
	
	return 1;
	
}

int main(){

	int Case;
	scanf("%d", &Case);
	
	for (int ii = 1; ii <= Case; ii++){
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) scanf("%d", &Start[i]);

		tot = 1;
		for (int i = 1; i <= n; i++) {
			g[i] = 0;
			low[i] = 0;
			dfn[i] = 0;
			Size[i] = 0;
		}
		
		for (int i = 1; i <= m * 2 + 1; i ++)
			bridge[i] = 0;

		for (int i = 1; i <= m; i++){
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			Ins(u, v, w);
			Ins(v, u, w);
		}

		block = 0;
		dfc = 0;
		for (int i = 1; i <= n; i++){
			if (dfn[i]) continue;
			Size[++block] = 0;
		
			Tarjan(i, 0);
		}
		
		//for (int i = 1; i <= n; i++){
		//	printf("i = %d dfn = %d low = %d\n",i,dfn[i],low[i]);
		//}
		
		//printf("%d\n", tot);
		//printf("%d %d\n",bridge[2],bridge[3]);
		
		//printf("%d\n", block);
		//for (int i = 1; i <= block; i++){
		//	printf("%d\n", Size[i]);
		//}
		
		
		LL Le = 0, Ri = 1e16;
		LL Mid, Ans = -1;
		
		while (Le <= Ri){
			Mid = (Le + Ri) >> 1;
			//printf("%lld\n",Mid);
			if ( Check(Mid) ){
				Ans = Mid;
				Ri = Mid - 1;
			} else 
				Le = Mid + 1;
		}
		
		printf("Case %d: %lld\n", ii, Ans);
		
	}

}
