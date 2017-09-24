#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 1005;
const int M = 4500010;

int n, m, Case, tot, tmp, times;
int sum[2][N];
int a[N], col[N];
int Ans[500005];
int tree[M];
int cnt[2][2];
int P[M];

struct node{
	int time;
	int l,r;
	int id;
}Q[M];


bool cmp(node a, node b){
	if (a.time != b.time) return a.time < b.time;
	return a.id < b.id;
}


int lowbit(int x){
	return (x & (-x));
}

void add(int x,int ret){
	while (x <= tmp){
		tree[x] += ret;
		x += (x & (-x));
	}
}

int find(int x){
	int ret = 0;
	while (x > 0){
		ret += tree[x];
		x -= (x & (-x));
	}
	return ret;
}

int main(){
	scanf("%d", &Case);
	while (Case > 0){
		--Case;
		scanf("%d%d", &n, &m);
		
		for (int i = 0; i <= n + 1; i++)
			a[i] = col[i] = 0;
		
		for (int i = 1; i <= n; i++){
			scanf("%d", &a[i]);
			col[i] = (i - 1) % 2;
		}
		
		sum[0][0] = sum[1][0] = 0;
		for (int i = 1; i <= n; i++){
			sum[0][i] = sum[0][i - 1];
			sum[1][i] = sum[1][i - 1];
			
			sum[col[i]][i] += a[i];
		}
		
		tot = 0;
		
		for (int i = 1; i <= n + 1; i++){
			for (int j = i; j <= n + 1; j++){
				for (int k = 0; k < 2; k++)
					cnt[k][0] = sum[k][j - 1] - sum[k][i - 1];
				
				int le = i - 1;
				int ri = j;
				
				cnt[0][1] = cnt[0][0];
				cnt[1][1] = cnt[1][0];
				
				cnt[col[le]][1] += a[le];
				cnt[col[ri]][1] += a[ri];
				
				
				++tot;
				Q[tot].time = cnt[0][0];
				Q[tot].l = cnt[1][0];
				Q[tot].r = cnt[1][1] + 1;
				Q[tot].id = 1;
				
				++tot;
				Q[tot].time = cnt[0][1] + 1;
				Q[tot].l = cnt[1][0];
				Q[tot].r = cnt[1][1] + 1;
				Q[tot].id = 2;
			}
		}
		
		for (int i = 1; i <= m; i++){
			int x, y;
			scanf("%d%d", &x, &y);
			++tot;
			Q[tot].time = x;
			Q[tot].l = y;
			Q[tot].r = i;
			Q[tot].id = 3;
		}
		
		tmp = 0;
		
		for (int i = 1; i <= tot; i++){
			++tmp;
			P[tmp] = Q[i].l;
			
			if (Q[i].id == 3) continue;
			++tmp;
			P[tmp] = Q[i].r;
		}
		
		sort(P + 1, P + 1 + tmp);
		tmp = unique(P + 1, P + 1 + tmp) - P - 1;
		
		for (int i = 1; i <= tot; i++){
			Q[i].l = lower_bound(P + 1, P + 1 + tmp, Q[i].l) - P;
			if (Q[i].id == 3) continue;
			Q[i].r = lower_bound(P + 1, P + 1 + tmp, Q[i].r) - P;
		}
		
		
		sort(Q + 1, Q + 1 + tot, cmp);
		
		for (int i = 1; i <= tot; i++){
			
			if (Q[i].id == 1){
				add(Q[i].l, 1);
				add(Q[i].r, -1);
				continue;
			}
			if (Q[i].id == 2){
				add(Q[i].l, -1);
				add(Q[i].r, 1);
				continue;
			}
			if (Q[i].id == 3){
				int Ret = find(Q[i].l);
				if (Ret > 0) Ans[Q[i].r] = 1; else Ans[Q[i].r] = 0;
				continue;
			}
		}
		
		for (int i = 1; i <= m; i++)
			printf("%d", Ans[i]);
		printf("\n");
	}
	return 0;
}