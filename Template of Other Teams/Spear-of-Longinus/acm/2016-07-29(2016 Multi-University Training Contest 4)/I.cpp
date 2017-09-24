#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 105;
const int T = N * N;
const int M = T * T;
const int INF = 99999999;

int n, tot, Ans;
char st[N];
int g[T], adj[M], nxt[M], f[M];
int id[N][N], w[N][N];
int a[N], b[N];
int cnt[T], dist[T], cur[T], fa[T], dat[T];

void add(int x, int y, int z){
	adj[++tot] = y; nxt[tot] = g[x]; g[x] = tot; f[tot] = z;
	adj[++tot] = x; nxt[tot] = g[y]; g[y] = tot; f[tot] = 0;
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
			cnt[dist[x]]--;
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
			if (x != s ) x = adj[fa[x] ^ 1];
		}
		
	}
	
}

int main(){

	int Case;
	scanf("%d", &Case);
	for (int ii = 1; ii <= Case; ii++){
		scanf("%d", &n);
		scanf("%s", st + 1);
		
		for (int i = 0; i <= 9; i++)
			scanf("%d%d", &a[i], &b[i]);
			
		Ans = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++){
				scanf("%d", &w[i][j]);
				Ans += w[i][j];
			}

		
		int s, t;
		
		s = n * (n - 1) / 2 + n + 10 + 1;
		t = s + 1;
		
		tot = 1;
		for (int i = 1; i <= t; i++)
			g[i] = 0;
		
		int tmp = 0;
		for (int i = 1; i <= n; i++)
			for (int j = i + 1; j <= n; j++){
				id[i][j] = ++tmp;
				add(s, id[i][j], w[i][j] + w[j][i]);
				add(id[i][j], n * (n - 1) / 2 + i, INF);
				add(id[i][j], n * (n - 1) / 2 + j, INF);
			}
		
		for (int i = 1; i <= n; i++){
			int num = st[i] - '0' + 1;
			add(n * (n - 1) / 2 + i, n * (n - 1) / 2 + n + num, INF);
			add(n * (n - 1) / 2 + i, t, a[num - 1]);
		}
		
		for (int i = 0; i <= 9; i++){
			add(n * (n - 1) / 2 + n + i + 1,  t,  b[i] - a[i]);
		}
		
		printf("Case #%d: %d\n", ii, Ans - sap(s, t));
		
	}

	return 0;
}
