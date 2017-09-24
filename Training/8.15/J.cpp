#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL n,m,A,B,C;

LL solve1(LL x,LL y){
	LL ans=0;
	ans+=y*max(max(A,B),C);
	if(x%2==1){
		ans+=max((x-1)*(A+C)/2,(x-1)*B);
	}else{
		ans+=max((x-2)*(A+C)/2,(x-2)*B);
		ans+=max(B,min(A,C));
	}
	return ans;
}
LL solve2(LL x,LL y){
	LL ans=0;
	ans+=x*min(min(A,B),C);
	if(y%2==1){
		ans+=min((y-1)*(A+C)/2,(y-1)*B);
	}else{
		ans+=min((y-2)*(A+C)/2,(y-2)*B);
		ans+=min(B,max(A,C));
	}
	return ans;
}

int main(){
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		cin>>n>>m;
		cin>>A>>B>>C;
		printf("Case #%d: %lld %lld\n",t,solve1(m+1,n-m-1),solve2(m-1,n-m+1));
	}
	return 0;
}
