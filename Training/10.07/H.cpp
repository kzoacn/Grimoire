#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+6;
int n,m;
int a[maxn],c[maxn];
int main(){
	while(scanf("%d",&m)==1){
		multiset<int>S;
		for(int i=1;i<=m;i++){
			scanf("%d",&c[i]);
			S.insert(c[i]);
		}
		n=0;
		while(S.size()){
			a[++n]=*S.begin();
			S.erase(S.begin());
			for(int i=1;i<n;i++)
				S.erase(S.find(a[i]+a[n]));
		}
		printf("%d\n",n);
		for(int i=1;i<=n;i++)
			printf("%d%c",a[i]," \n"[i==n]);
	}
	return 0;
}
