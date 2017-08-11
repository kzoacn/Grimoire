#include<bits/stdc++.h>
using namespace std;
const int maxn=33;
const int inf=1e9;
int sqr(int x){return x*x;}
int n,m;
int a[maxn][maxn];
int dp[maxn][maxn][1866];


int main(){
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		scanf("%d%d",&n,&m);
		int sum=1802;
		for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
		for(int i=0;i<=n;i++)
			for(int j=0;j<=m;j++)
				for(int w=0;w<=sum;w++)
					dp[i][j][w]=inf;
		
		dp[0][1][0]=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				for(int w=a[i][j];w<=sum;w++){
				
					dp[i][j][w]=min(dp[i][j][w],dp[i-1][j][w-a[i][j]]+sqr(a[i][j]));
					dp[i][j][w]=min(dp[i][j][w],dp[i][j-1][w-a[i][j]]+sqr(a[i][j]));
//					fprintf(stderr,"dp[%d][%d][%d]=%d\n",i,j,w,dp[i][j][w]);
				}
			}
		}
		int ans=inf;
		for(int i=0;i<=sum;i++)if(dp[n][m][i]!=inf){
			ans=min(ans,(n+m-1)*dp[n][m][i]-i*i);
		}
		printf("Case #%d: %d\n",t,ans);
	}
	return 0;
}
