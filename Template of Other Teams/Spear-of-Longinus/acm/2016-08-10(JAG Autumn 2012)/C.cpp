#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 1005;
const int M = 10005;

struct node{
	int s, t, c;
}edge[M];

int n, m;
int fa[N];

bool cmp(node a, node b){
	return a.c < b.c;
}

int Get(int x){
	if (x == fa[x]) return x;
	fa[x] = Get(fa[x]);
	return fa[x];
}

bool judge(int x, int y){
	int fx = Get(x);
	int fy = Get(y);
	
	if (fx == fy) return 0;
	fa[fy] = fx;
	return 1;
}

int main(){
	
	while (scanf("%d%d", &n, &m) == 2){
		if (n == 0 && m == 0) break;
		for (int i = 1; i <= m; i++)
			scanf("%d%d%d", &edge[i].s, &edge[i].t, &edge[i].c);
		
		sort(edge + 1, edge + 1 + m, cmp);
		
		for (int i = 1; i <= n; i++)
			fa[i] = i;
		
		int cnt = 0;
		int Ans = -1;
		for (int i = 1; i <= m; i++){
			if (judge(edge[i].s, edge[i].t)){
				++cnt;
				if (cnt == (n - 2) / 2 + 1){
					Ans = edge[i].c; 
					break;
				}
			}
		}
		printf("%d\n", Ans);
	}
	
	return 0;
}
