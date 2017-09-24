#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 55;
const int T = N * 10;
const int INF = 99999999;
const int M = T * T * 2;

int n[5], m[5];
bool flag[5][N][N];
int id[5][N][2];
int s, t, tot;
int g[T], adj[M], nxt[M], f[M];
int cnt[T], dist[T], cur[T], fa[T], dat[T];

void Ins(int x, int y, int ff, int rf){
	adj[++tot] = y; nxt[tot] = g[x]; g[x] = tot; f[tot] = ff;
	adj[++tot] = x; nxt[tot] = g[y]; g[y] = tot; f[tot] = rf;
}

int sap(int s, int t){
	int x, sum;
	
	for (int i = 1; i <= t; i++){
		dist[i] = 1;
		cur[i] = g[i];
		fa[i] = 0;
		dat[i] = 0;
		cnt[i] = 0;
	}
	
	cnt[0] = 1; cnt[1] = t - 1;
	dist[t] = 0;
	dat[s] = INF;
	x = s;
	sum = 0;
	while (1){
		int p;
		for (p = cur[x]; p; p = nxt[p]){
			if (f[p] > 0 && dist[adj[p]] == dist[x] - 1) break;
		}
		
		if (p > 0){
			cur[x] = p;
			fa[adj[p]] = p;
			dat[adj[p]] = min(dat[x], f[p]);
			x = adj[p];
			if (x == t){
				sum += dat[x];
				while (x != s){
					f[fa[x]] -= dat[t];
					f[fa[x] ^ 1] += dat[t];
					x = adj[fa[x] ^ 1];
 				}
			}
		} else {
			cnt[dist[x]] --;
			if (cnt[dist[x]] == 0) return sum;
			
			dist[x] = t + 1;
			for (int p = g[x]; p; p = nxt[p]){
				if (f[p] > 0 && dist[adj[p]] + 1 < dist[x]){
					dist[x] = dist[adj[p]] + 1;
					cur[x] = p;
				}
			}
			
			cnt[dist[x]]++;
			if (dist[s] > t) return sum;
			if (x != s) x = adj[fa[x] ^ 1];
 		}
	}
}

int main(){

	while (1){
		scanf("%d%d%d%d%d%d%d", &n[1], &n[2], &n[3], &n[4], &m[2], &m[3], &m[4]);
		if (n[1] == -1 && n[2] == -1 && n[3] == -1) break;
		
		memset(flag, 0, sizeof(flag));
		
		for (int i = 2; i <= 4; i++){
			for (int j = 1; j <= n[i]; j++){
				int k;
				scanf("%d", &k);
				for (int l = 1; l <= k; l++){
					int x;
					scanf("%d", &x);
					
					flag[i][j][x] = 1;
				}
			}				
		}
		
		
		int point = 0;
		for (int i = 1; i <= 4; i++){
			for (int j = 0; j <= n[i]; j++){
				if (i == 1 && j == 0) continue;
		
				
				id[i][j][0] = ++point;
				id[i][j][1] = ++point;
			}
		}
		
		s = point + 1; t = s + 1;
		
		tot = 1;
		for (int i = 1; i <= t; i++) g[i] = 0;
		
		for (int i = 1; i <= 4; i++){
			for (int j = 0; j <= n[i]; j++){
				if (i == 1 && j == 0) continue;
				
				if (j == 0) Ins(id[i][j][0], id[i][j][1], m[i], 0);
				else Ins(id[i][j][0], id[i][j][1], 1, 0);
			}
		}
		
		for (int i = 1; i <= n[1]; i++)
			Ins(s, id[1][i][0], 1, 0);
			
		for (int i = 1; i <= n[4]; i++)
			Ins(id[4][i][1], t, 1, 0);
		Ins(id[4][0][1], t, INF, 0);
		
		for (int i = 1; i <= 3; i++){
			for (int j = 1; j <= n[i]; j++){
				Ins(id[i][j][1], id[i + 1][0][0], INF, 0);
			}
		}
		
		for (int i = 2; i <= 3; i++){
			for (int j = 1; j <= n[i + 1]; j++){
				Ins(id[i][0][1], id[i + 1][j][0], INF, 0);
			}
		}
		
		for (int i = 2; i <= 4; i++){
			for (int j = 1; j <= n[i]; j++){
				for (int k = 1; k <= n[i - 1]; k++)
				if (flag[i][j][k] == 1){
					Ins(id[i - 1][k][1], id[i][j][0], 1, 0);
				}
			}
		}
		
		printf("%d\n", sap(s, t));
	}

	return 0;
}
