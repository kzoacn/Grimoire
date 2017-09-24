#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long LL;
LL sqr(LL x){return x*x;}
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n;scanf("%d",&n);
		int ans=0;
		for(int i=1;i<=n;i++){
			int x,y;scanf("%d%d",&x,&y);
			LL r2=x*x+y*y;
			for(int j=10;j>=1;j--){
				if(r2<=sqr(20*(11-j))){
					ans+=j;
					break;
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
