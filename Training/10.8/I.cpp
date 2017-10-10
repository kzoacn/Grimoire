#include<bits/stdc++.h>
using namespace std;
const int inf=1e9;
int dp[1<<21];
int cnt[1<<21][9];
int bag[21][9];
int B,G,S;
int main(){
	while(scanf("%d%d%d",&G,&B,&S)==3){
		if(G+B+S==0)break;
		memset(bag,0,sizeof bag);
		for(int s=0;s<(1<<B);s++){
			memset(cnt[s],0,sizeof cnt[s]);
			dp[s]=-inf;
		}
		
		for(int i=0;i<B;i++){
			int n;scanf("%d",&n);
			for(int j=0;j<n;j++){
				int x;scanf("%d",&x);
				bag[i][x]++;
			}
		}
		for(int s=1;s<(1<<B);s++){
			int pos=0;
			for(int i=0;i<B;i++)if(s>>i&1){
				pos=i;
				break;
			}
			for(int i=1;i<=G;i++){
				cnt[s][i]=(cnt[s^(1<<pos)][i]+bag[pos][i])%S;
			}
		}
		
		dp[0]=0;
		int mask = (1<< B) - 1;
		for(int s=1;s<(1<<B);s++){
		 
		
			for(int i=0;i<B;i++)if(s>>i&1){
				int get=0;
				for(int j=1;j<=G;j++){
					get+=(cnt[mask ^ s][j]+bag[i][j])/S;
				}
				if(get==0){
					dp[s]=max(dp[s],-dp[s^(1<<i)]);
				}else{
					dp[s]=max(dp[s],dp[s^(1<<i)]+get);
				}
			}
			//cerr<<s<<" "<<dp[s]<<endl;
		}
		
		printf("%d\n",dp[(1<<B)-1]);
	}
	return 0;
}
