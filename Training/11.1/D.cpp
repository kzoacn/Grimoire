#include<bits/stdc++.h>
using namespace std;
int n,m,x,y;
pair<int,int>a[111],b[111];
int main(){
	int T;cin>>T;
	while(scanf("%d%d%d%d",&n,&m,&x,&y)==4){
		for(int i=1;i<=x;i++)
			scanf("%d%d",&a[i].first,&a[i].second);
		for(int i=1;i<=y;i++)
			scanf("%d%d",&b[i].first,&b[i].second);
		long long ans=0;
		
		for(int i=1;i<=x;i++){
			for(int j=1;j<=y;j++){
				long long l=max(a[i].first,b[j].first);
				long long r=min(a[i].second,b[j].second);
				
				ans+=max(r-l+1-m+1,0LL);
			}
		}
		
		printf("%lld\n",ans);
	}
	return 0;
}
