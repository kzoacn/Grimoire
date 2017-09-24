#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int main(){
	LL n;
	while(cin>>n){
		static int t=0;
		LL ans=0;
		for(LL i=1;i*i*i<=n;i++)
		for(LL j=i;i*j*j<=n;j++){
			// k>=j && ijk <= n
			if(i!=j){
				LL km=n/(i*j);
				if(km>=j){
					ans+=3;
					ans+=(km-j)*6;
				}
			}else{
				LL km=n/(i*j);
				if(km>=j){
					ans++;
					ans+=(km-j)*3;
				}
			}
		}
		
		
		printf("Case %d: %I64d\n",++t,ans);	
	}	
	return 0;
}
