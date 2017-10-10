#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int n,m;
const int maxn=1e4+4;
LL a[maxn],mask,pmx[maxn],pmn[maxn],smx[maxn],smn[maxn];;
char s[100];
int main(){
	int T;cin>>T;
	while(T--){
		scanf("%d%d",&n,&m);
		mask=(1LL<<m)-1;
		for(int i=1;i<=n;i++){
			scanf("%s",s);
			a[i]=0;
			for(int j=0;j<m;j++){
				a[i]=a[i]<<1|(s[j]-'0');
			}
		}
		
		pmn[1]=min(a[1],mask^a[1]);
		pmx[1]=max(a[1],mask^a[1]);
		for(int i=2;i<=n;i++){
			pmn[i]=min(pmn[i-1],a[i]);
			pmn[i]=min(pmn[i-1],mask^a[i]);
			pmx[i]=max(pmx[i-1],a[i]);
			pmx[i]=max(pmx[i-1],mask^a[i]);
		}
		
		smn[n]=min(a[n],mask^a[n]);
		smx[n]=max(a[n],mask^a[n]);
		
		for(int i=n-1;i>=1;i--){
			smn[i]=min(smn[i+1],a[i]);
			smn[i]=min(smn[i+1],mask^a[i]);
			
			smn[i]=min(smn[i+1],a[i]);
			smx[i]=max(smx[i+1],mask^a[i]);
		}
		LL ans=0;
		for(int i=1;i<=n;i++){
			if(i>1){
				ans=max(ans,llabs(pmn[i-1]-a[i]));
				ans=max(ans,llabs(pmx[i-1]-a[i]));
				ans=max(ans,llabs(pmn[i-1]-(a[i]^mask)));
				ans=max(ans,llabs(pmx[i-1]-(a[i]^mask)));
			}
			if(i<n){
				ans=max(ans,llabs(smn[i+1]-a[i]));
				ans=max(ans,llabs(smx[i+1]-a[i]));
				ans=max(ans,llabs(smn[i+1]-(a[i]^mask)));
				ans=max(ans,llabs(smx[i+1]-(a[i]^mask)));
			}
		}
		static int t=0;
		printf("Case #%d: %lld\n",++t,ans);
	}
	return 0;
}
