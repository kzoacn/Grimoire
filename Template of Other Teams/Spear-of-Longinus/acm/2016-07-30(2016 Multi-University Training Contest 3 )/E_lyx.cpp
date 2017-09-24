#pragma comment(linker, "/STACK:1024000000,1024000000") 
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 50005;
const int INF = 999999999;

int n, m, tot, dfc, tree_cnt, ii;
int LE, RI, Ans;
int k, p, t;
int g[N], adj[N * 2], nxt[N * 2];
int fa[N], dfn[N], ri[N], dep[N], root[N];


struct node1{
    int l, r;
}Seg[N];

struct node{
    int lson, rson;
    int size, Max, Min, sum;
    int lazy;
}tree[N * 100];

inline void Ins(int x, int y){
    adj[++tot] = y; nxt[tot] = g[x]; g[x] = tot;
}

inline void Prep(int x){
    dfn[x] = ++dfc;
    for (int i = g[x]; i; i = nxt[i]){
        if (adj[i] == fa[x]) continue;
        
        fa[adj[i]] = x;
        dep[dfc + 1] = dep[dfn[x]] + 1;
        
        Prep(adj[i]);
    }
    ri[x] = dfc;
}

inline void make(int s, int Size, int W){
    tree[s].size = Size;
    tree[s].lazy = 0;
    tree[s].Min = tree[s].Max = tree[s].sum = W;
}

inline void update(int s){
    int Le = tree[s].lson, Ri = tree[s].rson;
    
    tree[s].sum = tree[Le].sum + tree[Ri].sum + tree[s].lazy * tree[s].size;
    tree[s].Max = max(tree[Le].Max, tree[Ri].Max) + tree[s].lazy;
    tree[s].Min = min(tree[Le].Min, tree[Ri].Min) + tree[s].lazy;
    
}

inline void build(int s, int x, int y){
    
    tree_cnt = max(tree_cnt, s);
    
    if (x == y) {
        make(s, 1, dep[x]);
        return;
    }
    
    make(s, y - x + 1, 0);
    
    int t = s + s;
    int mid = (x + y) >> 1;
    
    tree[s].lson = t;
    build(t, x, mid);
    
    tree[s].rson = t + 1;
    build(t + 1, mid + 1, y);
    
    update(s);
}

inline void add(int s, int w){
    tree[s].lazy += w;
    tree[s].sum += tree[s].size * w;
    tree[s].Max += w;
    tree[s].Min += w;
}

inline void Insert(int lst, int cur, int x, int y){
    tree[cur] = tree[lst];
    
    if (LE <= x && y <= RI){
        add(cur, -1);
        return;
    }
    
    if (RI < x || LE > y){
        add(cur, 1);
        return;
    }
    
    int mid = (x + y) >> 1;
    
    ++tree_cnt;
    tree[cur].lson = tree_cnt;
    Insert(tree[lst].lson, tree[cur].lson, x, mid);
    
    ++tree_cnt;
    tree[cur].rson = tree_cnt;
    Insert(tree[lst].rson, tree[cur].rson, mid + 1, y);
    
    
    update(cur);
}

inline void Query(int s, int x, int y, int lazy){
    if (LE <= x && y <= RI){
        if (t == 1) Ans += tree[s].sum + lazy * tree[s].size;
        if (t == 2) Ans = min(Ans, tree[s].Min + lazy);
        if (t == 3) Ans = max(Ans, tree[s].Max + lazy);
        
        return;
    }
    
    int mid = (x + y) >> 1;
    if (LE <= mid) Query(tree[s].lson, x, mid, lazy + tree[s].lazy);
    if (RI > mid) Query(tree[s].rson, mid + 1, y, lazy + tree[s].lazy);
}

inline void Calc(int x){
    for (int i = g[x]; i; i = nxt[i]){
        if (adj[i] == fa[x]) continue;
        
        LE = dfn[adj[i]];
        RI = ri[adj[i]];
        
        ++tree_cnt;
        root[adj[i]] = tree_cnt;
        Insert(root[x], root[adj[i]], 1, n);
        
        Calc(adj[i]);
    }
}

inline bool cmp(node1 a, node1 b){
    return a.l < b.l;
}

int main(){
    
    while (scanf("%d%d", &n, &m) != EOF){
        tot = 0;
        for (int i = 1; i <= n; i++) g[i] = 0;
        
        for (int i = 1; i < n; i++){
            int u, v;
            scanf("%d%d", &u, &v);
            Ins(u, v);
            Ins(v, u);
        }
        
        dfc = 0;
        dep[1] = 0;
        fa[1] = 0;
        Prep(1);
        
        
        tree_cnt = 1;
        build(1, 1, n);
        root[1] = 1;
        
        Calc(1);
        
        Ans = 0;
        for (ii = 1; ii <= m; ii++){
            scanf("%d%d%d", &k, &p, &t);
            if (Ans == -1) Ans = 0;
            p = (p + Ans) % n + 1;
                
            for (int i = 1; i <= k; i ++){
                int x;
                scanf("%d", &x);
                Seg[i].l = dfn[x]; Seg[i].r = ri[x];
                
                if (x == 1) Ans = -1;
            }
            
            if (Ans == -1){
                printf("-1\n");
                continue;
            }
            
            sort(Seg + 1, Seg + 1 + k, cmp);
            
            int Realk = 0;
            
            if (k > 0){
                Realk = 1;
                for (int i = 2; i <= k; i++)
                    if (Seg[i].l > Seg[Realk].r) Seg[++Realk] = Seg[i];
            }
            
            Seg[0].r = 0;
            Seg[Realk + 1].l = n + 1;
            
            if (t == 2) Ans = INF;
            else Ans = 0;
            
            for (int i = 0; i <= Realk; i++){
                LE = Seg[i].r + 1;
                RI = Seg[i + 1].l - 1;
                
                if (LE > RI) continue;
                
                Query(root[p], 1, n, 0);
            }
            
            printf("%d\n", Ans);
        
        }
        
    }

    return 0;
}
