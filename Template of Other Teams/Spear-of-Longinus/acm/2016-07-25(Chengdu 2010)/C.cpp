#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=111;
int a[maxn],b[maxn];
int count(int x){
	int ans=0;
	while(x)ans++,x-=x&-x;
	return ans;
}
int main(){
	int T;scanf("%d",&T);
	while(T--){
		int n,m;scanf("%d%d",&m,&n);
		for(int i=1;i<=m;i++)
			scanf("%d",&a[i]);
		for(int i=1;i<=n;i++)
			scanf("%d",&b[i]);
		for(int i=1;i<=n;i++){
			pair<int,int>ans=make_pair(int(2e9),int(2e9));
			for(int j=1;j<=m;j++){
				int cot=count(b[i]^a[j]);
				ans=min(ans,make_pair(cot,a[j]));	
			}printf("%d\n",ans.second);
		}
	}
	return 0;
}
