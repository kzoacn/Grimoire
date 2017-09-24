//#pragma GCC optimal(2)

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
#define fir first
#define sec second
using namespace std;
typedef pair<int,int> Par;
char mp[17][17];
int n,m;
const int dx[4]={0,0,1,-1};
const int dy[4]={1,-1,0,0};
struct edge{
	int u,v,w;
	bool operator<(const edge &oth)const{
		return w<oth.w;
	}
};
vector<edge>G[17];
int dis[17][17];
int d[17][1<<15],vis[17][1<<15];
vector<pair<char,Par> >spe;
void bfs(Par s,int d[17][17]){
	for(int i=0;i<16;i++)
		for(int j=0;j<16;j++)
			d[i][j]=1e9;
	queue<Par>q;d[s.fir][s.sec]=0;
	q.push(s);
	while(!q.empty()){
		Par u=q.front();q.pop();
		for(int i=0;i<4;i++){
			int x=u.first+dx[i];
			int y=u.second+dy[i];
			if(x<1||x>n||y<1||y>m||mp[x][y]=='D'||d[x][y]!=d[0][0])
				continue;
			d[x][y]=d[u.fir][u.sec]+1;
			q.push(make_pair(x,y));
		}
	}
}
bool dijk(int E){
	static queue<Par >q;
	for(int i=0;i<spe.size();i++)
		for(int j=0;j<(1<<(spe.size()-1));j++)
			d[i][j]=-1e9,vis[i][j]=0;
	
	d[0][0]=E;
	q.push(Par(0,0));
	int mask=0;
	for(int i=0;i<spe.size();i++){
		if(spe[i].fir=='Y')
			mask|=1<<(i-1);
	}
	while(!q.empty()){
		int u=q.front().fir;
		int S=q.front().sec;
		vis[u][S]=0;
		if((S&mask)==mask){
			while(!q.empty())
				q.pop();
			return 1;
		}
		
			q.pop();
		
			
			
		for(int i=0;i<G[u].size();i++){
			int v=G[u][i].v,w=G[u][i].w,nS=S;
			
//			if(w<0){
//				cerr<<w<<endl;
//			}
			
			if(d[u][S]-w<0)break;
			
			if(spe[v].fir=='Y'){
				nS=S|(1<<(v-1));
				if(d[v][nS]<d[u][S]-w){
					d[v][nS]=d[u][S]-w;
					if(!vis[v][nS])	{
						q.push(Par(v,nS));
						vis[v][nS]=1;
					}
				}
			}else if(spe[v].fir=='G'){
				nS=S|(1<<(v-1));
				if(S^nS){
					d[v][nS]=E;
					if(!vis[v][nS]){q.push(Par(v,nS));vis[v][nS]=1;}
				}
				
				nS=S;
				if(d[v][nS]<d[u][S]-w){
					d[v][nS]=d[u][S]-w;
					if(!vis[v][nS]){q.push(Par(v,nS));vis[v][nS]=1;}
				}
				
			}else{
				nS=S;
				if(d[v][nS]<d[u][S]-w){
					d[v][nS]=d[u][S]-w;
					if(!vis[v][nS]){q.push(Par(v,nS));vis[v][nS]=1;}
				}
			}
		
		}
	}
	int ans=-1;
	for(int i=0;i<spe.size();i++)
		for(int j=0;j<(1<<(spe.size()-1));j++){
			if((j&mask)==mask){
				ans=max(ans,d[i][j]);
			}
		}
	return ans>=0;
}
int main(){
	while(scanf("%d%d",&n,&m)==2){
		if(!n)
			break;
		
		spe.clear();
		for(int i=0;i<17;i++)
			G[i].clear();
				
		for(int i=1;i<=n;i++)
			scanf("%s",mp[i]+1);
		
		
		
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				if(mp[i][j]=='F'
					||mp[i][j]=='G'
					||mp[i][j]=='Y'){
				
					
					spe.push_back(make_pair(mp[i][j],Par(i,j)));
				
				
					
							
				}	
			}
		}	 
		sort(spe.begin(),spe.end());
		
		int flag=0;
		
		for(int i=0;i<spe.size();i++){
		
			//cerr<<spe[i].fir<<" "<<spe[i].sec.fir<<" "<<spe[i].sec.sec<<endl;
			
			bfs(spe[i].sec,dis);
			for(int j=i+1;j<spe.size();j++){
			
				if(spe[i].fir=='F'&&spe[j].fir=='Y'&&dis[spe[j].sec.fir][spe[j].sec.sec]==int(1e9)){
					flag=1;
				}
			
				G[i].push_back((edge){i,j,dis[spe[j].sec.fir][spe[j].sec.sec]});
				G[j].push_back((edge){j,i,dis[spe[j].sec.fir][spe[j].sec.sec]});
				
				//cerr<<i<<"---"<<j<<" "<<dis[spe[j].sec.fir][spe[j].sec.sec]<<endl;
				
			}			
		}
		
		for(int i=0;i<spe.size();i++)
			sort(G[i].begin(),G[i].end());		
		
		if(flag){
			puts("-1");
			continue;
		}
		
		
		int l=1,r=n*m*2+10;
		while(l<r){
			int mid=(l+r)>>1;
			if(dijk(mid))
				r=mid;
			else 
				l=mid+1;
		}	
		printf("%d\n",l);	
	}
	return 0;
}

/*

3 3 
FYY
DDG
GDS

F 1 1
0---1 3
0---2 1
0---3 2
0---4 3
0---5 1
0---6 2
0---7 3
0---8 4
0---9 5
G 2 3
1---2 2
1---3 1
1---4 2
1---5 4
1---6 3
1---7 2
1---8 1
1---9 2
Y 1 2
2---3 1
2---4 2
2---5 2
2---6 3
2---7 4
2---8 3
2---9 4
Y 1 3
3---4 1
3---5 3
3---6 4
3---7 3
3---8 2
3---9 3
Y 1 4
4---5 4
4---6 5
4---7 4
4---8 3
4---9 4
Y 2 1
5---6 1
5---7 2
5---8 3
5---9 4
Y 3 1
6---7 1
6---8 2
6---9 3
Y 3 2
7---8 1
7---9 2
Y 3 3
8---9 1
Y 3 4
4
*/
