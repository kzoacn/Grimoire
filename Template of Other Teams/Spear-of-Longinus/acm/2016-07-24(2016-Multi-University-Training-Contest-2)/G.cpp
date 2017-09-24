#include<bits/stdc++.h>

#define output(x) cerr<< #x << " is " << x <<endl;

#define NDEBUG

using namespace std;
const int maxn=510;
const int inf=1e9;
int n,m;
int mp[maxn][maxn];
char s[maxn];
int vis[maxn],ncol[maxn],col[maxn];
int block[maxn];
int cnt,cnt0,cnt1,cot0,cot1;
int label[maxn];
int rlabelX[maxn],rlabelY[maxn];
// is inf too big ?
int t;
bool dfs(int u,int c){
    block[++cnt]=u;
    vis[u]=1;
    ncol[u]=c;
    if(c==0)
        cot0++;
    else 
        cot1++;
        
    if(col[u]==0)
        cnt0++;
    else 
        cnt1++;
        
    for(int v=1;v<=n;v++){
        if(mp[u][v]==1){
            if(!vis[v]){
                if(!dfs(v,c^1))
                    return false;            
            }else{
                if(ncol[v]==ncol[u])    
                    return false;
            }
        }
    }
    return true;
}
//vector<int>SP[maxn][maxn];
int pre[maxn][maxn];
int w[maxn][maxn];
vector<int>G[maxn];
void bfs(int s){
    static int vis[maxn];
    for(int i=1;i<=n;i++)
        vis[i]=0;
    queue<int>q;
    q.push(s);
    vis[s]=1;
    for(int i=1;i<=n;i++)w[s][i]=inf;
    w[s][s]=0;
//    SP[s][s].clear();SP[s][s].push_back(s);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=0;i<G[u].size();i++){
            int v=G[u][i];
            if(mp[u][v]==1){
                if(!vis[v]){
                    vis[v]=1;
                    q.push(v);
                    //SP[s][v]=SP[s][u];
                    pre[s][v]=u;
                    w[s][v]=w[s][u]+1;
                }
            }
        }
    }
}
vector<pair<int,int> >Swap(int x,int y){

    //cerr<< x << " " << y << endl;

    int u=y,i=0;
    vector<int>vec;
    
    while(u!=x){
        vec.push_back(u);
        u=pre[x][u];
    }vec.push_back(x);
    
    reverse(vec.begin(),vec.end());

#ifndef NDEBUG    
    for(int i=0;i<vec.size();i++)
        printf("%d%c",vec[i]," \n"[i+1==vec.size()]);
#endif    
    u=x;
    vector<pair<int,int> >tmp,ans;
    int c=col[x];
    while(1){
    //    cerr<<i<<endl;
    //    cerr<<vec[i]<<endl;
        tmp.clear();
        while(col[vec[i]]==c){
            tmp.push_back(make_pair(vec[i],vec[i+1]));
            i++;
        }
        reverse(tmp.begin(),tmp.end());
        for(int j=0;j<tmp.size();j++){
            ans.push_back(tmp[j]);    
            swap(col[tmp[j].first],col[tmp[j].second]);
        }
        if(i+1==vec.size())
            break;
    }
    return ans;
}
namespace KM{
    int n,lx[maxn],ly[maxn],vx[maxn],vy[maxn],slack[maxn];
    int match[maxn];
    int mat[maxn][maxn];
    bool find(int x){
        //cerr << x << endl;
        vx[x]=1;
        for(int i=1;i<=n;i++){
            if(vy[i])
                continue;
            int tmp=lx[x]+ly[i]-mat[x][i];
            if(tmp==0){
                vy[i]=1;
                if(match[i]==-1 || find(match[i])){
                    match[i]=x;
                    return 1;
                }
            }else
                slack[i]=min(slack[i],tmp);
                
        }
        return 0;
    }
    bool KM(int n){
        KM::n=n;
        for(int i=1;i<=n;i++){
            lx[i]=-inf;
            ly[i]=0;
            match[i]=-1;
            for(int j=1;j<=n;j++)
                lx[i]=max(lx[i],mat[i][j]);
        }
        
        
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++)
                slack[j]=inf;
            while(1){
                for(int j=1;j<=n;j++)
                    vx[j]=vy[j]=0;
                if(find(i))
                    break; 
                int delta=inf;
                for(int j=1;j<=n;j++)
                    if(!vy[j])
                        delta=min(delta,slack[j]);
                for(int j=1;j<=n;j++){
                    if(vx[j])
                        lx[j]-=delta;
                    if(vy[j])
                        ly[j]+=delta;
                    else 
                        slack[j]-=delta;
                }    
                
            }
        }
        
        for(int i=1;i<=n;i++)
            vx[i]=0;
        int ok=1;
        for(int i=1;i<=n;i++)
            if(match[i]==-1 || mat[match[i]][i]<0){
                ok=0;
            }else{
                if(vx[match[i]])
                    ok=0;
                vx[match[i]]=1;
            }
            
        return ok;    
    }
}
using KM::match;
int flag;
int X=0,Y=0;    
bool Match(int n){
    if(cnt0!=cot0 || cnt1!=cot1)
        return false;
    X=0;Y=0;             
    for(int i=1;i<=n;i++)
        if(col[block[i]]!=ncol[block[i]]){
            if(ncol[block[i]]==0){
                label[i]=++X;
                rlabelX[X]=i;
            }
            else{ 
                label[i]=++Y;
                rlabelY[Y]=i;
            }
        }
    
    for(int i=1;i<=X;i++)
        for(int j=1;j<=Y;j++)
            KM::mat[i][j]=-inf;
    
    
    for(int i=1;i<=n;i++)
        if(col[block[i]]!=ncol[block[i]]&&ncol[block[i]]==0)
            for(int j=1;j<=n;j++)
                if(col[block[j]]!=ncol[block[j]]&&ncol[block[j]]==1){
                    KM::mat[label[i]][label[j]]=inf - mp[block[i]][block[j]];
                    //cerr<< label[i] << "->" << label[j] <<" w= "<< mp[block[i]][block[j]] <<endl;            
                }
    
    
    
    assert(X==Y);
    
    if(!KM::KM(X|Y))
        return false;
        
        //cerr<<"KM ok"<<endl;
    return true;
}
int ComputeAns(vector<pair<int,int> >res){
    int ans=0;
    for(int i=0;i<res.size();i++)
        ans+=mp[res[i].first][res[i].second];
    return ans;
}
void solve(){
    scanf("%d%d",&n,&m);
    scanf("%s",s+1);
    for(int i=1;i<=n;i++)
        col[i]=s[i]-'0';
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(i!=j)
                mp[i][j]=inf;
    for(int i=1;i<=n;i++)
        vis[i]=0,G[i].clear();
    while(m--){
        int u,v;scanf("%d%d",&u,&v);
        mp[u][v]=mp[v][u]=1;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    //for(int k=1;k<=n;k++)
    
    
    for(int i=1;i<=n;i++)
        bfs(i);
    //cerr<<clock()/double(CLOCKS_PER_SEC)<<endl;
     
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                mp[i][j]=w[i][j];
    
    
    flag=1;
    vector<pair<int,int> >ans;
    
    
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            int answer=2e9;
        
            //cerr<< "blocks!" <<endl; 
            
            int found=0;
            
            vector<pair<int,int> >res,tmp;
            
            cnt=cnt0=cnt1=cot0=cot1=0;
            if(!dfs(i,0)){
                flag=0;
                break;
            } 
            
            
/*#ifndef NDEBUG
            output(cnt);
            for(int j=1;j<=cnt;j++)
                printf("%d%c",block[j]," \n"[j==cnt]);

#endif    */        
            
            //cerr<<"ok"<<endl;
            
            if(Match(cnt)){
                tmp.clear();
                for(int j=1;j<=Y;j++)
                    tmp.push_back(make_pair(block[rlabelX[match[j]]],block[rlabelY[j]]));
                if(answer>ComputeAns(tmp)){
                    answer=ComputeAns(tmp);
                    res=tmp;
                }
                found=1;
                //break;
            }
            
            //cerr<<"ok"<<endl;
            
            swap(cot0,cot1);
            for(int j=1;j<=cnt;j++)
                ncol[block[j]]^=1;
            //cerr<<"ok"<<endl;
            
            if(Match(cnt)){
                tmp.clear();
                for(int j=1;j<=Y;j++)
                    tmp.push_back(make_pair(block[rlabelX[match[j]]],block[rlabelY[j]]));
                if(answer>ComputeAns(tmp)){
                    answer=ComputeAns(tmp);
                    res=tmp;
                }
                found=1;
                //break;
            }
            
            if(!found){
                flag=0;
                break;
            }
            for(int j=0;j<res.size();j++)
                ans.push_back(res[j]);
        }
    }
    
    if(!flag){
        puts("-1");
        return;
    }
    
    
    vector<pair<int,int> >Ans;
    for(int i=0;i<ans.size();i++){
        vector<pair<int,int> >tmp=Swap(ans[i].first,ans[i].second);
        for(int j=0;j<tmp.size();j++)
            Ans.push_back(tmp[j]);
    }
    
//    test();
    printf("%d\n",(int)Ans.size());
    for(int i=0;i<Ans.size();i++)
        printf("%d %d\n",Ans[i].first,Ans[i].second);
}
int main(){
    
    int T;scanf("%d",&T);    
    
    
    // test 105 got RE
    for(t=1;t<=T;t++){
    
        solve();
        
        
    }
    return 0;
}
