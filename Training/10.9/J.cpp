#include <bits/stdc++.h>

using namespace std;

template <class T>
void scan(T &x) {
	register char ch; x = 0;
	for (ch = getchar(); ~ch && (ch < '0' || ch > '9'); ch = getchar());
	for (; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
}

const int maxn = 100005;

int n;

vector<int> G[maxn];

int fa[maxn][17], depth[maxn];
int sz[maxn];

void DFS(int now) {
	sz[now] = 1;
	for (int i = 1; i < 17; ++i)
		fa[now][i] = fa[fa[now][i - 1]][i - 1];
	for (int to: G[now]) {
		if (to == fa[now][0]) continue;
		fa[to][0] = now;
		depth[to] = depth[now] + 1;
		DFS(to);
		sz[now] += sz[to];
	}
}

// -------- sys

inline int __lca(int u, int v) {
	if (depth[u] < depth[v]) swap(u, v);
	int dep_delta = depth[u] - depth[v];
	for (int i = 0; i < 17; ++i)
		if ((dep_delta >> i) & 1) u = fa[u][i];
	for (int i = 16; i >= 0; --i)
		if (fa[u][i] != fa[v][i])
			u = fa[u][i], v = fa[v][i];
	return u == v ? u : fa[u][0];
}

inline int __son(int u, int fa) {
	int dep_delta = depth[u] - depth[fa] - 1;
	for (int i = 0; i < 17; ++i)
		if ((dep_delta >> i) & 1) u = ::fa[u][i];
	return u;
}

inline int __jump(int u, int dep) {
	for (int i = 0; i < 17; ++i)
		if ((dep >> i) & 1) u = fa[u][i];
	return u;
}

// --------

int Dist(int u, int v) {
	return depth[u] - depth[v] - depth[__lca(u, v)] * 2;
}	

int LCA(int root, int u, int v) {
	int res = __lca(u, v), tmp = __lca(u, root);
	if (depth[tmp] > depth[res]) res = tmp;
	tmp = __lca(v, root);
	if (depth[tmp] > depth[res]) res = tmp;
	return res;
}

int S(int root, int u) {
	int lca = __lca(root, u);
	if (lca != u) return sz[u];
	if(root==u)return n;
	return n - sz[__son(root, u)];
}

/*int F(int root, int u) {
	int lca = __lca(root, u);
	if (lca == root) {
		int dep_delta = (depth[u] - depth[root] - 1) >> 1;
		return sz[__jump(u, dep_delta)];
	}
	if (lca == u) {
		int dep_delta = (depth[root] - depth[u]) >> 1;
		return n - sz[__jump(root, dep_delta)];
	}
	if (depth[u] == depth[root]) return sz[__son(u, lca)];
	if (depth[u] < depth[root]) {
		int dep_delta = Dist(root, u) >> 1;
		return n - sz[__jump(root, dep_delta)];
	}
	int dep_delta = (Dist(root, u) - 1) >> 1;
	return sz[__jump(u, dep_delta)];
}	*/


int better(int a,int c){
	int lca=__lca(a,c);
	int x=depth[a]-depth[lca];
	int y=depth[c]-depth[lca];
	int l=x+y;
	if(x>=(l-1)/2){
		return __jump(a,(l-1)/2);	
	}else{
		return __jump(c,y-(l-1)/2+x);
	}
}

int notbetter(int a,int c){
	int lca=__lca(a,c);
	int x=depth[a]-depth[lca];
	int y=depth[c]-depth[lca];
	int l=x+y;
	if(x>=(l+1)/2){
		return __jump(a,(l+1)/2);	
	}else{
		return __jump(c,y-(l+1)/2+x);
	}
}

inline int F(int rt, int u) {
	int x = better(u, rt);
	return S(rt, x);
}

int f(int a,int b,int c){
	if(LCA(c,a,b)==a){
		int x=better(a,c);	
		int y=notbetter(a,b);
		return S(c,x)-S(c,y);
	}else 
	if(LCA(c,a,b)==b){
		return F(b,a);
	}else{
		int u=LCA(c,a,b);
		if(Dist(a,u)<min(Dist(b,u),Dist(c,u))){
			int x=better(a,c);	
			int y=notbetter(a,b);
			return S(c,x)-S(c,y);
		}else{
			return min(F(b,a),F(c,a));
		}
	}
}

int main() {
	int caseCnt; scan(caseCnt);
	for (int kase = 1; kase <= caseCnt; ++kase) {
		scan(n);
		for (int i = 1; i <= n; ++i)
			G[i].clear();
		
		for (int u, v, i = 1; i < n; ++i) {
			scan(u); scan(v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		
		DFS(1);
		
		int q;scanf("%d",&q);
		while(q--){
			int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			int ansa=f(a,b,c);
			int ansb=f(b,a,c);
			int ansc=f(c,a,b);
			
			printf("%d %d %d\n",ansa,ansb,ansc);
		}
	}
	
	return 0;
}
