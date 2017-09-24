#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=1e6+4;
LL cub[maxn];

LL c(LL x){return x*x*x;}

int main(){
	for(int i=1;i<maxn;i++){
		cub[i]=c(i)-c(i-1);
	}
	
	
	int T;
	cin>>T;
	while(T--){
		LL p;
		cin>>p;
		bool ok=0;
		ok=binary_search(cub+1,cub+maxn,p);
		puts(ok?"YES":"NO");
	}
	return 0;
}
