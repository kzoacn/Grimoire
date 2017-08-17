#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n,k;
int a[maxn];
int main(){
	int T;cin>>T;
	while(T--){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		sort(a+1,a+1+n);
		int cnt=1;
		for(int i=n-1;i>=1;i--){
			if(a[i+1]-a[i]>k)
				break;
			cnt++;
		}
		cout<<cnt<<endl;
	}
	return 0;
}
