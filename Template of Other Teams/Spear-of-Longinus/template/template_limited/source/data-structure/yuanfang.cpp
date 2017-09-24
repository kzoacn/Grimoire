void tarjan(int u){
	dfn[u]=low[u]=++tot;
	for(int i=0;i<G[u].size();i++){
		edge e=G[u][i];
		if(dfn[e.v])
			low[u]=min(low[u],dfn[e.v]);
		else{
			S.push(e);
			tarjan(e.v);
			if(low[e.v]==dfn[u]){
				
				if(S.top()==e){
					fa[e.v][0]=u;
					fw[e.v]=e.w;
					S.pop();
					continue;
				}
				
				Rcnt++;
				edge ed;
				do{  
                    ed=S.top();S.pop(); 
                    ring[Rcnt].push_back(ed); 
                }while(ed!=e);  
            	reverse(ring[Rcnt].begin(),ring[Rcnt].end());
                int last=ring[Rcnt].back().v;
            	ring[Rcnt].push_back((edge){last,u,Mw[pack(last,u)]});
			}
			low[u]=min(low[u],low[e.v]);  
		}
	}
}
void up(int u){
	if(dep[u]||u==1)return ;
	if(fa[u][0])up(fa[u][0]);
	dep[u]=dep[fa[u][0]]+1;
	fw[u]+=fw[fa[u][0]];
}
void build(){
	S.push((edge){0,1,0});
	tarjan(1);
	
	for(int i=1;i<=Rcnt;i++){
		rlen[i]=0;
		sum[i].resize(ring[i].size());
		dis[i].resize(ring[i].size());
		for(int j=0;j<ring[i].size();j++){
			rlen[i]+=ring[i][j].w;
			ind[i].push_back(make_pair(ring[i][j].u,j));
		}
		sum[i][0]=0;
		fw[i+n]=0;
		fa[i+n][0]=ring[i][0].u;
		for(int j=1;j<ring[i].size();j++){
			sum[i][j]=sum[i][j-1]+ring[i][j-1].w;
			dis[i][j]=min(sum[i][j],rlen[i]-sum[i][j]);
			fw[ring[i][j].u]=dis[i][j];
			fa[ring[i][j].u][0]=i+n;
		}
		sort(ind[i].begin(),ind[i].end());
	}
	
	for(int i=1;i<=n+Rcnt;i++)
		up(i);
		
	for(int j=1;j<BIT;j++)
	for(int i=1;i<=n+Rcnt;i++)if(fa[i][j-1])
		fa[i][j]=fa[fa[i][j-1]][j-1];
	
}
pair<int,int>second_lca;
int lca(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	int d=dep[u]-dep[v];
	for(int i=0;i<BIT;i++)if(d>>i&1)
		u=fa[u][i];
	if(u==v)return u;
	for(int i=BIT-1;i>=0;i--)if(fa[u][i]!=fa[v][i]){
		u=fa[u][i];
		v=fa[v][i];
	}
	second_lca=make_pair(u,v);
	return fa[u][0];
}
