#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int a[maxn];
int n,A,B,L;


int solve(){
	scanf("%d%d%d%d",&n,&A,&B,&L);
	for(int i=0;i<L;i++)
		a[i]=0;
	for(int i=1;i<=n;i++){
		int l,r;scanf("%d%d",&l,&r);
		a[l]++;
		a[r]--;
	}
	int cur=0,res=0,ans=0;
	for(int i=0;i<L;i++){
		cur+=a[i];
		if(cur)
			res-=A;
		else
			res+=B;
		ans=min(ans,res);
	}
	return -ans;
}
int main(){
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		
		printf("Case #%d: %d\n",t,solve());
	}
	return 0;
}
