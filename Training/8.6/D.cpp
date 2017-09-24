#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

LL dp[2][3][4010];
int n,L;
int a[2222],v[2222];
LL solve(){
	scanf("%d%d",&n,&L);
	LL ans=0;
	L*=2;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i],&v[i]);
		a[i]*=2;
		ans=max(ans,1ll*v[i]);
	}
	memset(dp,0,sizeof dp);
	int cur=0;
	register int i,j,k;
	for(i=1;i<=n;i++){
		for(k=0;k<=2;k++){
			//memset(dp[cur],0,sizeof dp[cur]);
			for(j=0;j<=L;j++)
				dp[cur][k][j]=dp[cur^1][k][j];
			for(j=a[i]/2;j<=L;j++){
				if(j>=a[i])
					dp[cur][k][j]=max(dp[cur][k][j],dp[cur^1][k][j-a[i]]+v[i]);
				if(k)
					dp[cur][k][j]=max(dp[cur][k][j],dp[cur^1][k-1][j-a[i]/2]+v[i]);
			}
//			for(int j=0;j<=L;j++)
//				printf("dp[%d][%d][%d]=%lld\n",i,k,j,dp[cur][k][j]);
		}
		cur^=1;
	}
	cur^=1;
	for(k=0;k<=2;k++)
		ans=max(ans,dp[cur][k][L]);
	return ans;
}

int main(){
	int T;
	cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case #%d: %lld\n",t,solve());
	}
	return 0;
}
