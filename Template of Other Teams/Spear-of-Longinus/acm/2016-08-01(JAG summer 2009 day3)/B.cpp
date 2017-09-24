#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=110;
const int inf=1e9;
int T;
int t[maxn];
int n;
pair<int,int>view[maxn];
int f[maxn][maxn];
int M[maxn];
int main(){
	while(scanf("%d",&T)==1){
		if(!T)break;
		for(int i=1;i<=T;i++)
			scanf("%d",&t[i]);
		scanf("%d",&n);
		int D=0;
		for(int i=1;i<=100;i++)
			M[i]=24;
		for(int i=1;i<=n;i++){
			int x,y;scanf("%d%d",&x,&y);
			M[x]=min(M[x],y);
			D=max(D,x);
		}
		
		
		
		for(int i=0;i<=D;i++)
			for(int j=0;j<=T;j++)
				f[i][j]=inf;
		
		
		f[1][1]=0;
		for(int i=2;i<=D;i++){
			for(int j=1;j<=T;j++){
				f[i][j]=inf;
				if(t[j]<=M[i])
					f[i][j]=min(f[i][j],f[i-1][j-1>0?j-1:T]);
				if(j==1){
					for(int k=1;k<=T;k++)if(f[i-1][k]!=inf)
						f[i][j]=min(f[i][j],f[i-1][k]+1);
				}
			}
		}		
		int ans=*min_element(f[D]+1,f[D]+T+1);
		printf("%d\n",ans);
	}
	return 0;
}
