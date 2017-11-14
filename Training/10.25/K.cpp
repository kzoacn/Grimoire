#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
typedef long long LL;
int n,m;
LL a[maxn],c;
int main(){
	while(scanf("%d%d%d",&n,&m,&c)==3){
		for(int i=1;i<=n;i++)
			scanf("%lld",&a[i]);
		a[0]=0;
		for(int i=1;i<=n;i++){
			a[i]+=a[i-1];
		}
		sort(a,a+1+n);
		int be=0,ed=n;
		long long ans=0;
		for(int i=1;i<=m;i++){
			LL res=a[ed]-a[be]-c;
			if(res>0){
				ans+=res;
				ed--;
				be++;
			}else break;
		}
		cout<<ans<<endl;
	}
	return 0;
}
