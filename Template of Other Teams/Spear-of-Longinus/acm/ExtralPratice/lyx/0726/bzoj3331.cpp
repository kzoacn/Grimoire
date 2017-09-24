#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
 
using namespace std;
 
const int N = 200005;
const int M = 400005;
 
int n, m, q, tot, dfc, block, top;
int g[N], adj[M], nxt[M];
int dfn[N], low[N], stack[N], belong[N], Ans[N], Dep[N];
int Fa[N][20];
 
vector<int> E[N], G[N];
 
void Ins(int x, int y){
    adj[++tot] = y; nxt[tot] = g[x]; g[x] = tot;
}
 
void Tarjan(int x, int lst){
    dfn[x] = ++dfc;
    low[x] = dfn[x];
    stack[++top] = x;
     
    for (int i = g[x]; i; i = nxt[i]){
        if (!dfn[adj[i]]){
            Tarjan(adj[i], i);
            low[x] = min(low[x], low[adj[i]]);
            if (low[adj[i]] >= dfn[x]){
                int Tmp;
                ++block;
                E[x].push_back(block + n);
                do{
                    Tmp = stack[top --];
                    belong[Tmp] = block + n;
                     
                    E[Tmp].push_back(block + n);
                }while (Tmp != adj[i]);
            }
        }
        else
        if (i ^ lst != 1) low[x] = min(low[x], dfn[adj[i]]);
    }
}
 
void Dfs(int x ,int fa){
    Dep[x] = Dep[fa] + 1;
    Fa[x][0] = fa;
    for (int i = 1; i <= 18; i++)
        Fa[x][i] = Fa[Fa[x][i - 1]][i - 1];
    for (int i = 0; i < G[x].size(); i++){
        if (G[x][i] == fa) continue;
        Dfs(G[x][i], x);
    }
}
 
int Get(int u, int v) {
    if (Dep[u] < Dep[v]) swap(u, v);
     
    for (int i = 18; i + 1; i --) 
        if (Dep[Fa[u][i]] >= Dep[v]) u = Fa[u][i];
    if (u == v) return u;
     
    for (int i = 18; i + 1; i --)
        if (Fa[u][i] != Fa[v][i]) u = Fa[u][i], v = Fa[v][i];
    return Fa[u][0];
}
 
void Solve(int x) {
    for (int i = 0; i < G[x].size(); i++) {
        int y = G[x][i];
        if (y == Fa[x][0]) continue;
        Solve(y);
        Ans[x] += Ans[y];
    }
}
 
 
int main(){
     
    scanf("%d%d%d", &n, &m, &q);
     
    tot = 1;
     
    for (int i = 1; i <= m; i++){
        int u, v;
        scanf("%d%d", &u, &v);
        Ins(u, v);
        Ins(v, u);
    }
     
    dfc = 0;
    block = 0;
    top = 0;
     
    Tarjan(1, 0);
     
    for (int i = 1; i <= n; i ++){
        for (int j = 0; j < E[i].size(); j++){
            G[i].push_back(E[i][j]);
            G[E[i][j]].push_back(i);
        }
    }
     
    for (int i = 1; i <= n + block; i++) Ans[i] = 0;
     
    Dep[0] = 0;
    Dfs(1, 0);
     
    for (int i = 1; i <= q; i++){
        int u, v;
        scanf("%d%d", &u, &v);
        int Lca = Get(u, v);
        Ans[u]++;
        Ans[v]++;
        Ans[Lca]--;
        Ans[Fa[Lca][0]]--;
    }
     
    Solve(1);
    for (int i = 1; i <= n; i++)
        printf("%d\n", Ans[i]);
     
    return 0;
}
?