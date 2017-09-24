vector<int>G[maxn];
int Link[maxn],vis[maxn],T;
bool find(int x){
	for(int i=0;i<G[x].size();i++){
		int v=G[x][i];
		if(vis[v]==T)continue;
		vis[v]=T;
		if(!Link[v]||find(Link[v])){
			Link[v]=x;
			return 1; 
		}
	}return 0;
}
int Hungarian(int n){
	int ans=0;
	memset(Link,0,sizeof Link);
	for(int i=1;i<=n;i++){
		T++;
		ans+=find(i);
	}return ans;
}
