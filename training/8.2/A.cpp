#include<bits/stdc++.h>
using namespace std;
const int maxn=10010;
int a[maxn];
set<pair<int,int> >S;
int n;

int main(){
	freopen("A.in", "r", stdin);
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
		S.insert({a[i],i});
	}
	
	if(n==1){
		puts("0");
		return 0;
	}
	if(n==2){
		if(a[0]>=0&&a[1]>=0)
			puts("0");
		else
			puts("1");
		return 0;
	}
	
	int ans=0;
	while(1){
		int ps=S.begin()->second;
		if(a[ps]>=0)break;
		ans++;
		int pre=(ps-1+n)%n;
		int nxt=(ps+1)%n;
		S.erase(S.begin());
		S.erase(S.find({a[pre],pre}));
		S.erase(S.find({a[nxt],nxt}));
		a[pre]+=a[ps];
		a[nxt]+=a[ps];
		a[ps]*=-1;
		S.insert({a[ps],ps});
		S.insert({a[pre],pre});
		S.insert({a[nxt],nxt});
	}
	cout<<ans<<endl;
	return 0;
}
