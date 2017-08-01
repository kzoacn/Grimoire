#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
const int BIT=20;
int fa[maxn][BIT];
int dep[maxn];

int dis(int u,int v){
	if(dep[u]<dep[v])swap(u,v);
	int d=dep[u]-dep[v];
	for(int i=0;i<BIT;i++)if(d>>i&1){
		u=fa[u][i];
	}
	int ans=d;
	if(u==v)return ans;
	for(int i=BIT-1;i>=0;i--){
		if(fa[u][i]!=fa[v][i]){
			u=fa[u][i];
			v=fa[v][i];
			ans+=2*(1<<i);
		}
	}
	return ans+2;
}
int n;
int a[maxn];
int main(){
	while(scanf("%d",&n)==1){
		if(!n)break;
		for(int i=1;i<=n;i++){
			memset(fa[i],0,sizeof fa[i]);
			dep[i]=0;
		}
		int s=1,t=1;
		int rt=1;
		long long ans=0;
		for(int i=2;i<=n;i++){
			int x,y;scanf("%d%d",&x,&y);
			if(y)rt=i;
			fa[i][0]=x;
			dep[i]=dep[x]+1;	
			for(int j=1;j<BIT;j++)
				fa[i][j]=fa[fa[i][j-1]][j-1];
			int len1=dis(s,t),len2=dis(s,i),len3=dis(i,t);
			
			if(len1>=len2&&len1>=len3){
				//
			}else
			if(len2>=len1&&len2>=len3){
				t=i;
			}else
			if(len3>=len1&&len3>=len2){
				s=i;
			}
			ans+=max(dis(rt,s),dis(rt,t));
		}
		printf("%lld\n",ans);
	}
	return 0;
}
