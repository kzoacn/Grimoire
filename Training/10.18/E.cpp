#include<bits/stdc++.h>
using namespace std;
const int maxn=2e4+4;


int win[maxn][2],b[maxn],n;
int stamp,comps,top;
int dfn[maxn],low[maxn],comp[maxn],sta[maxn];
vector<int>edge[maxn];
void add(int x,int a,int y,int b){

//	cerr<<x<<" "<<a<<" -> "<<y<<" "<<b<<endl;
	x--;y--;

	edge[x<<1|a].push_back(y<<1|b);
}


void tarjan(int x){
	dfn[x]=low[x]=++stamp;
	sta[top++]=x;
	for(int i=0;i<edge[x].size();i++){
		int y=edge[x][i];
		if(!dfn[y]){
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}else if(!comp[y]){
			low[x]=min(low[x],dfn[y]);
		}
	}
	if(low[x]==dfn[x]){
		comps++;
		do{
			int y=sta[--top];
			comp[y]=comps;
		}while(sta[top]!=x);
	}
}

bool solveTarjan(){
	int counter=n+n+1;
	stamp=top=comps=0;
	fill(dfn,dfn+counter,0);
	fill(comp,comp+counter,0);
	for(int i=0;i<counter;i++){
		if(!dfn[i]){
			tarjan(i);
		}
	}
	for(int i=0;i<n;i++){
		if(comp[i<<1]==comp[i<<1|1])
			return false;
	}
	return true;
}

bool solve(){
	int m;
	scanf("%d",&n);
	scanf("%d",&m);
	for(int i=0;i<=n*2+1;i++){
		edge[i].clear();
		
	}
	
	for(int i=1;i<=n;i++){
		scanf("%d",&b[i]);
		int sz=0;
		for(int j=1;j<=3;j++)
			if(j!=b[i])
				win[i][sz++]=j;
	}
	bool ok=true;
	for(int t=0;t<m;t++){
		int a,b,k;
		scanf("%d%d%d",&a,&b,&k);
		if(a==b){
			if(k==1)ok=false;
			continue;
		}
		
		if(k==0){
		
			for(int i=0;i<2;i++){
				int x= i==0 ? a:b;
				int y=a+b-x;
				for(int j=0;j<2;j++){
					int same=-1;
					for(int k=0;k<2;k++){
						if(win[x][j]==win[y][k]){
							same=k;
							break;
						}
					}
					if(same==-1){
						add(x,j,x,j^1);
					}else{
						add(x,j,y,same);
					}
				}
			}
		
		}else{
		
		
			for(int i=0;i<2;i++){
				int x= i==0 ? a:b;
				int y=a+b-x;
				for(int j=0;j<2;j++){
					int same=-1;
					for(int k=0;k<2;k++){
						if(win[x][j]==win[y][k]){
							same=k;
							break;
						}
					}
					if(same==-1){
						
					}else{
						add(x,j,y,same^1);
					}
				}
			}
		
		}
		
	}
	
	ok&=solveTarjan();
	
	return ok;
}

int main(){
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case #%d: %s\n",t,solve()?"yes":"no");
	}
	return 0;
}
