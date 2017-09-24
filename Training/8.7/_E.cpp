#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int n=4;
LL d[4],nd[4];


const int maxn=2000000;
LL calc(LL k,vector<LL>num){
	if(k<=0)return 0;
	static bool dp[maxn];
	memset(dp,0,sizeof dp);
	dp[0]=1;
	for(auto x:num)
		for(int i=x;i<maxn;i++)
			dp[i]|=dp[i-x];
	
	LL ans=2e18;
	LL N = maxn - 5;
	for(auto x:num){
		for(LL y=k;y<=k+30000;y++){
		//cout << y << " " << N << " " << y - (y - N + x - 1) / x * x << endl;
			if (y <= N) {
				if (dp[y]) {
					ans = min(ans, y);
				}
			} else {
				if (dp[y - (y - N + x - 1) / x * x]) {
						ans = min(ans, y);
				}
			}
		}
	}
	return ans;
}

void solve(){
	LL k;
	cin>>k;
	for(int i=0;i<n;i++){
		cin>>d[i];
		nd[(i-1+n)%n]=d[i];
	}
	LL sum=0;
	for(int i=0;i<n;i++){
		d[i]=nd[i];
		sum+=d[i];
	}
	LL ans=2e18;
	
	vector<LL>vec;
	
	vec.clear();
	for(int i=0;i<4;i++)vec.push_back(d[i]*2);
	ans=min(ans,calc(k-sum,vec)+sum);
	
	//return;
	ans=min(ans,calc(k-sum*2,vec)+sum*2);
			
	for(int i=0;i<4;i++){
		for(int j=i;j<4;j++){
			if(i==0&&j==3)continue;
			vec.clear();
			LL sum=0;
			for(int k=0;k<4;k++){
				if(i<=k&&k<=j)continue;
				vec.push_back(d[k]*2);
				sum+=d[k];
			}
			ans=min(ans,calc(k-sum*2,vec)+sum*2);
		}
	}
	
	cout<<ans<<endl;
}

int main(){
	int T;cin>>T;
	while(T--)
		solve();
	return 0;
}
