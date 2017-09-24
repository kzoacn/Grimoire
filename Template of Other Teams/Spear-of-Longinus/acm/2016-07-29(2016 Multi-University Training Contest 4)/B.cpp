#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
vector<int>G[maxn];
int n,rt;
int a[maxn],fa[maxn];
int b[maxn],chain[maxn];
int flag=0,mp[maxn];
void dfs(int u){
	if(fa[u]&&a[u]==a[fa[u]])
		chain[fa[u]]++;
	if(fa[u]&&a[u]>a[fa[u]])
		flag=1;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if(fa[u]==v)continue;
		fa[v]=u;
		dfs(v);
	}
}
int main(){


	int T;scanf("%d",&T);
	
	for(int t=1;t<=T;t++){
		scanf("%d",&n);
		rt=0;
		
		for(int i=1;i<=n;i++){
			G[i].clear();
			chain[i]=0;
			b[i]=0;
			fa[i]=0;
			mp[i]=0;
		}
		for(int i=1;i<=n;i++)scanf("%d",&a[i]);
		for(int i=1;i<n;i++){
			int u,v;scanf("%d%d",&u,&v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		
	
		for(int i=1;i<=n;i++){
			if(a[i]==n){
				int cnt=0;
				for(int j=0;j<G[i].size();j++)
					cnt+=a[G[i][j]]==n;
				if(cnt==1 or cnt==0){
					rt=i;
					break;
				}
			}
		}
		if(!rt){
			printf("Case #%d: Impossible\n",t);
			continue;
		}
		flag=0;
		dfs(rt);
		if(flag==1 || *max_element(chain+1,chain+1+n)>1){
			printf("Case #%d: Impossible\n",t);
			continue;
		}
		
		
		for(int i=1;i<=n;i++)if(!chain[i]){
			b[i]=a[i];
			mp[a[i]]=i;
		}
		
		
		for(int i=1;i<=n;i++){
//			printf("%d%c",chain[i]," \n"[i==n]);
//			printf("%d%c",mp[i]," \n"[i==n]);
		}		
		
		priority_queue<int>q;
		flag=0;
		for(int i=n;i>=1;i--){
			//cerr<< i <<endl;
			if(!mp[i]){
				if(q.empty()){
					flag=1;break;
				}
				int x=q.top();q.pop();
				//cerr<< x <<endl;
				mp[i]=x;
				b[x]=i;
			}else{
				int u=mp[i];
				while(a[fa[u]]==a[mp[i]]){
					q.push(fa[u]);
					u=fa[u];
				}
			}
		}
		if(flag){
			printf("Case #%d: Impossible\n",t);
			continue;			
		}
		printf("Case #%d: ",t);
		for(int i=1;i<=n;i++)
			printf("%d%c",b[i]," \n"[i==n]);
	}
	return 0;
}
