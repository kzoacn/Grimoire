#include<bits/stdc++.h>
using namespace std;

const long long inf=(long long)1e17;
long long d[1111],n,p[1111],E;
void dijk(long long m){
	for(long long i=0;i<m;i++){
		d[i]=inf;
	}
	priority_queue<pair<long long,long long>,vector< pair<long long,long long> >,greater<pair<long long,long long> > >q;
	q.push({d[0]=0,0});
	while(!q.empty()){
		if(d[q.top().second]!=q.top().first){
			q.pop();
			continue;
		}
		long long u=q.top().second;q.pop();
		for(long long i=1;i<=n;i++){
			long long v=(u+p[i])%m;	
			if(d[v]>d[u]+p[i]){
				d[v]=d[u]+p[i];
				q.push({d[v],v});
			}
		}
	}
}

int main(){
	long long T;cin>>T;
	for(long long t=1;t<=T;t++){
		scanf("%lld%lld",&n,&E);
		for(long long i=1;i<=n;i++)
			scanf("%lld",&p[i]);
		sort(p+1,p+1+n);
		n=unique(p+1,p+1+n)-p-1;
		dijk(p[1]);
		
		
		long long ans=inf;
		for(long long i=0;i<p[1];i++){
			if(d[i]>=E){
				ans=min(ans,d[i]-E);
			}else{
				long long k=(E-d[i]+p[1]-1)/p[1];
				ans=min(ans,d[i]+k*p[1]-E);
			}
		}
		
		printf("Case #%lld: %lld\n",t,ans);
	}
	return 0;
}
