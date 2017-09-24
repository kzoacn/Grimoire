#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
unordered_map<int,LL>dp[(1<<8)+3];
int n,q;
int a[9];



LL solve(){
	scanf("%d%d",&n,&q);
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=0;i<(1<<n);i++)dp[i].clear();
	for(int i=0;i<n;i++){
		dp[1<<i][a[i]]++;
	}
	
	
	for(int S=1;S<(1<<n);S++){
		if(__builtin_popcount(S)==1){
			continue;
		}
		for(int SS=(S-1)&S;SS>0;SS=(SS-1)&S){
			for(auto x:dp[SS]){
				for(auto y:dp[S^SS]){
				
					//cerr<<S<<" merge from "<<SS<<" and "<<(S^SS)<<endl;
				
					int a=x.first,b=y.first;
					LL cas=x.second*y.second;
					dp[S][a+b]+=cas;
					if(a-b>=0)
						dp[S][a-b]+=cas;
					dp[S][a*b]+=cas;	
					if(b&&a%b==0)
						dp[S][a/b]+=cas;
				}
			}
		}
	}
	
	/*for(int S=1;S<(1<<n);S++){
		cerr<<"set is "<<S<<endl;
		for(auto x:dp[S])
			cerr<<x.first<<" "<<x.second<<endl;
	}*/
	long long ans=0;
	for(int S=1;(S<(1<<n));S++){
		int x=__builtin_popcount(S);
		ans+=dp[S][q]*x*x;
	}
	return ans;
}

int main(){
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case #%d: %lld\n",t,solve());
	}
	return 0;
}
