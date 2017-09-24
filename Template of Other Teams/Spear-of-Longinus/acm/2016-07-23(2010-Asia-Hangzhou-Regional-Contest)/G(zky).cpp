#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
const int maxn=300010;
int n,m;
vector<int>G[maxn];
vector<int>G2[maxn];
void add(int u,int v){
//    cerr<<u<<" "<<v<<endl;
    G[u].push_back(v);
    G[v].push_back(u);
}
int pre[maxn],iscut[maxn],bccno[maxn],dfs_clock,bcc_cnt,vis[maxn];
vector<int>bcc[maxn];
stack<pair<int,int> >S;
int dfs(int u,int fa){
    //cerr<<u<<endl;
    int lowu=pre[u]=++dfs_clock;
    int ch=0;
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        pair<int,int> e=make_pair(u,v);
        if(!pre[v]){
            S.push(e);
            ch++;
            int lowv=dfs(v,u);
            lowu=min(lowu,lowv);
            if(lowv>=pre[u]){
                iscut[u]=1;
                ++bcc_cnt;
                bcc[bcc_cnt].clear();
                while(1){
                    pair<int,int> x=S.top();S.pop();
                    if(bccno[x.first]!=bcc_cnt){
                        bcc[bcc_cnt].push_back(x.first);
                        bccno[x.first]=bcc_cnt;
                    }
                    if(bccno[x.second]!=bcc_cnt){
                        bcc[bcc_cnt].push_back(x.second);
                        bccno[x.second]=bcc_cnt;
                    }
                    if(x.first==u&&x.second==v)break;
                }
            }
        }else{
                if(pre[v]<pre[u]&&v!=fa){
                    S.push(e);
                    lowu=min(lowu,pre[v]);
                }
            }
    }
    if(fa<0&&ch==1)iscut[u]=0;
    return lowu;
}
int fa[maxn],top[maxn],siz[maxn],son[maxn],mp[maxn],z,dep[maxn],cnt[maxn],Tcut[maxn];
void dfs2(int u){
    siz[u]=1;cnt[u]=cnt[fa[u]]+Tcut[u];
    for(int i=0;i<G2[u].size();i++){
        int v=G2[u][i];
        if(v!=fa[u]){
            fa[v]=u;dep[v]=dep[u]+1;
            dfs2(v);
            siz[u]+=siz[v];
            if(siz[son[u]]<siz[v])son[u]=v;
        }
    }
}
void build(int u,int tp){
    top[u]=tp;mp[u]=++z;
    if(son[u])build(son[u],tp);
    for(int v,i=0;i<G2[u].size();i++)if((v=G2[u][i])!=son[u]&&v!=fa[u])build(v,v);
}
int lca(int u,int v){
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]])swap(u,v);
        u=fa[top[u]];
    }
    if(dep[u]<dep[v])return u;
    return v;
}
int main(){
    while(scanf("%d%d",&n,&m)==2){
        if(!n)break;
        for(int i=1;i<=(n+m)*2;i++){
            G[i].clear();
            G2[i].clear();
            bcc[i].clear();
            pre[i]=0;
            iscut[i]=0;
            bccno[i]=0;
            fa[i]=0;
            top[i]=0;
            siz[i]=0;
            son[i]=0;
            mp[i]=0;
            dep[i]=0;
            cnt[i]=0;
            vis[i]=0;
            Tcut[i]=0;
        }
        dfs_clock=0;bcc_cnt=0;z=0;

        for(int i=1;i<=m;i++){
            int u,v;scanf("%d%d",&u,&v);    
            add(u,n+i);
            add(n+i,v);
        }
        
        
        
        
        for(int i=1;i<=n+m;i++)
            if(!pre[i]){
                dfs(i,-1);
            }
            
        int cuts=0;
        for(int i=1;i<=n+m;i++)if(iscut[i])
            iscut[i]=++cuts;
           
        //cerr<<cuts<<endl;    
            
        for(int i=1;i<=n+m;i++)if(iscut[i]){
            if(i<=n)Tcut[bcc_cnt+iscut[i]]=1;
            for(int j=0;j<G[i].size();j++){
                int v=G[i][j];
                if(!iscut[v]){
                    if(vis[bccno[v]]==iscut[i])continue;
                    vis[bccno[v]]=iscut[i];
                    G2[bccno[v]].push_back(bcc_cnt+iscut[i]);
                    G2[bcc_cnt+iscut[i]].push_back(bccno[v]);
                }else{
                    G2[bcc_cnt+iscut[i]].push_back(bcc_cnt+iscut[v]);
                }
                //cerr<<bccno[v]<<"---"<<bcc_cnt+cuts<<endl;
            }
        }

        for(int i=1;i<=bcc_cnt+cuts;i++)
            if(!mp[i]){
                dfs2(i);
                build(i,i);
            }
        
        int q;scanf("%d",&q);
        while(q--){
            int x,y;scanf("%d%d",&x,&y);
            x=iscut[x+n]?bcc_cnt+iscut[x+n]:bccno[x+n];
            y=iscut[y+n]?bcc_cnt+iscut[y+n]:bccno[y+n];
            //cerr<<x<<" "<<y<<endl;
            int LCA=lca(x,y);
            int ans=cnt[x]+cnt[y]-2*cnt[LCA]+Tcut[LCA];
            printf("%d\n",ans);
        }
    }
    return 0;
}
