#include<bits/stdc++.h>
using namespace std;
const int maxn=2020;
const int mo=1e9+7;
typedef long long LL;
LL C[maxn][maxn];
LL pw[maxn];
LL S[maxn],dp[maxn];
LL pwer(LL x,LL k,LL mo){
	LL ans=1;
	for(;k;k>>=1){
		if(k&1)ans=ans*x%mo;
		x=x*x%mo;
	}
	return ans;
}

int main(){
	C[0][0]=1;
	for(int i=1;i<maxn;i++){
		C[i][0]=1;
		for(int j=1;j<maxn;j++){
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mo;
		}
	}
	
	int T;cin>>T;
	while(T--){
		int n,m;
		cin>>n>>m;
		LL ans=0;
		
		for(int i=1;i<maxn;i++)
			pw[i]=pwer(i,n,mo);
		
		
		for(int i=1;i<=n;i++){
			dp[i]=0;
			int sgn=1;
			for(int j=0;j<=i;j++){
				dp[i]+=sgn*C[i][j]*pw[i-j]%mo;
				dp[i]=(dp[i]+mo)%mo;
				sgn=-sgn;
			}
		}
		
		for(int k=2;k<=m&&k<=2*n;k++){
			S[k]=0;
			for(int i=1;i<k;i++){
				if(i<=n&&k-i<=n)
					S[k]+=1ll*C[k][i]*dp[i]%mo*dp[k-i]%mo;
				S[k]%=mo;
			}
//			cerr<<k<<" "<<S[k]<<endl;
			ans+=S[k]*C[m][k]%mo;
			ans%=mo;
		}
		cout<<ans<<endl;
	}
	
	return 0;
}
