#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

typedef long long LL;

const int N = 100005;
const int S = 25;

struct node{
	int L, R, Lson, Rson, Sum;
}tree[N * 25];

int a[N];
int n, m, tot, dfc, cnt;
LL Total, Ans;
int g[N], adj[N], nxt[N];
int fa[N], Size[N], dfn[N], Ri[N], val[N];
int Mid[N], Mid_nxt[N];
int root[N];

LL Sum[N];



void Ins(int x, int y){
	adj[++tot] = y; nxt[tot] = g[x]; g[x] = tot;
}

void Prep(int x){
	Size[x] = 1;
	dfn[x] = ++dfc;
	val[dfn[x]] = a[x]; 
	for (int i = g[x]; i; i = nxt[i]){
		Prep(adj[i]);
		Size[x] += Size[adj[i]];
	}
	Ri[x] = dfc;
}

int Build(int L, int R){
	int s = ++cnt;
	tree[s].L = L;
	tree[s].R = R;
	tree[s].Lson = 0;
	tree[s].Rson = 0;
	tree[s].Sum = 0;
	
	if (L == R) return s;
	
	int mid = (L + R) >> 1;
	tree[s].Lson = Build(L, mid);
	tree[s].Rson = Build(mid + 1, R);
	
	return s;
}

int Same(int x){
	++cnt;
	tree[cnt] = tree[x];
	return cnt; 
}

int Add(int Lst, int pos){
	int s = Same(Lst);
	
	tree[s].Sum++;
	
	if (tree[s].L == tree[s].R) return s;
	
	int mid = (tree[s].L + tree[s].R) >> 1;
	if (pos <= mid) tree[s].Lson = Add(tree[Lst].Lson, pos);
	else tree[s].Rson = Add(tree[Lst].Rson, pos);
	
	return s;
}

int Find(int Lst, int Cur, int L, int R, int k){
	if (L == R) return L;
	
	int mid = (L + R) >> 1;
	
	int Le = tree[tree[Cur].Lson].Sum - tree[tree[Lst].Lson].Sum;
	
	if (Le >= k) return Find(tree[Lst].Lson, tree[Cur].Lson, L, mid, k);
	
	k -= Le;
	return Find(tree[Lst].Rson, tree[Cur].Rson, mid + 1, R, k);
}

void Change(int x, LL val){
	while (x > 0){
		Sum[x] += val;
		x -= (x & (-x));
	}
}

LL Ask(int x){
	LL Ret = 0;
	while (x <= m){
		Ret += Sum[x];
		x += (x & (-x));
	}
	return Ret;
}

void Dfs(int x){
	
	//printf("%d %d\n", Mid[x], Mid_nxt[x] - Mid[x]);
	Change(Mid[x], Mid_nxt[x] - Mid[x]);
	
	LL Cur = Total + Ask(a[x]);
	Ans = max(Ans, Cur);
	
	for (int i = g[x]; i; i = nxt[i]){
		Dfs(adj[i]);
	}
	
	Change(Mid[x], -(Mid_nxt[x] - Mid[x]));
	
}

int main(){
	
	while (scanf("%d", &n) == 1){
		m = 0;
		for (int i = 1; i <= n; i++){
			scanf("%d", &a[i]);
			m = max(m, a[i]);
		}
		
		tot = 0;
		for (int i = 1; i <= n; i++)
			g[i] = 0;
		
		for (int i = 2; i <= n; i++){
			scanf("%d", &fa[i]);
			Ins(fa[i], i);
		}
		
		fa[1] = 0;
		dfc = 0;
		Prep(1);
		
		cnt = 0;
		root[0] = Build(1, m);
		for (int i = 1; i <= n; i++)
			root[i] = Add(root[i - 1], val[i]);
		
		Total = 0;
		for (int i = 1; i <= n; i++){
			int kth = (Size[i] + 1) >> 1;
			
			Mid[i] = Find(root[dfn[i] - 1], root[Ri[i]], 1, m, kth);
			Total += Mid[i];
			
			//printf("%d %d %d\n", i, dfn[i], Ri[i]);
			if (dfn[i] == Ri[i]) {
				Mid_nxt[i] = 100000;
			}
			else{
				//printf("%d %d\n", dfn[i] - 1, Ri[i]);
				Mid_nxt[i] = Find(root[dfn[i] - 1], root[Ri[i]], 1, m, kth + 1);
			}
		}
		
		/*for (int i = 1; i <= n; i++)
			printf("%d %d\n", Mid[i], Mid_nxt[i]);*/
		
		Ans = 0;
		Dfs(1);
		
		cout << Ans << endl;
			
	}
	
	return 0;
}
