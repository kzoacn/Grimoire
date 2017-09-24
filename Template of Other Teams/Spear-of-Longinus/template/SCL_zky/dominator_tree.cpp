#include<bits/stdc++.h>
using namespace std;
const int maxn=50010;
vector<int>G[maxn],rG[maxn],dom[maxn];
int n,m;
int dfn[maxn],rdfn[maxn],dfs_c,semi[maxn],idom[maxn],fa[maxn];
struct ufsets{
    int fa[maxn],best[maxn];
    int find(int x){
        if(fa[x]==x)
            return x;
        int f=find(fa[x]);
        if(dfn[semi[best[x]]]>dfn[semi[best[fa[x]]]])
            best[x]=best[fa[x]];
        fa[x]=f;
        return f;
    }
    int getbest(int x){
        find(x);
        return best[x];
    }
    void init(){
        for(int i=1;i<=n;i++)
            fa[i]=best[i]=i;
    }
}uf;
void init(){
    uf.init();
    for(int i=1;i<=n;i++){
        semi[i]=i;
        idom[i]=0;
        fa[i]=0;
        dfn[i]=rdfn[i]=0;
    }
    dfs_c=0;
}
void dfs(int u){
    dfn[u]=++dfs_c;
    rdfn[dfn[u]]=u;
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(!dfn[v]){
            fa[v]=u;
            dfs(v);
        }
    }
}
 
void tarjan(){
    for(int i=n;i>1;i--){
        int tmp=1e9;
        int y=rdfn[i];
        for(int i=0;i<rG[y].size();i++){
            int x=rG[y][i];
            tmp=min(tmp,dfn[semi[uf.getbest(x)]]);
        }
        semi[y]=rdfn[tmp];
        int x=fa[y];
        dom[semi[y]].push_back(y);
        uf.fa[y]=x;
        for(int i=0;i<dom[x].size();i++){
            int z=dom[x][i];
            if(dfn[semi[uf.getbest(z)]]<dfn[x])
                idom[z]=uf.getbest(z);
            else
                idom[z]=semi[z];
        }
        dom[x].clear();
    }
    semi[rdfn[1]]=1;
    for(int i=2;i<=n;i++){
        int x=rdfn[i];
        if(idom[x]!=semi[x])
            idom[x]=idom[idom[x]];
             
    }
    idom[rdfn[1]]=0;
}
 
int main(){
    while(scanf("%d%d",&n,&m)==2){
        for(int i=1;i<=n;i++){
            G[i].clear();
            rG[i].clear();
            dom[i].clear();
        }
     
        for(int i=1;i<=m;i++){
            int u,v;
            scanf("%d%d",&u,&v);
            G[u].push_back(v);
            rG[v].push_back(u);
        }
        init();
        dfs(1);
     
        tarjan();
 
        static int vis[maxn];
        memset(vis,0,sizeof vis);
        int ans=0;
        for(int i=2;i<=n;i++){
            if(!vis[idom[i]]){
                vis[idom[i]]=1;
                ans++;
            }
        }
        cout<<ans<<endl;
        for(int i=1;i<=n;i++)
            if(vis[i]){
                ans--;
                printf("%d%c",i," \n"[ans==0]);
            }
    }
    return 0;
}
