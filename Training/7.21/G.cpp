#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long LL;
LL dp[111][666];
int n,m;
int a[111][111];
int main(){
	cin>>n>>m;
	
	for(int i=1;i<=m;i++){
		double x,y;scanf("%lf%lf",&x,&y);
		a[(int)ceil(x)][(int)ceil(y)]=1;
	}
	dp[0][7]=1;
	for(int i=1;i<=n;i++){
		for(int S=0;S<(1<<3);S++){
			for(int S2=0;S2<(1<<3);S2++){
				int ok=1;
				for(int j=0;j<3;j++){
					if(!(S2>>j&1)&&!(S>>j&1))
						ok=0;
					
					if(a[i][j+1]&&!(S>>j&1))
						ok=0;
					if(a[i][j+1]&&!(S2>>j&1))
						ok=0;
				}
			
				if(ok){
					//if(i==2&&S==3)
					//	cerr<<"from "<<S2<<" "<<dp[i-1][S2]<<endl;
				
					dp[i][S]+=dp[i-1][S2];
					if((S>>0&1)&&(S>>1&1)&&(S2>>0&1)&&(S2>>1&1)&&!a[i][1]&&!a[i][2])
						dp[i][S]+=dp[i-1][S2];
					if((S>>1&1)&&(S>>2&1)&&(S2>>1&1)&&(S2>>2&1)&&!a[i][2]&&!a[i][3])
						dp[i][S]+=dp[i-1][S2];
				}
			}
		}
	}
	/*for(int i=1;i<=n;i++)
		for(int S=0;S<(1<<3);S++)
			printf("dp[%d][%d]=%lld\n",i,S,dp[i][S]);*/
	cout<<dp[n][7]<<endl;
	return 0;
}
