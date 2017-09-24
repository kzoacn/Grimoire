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
/*
tot = 1
edges' id start from 2
remember to clean g
t is the number of points
*/
