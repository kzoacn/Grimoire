#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int L,n,k;
int a[maxn];
long long f[maxn],g[maxn];

int main(){
	int T;cin>>T;
	while(T--){
		scanf("%d%d%d",&L,&n,&k);
		
		//L++;
		int sz=0;
		for(int i=1;i<=n;i++){
			int x,c;
			scanf("%d%d",&x,&c);
			while(c--)
				a[++sz]=x;
			
		}
		sort(a+1,a+1+sz);
		
		
		f[0]=0;
		for(int i=1;i<=sz;i++){
			f[i]=f[max(i-k,0)]+min(L, a[i]*2);
		}
		g[sz+1]=0;
		for(int i=sz;i>=1;i--){
			g[i]=g[min(i+k,sz+1)]+min(L, (L-a[i])*2);
		}
		
		
		/*cerr<<sz<<endl;
		for(int i=1;i<=sz;i++)
			cerr<<a[i]<<" ";
		cerr<<endl;
		for(int i=1;i<=sz;i++)
			cerr<<f[i]<<" ";
		cerr<<endl;
		for(int i=1;i<=sz;i++)
			cerr<<g[i]<<" ";
		cerr<<endl;
		*/
		
		long long ans=1LL<<61;
		for(int i=0;i<=sz;i++){
			ans=min(ans,f[i]+g[i+1]);
		}
		printf("%lld\n",ans);
	}

	return 0;
}
