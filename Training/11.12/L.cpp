#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

struct array{
	int vis[int(1e6+8)];
	LL a[int(1e6+8)];
	int T;
	void clear(){
		T++;
	}
	LL& operator[](int x){
		
		if(vis[x]!=T){
			vis[x]=T;
			a[x]=0;
		}
		return a[x];
	}
}d;

void add(int x,LL y){

	x++;

	while(x<int(1e6+6)){
		d[x]=max(d[x],y);
		x+=x&-x;
	}
}
LL get(int x){

	x++;

	LL ans=0;
	while(x){
		ans=max(ans,d[x]);
		x-=x&-x;
	}
	return ans;
}
int n;

struct task{
	int l,r,h;
	bool operator<(task t){
		return r<t.r;
	}
}a[int(1e5+5)];

int main(){
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		scanf("%*d%d",&n);
		d.clear();
		
		for(int i=1;i<=n;i++){
			scanf("%*d%d%d%d",&a[i].l,&a[i].r,&a[i].h);
		}
		sort(a+1,a+1+n);
		
		d.clear();
		static LL dp[int(1e5+5)];
		LL ans=0;
		for(int i=1;i<=n;i++){
			dp[i]=get(a[i].l)+a[i].h;
			add(a[i].r,dp[i]);
			ans=max(ans,dp[i]);
		}
		
		printf("Case #%d: %lld\n",t,ans);
	}
	return 0;
}
