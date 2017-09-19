#include<bits/stdc++.h>
using namespace std;
const int maxn=1010;
int n,k;
int a[maxn],b[maxn];

int main(){
	int T;cin>>T;
	while(T--){
		scanf("%d%d",&n,&k);
		int sum1=0,sum2=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		for(int i=1;i<=n;i++){
			char s[3];
			scanf("%s",s);
			
			if(s[0]=='L'){
				sum1+=a[i];
			}
			if(s[0]=='D'){
				sum2-=a[i];
			}
			if(s[0]=='N'){
				sum1+=a[i];
				sum2-=a[i];
			}
		}
		if(sum2<=k&&k<=sum1)
			puts("yes");
		else
			puts("no");
	}
	return 0;
}
