#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n,m;
multiset<int>S;
struct troop{
	int a,d;
	bool operator<(troop oth){
		return d<oth.d;
	}
}a[maxn],e[maxn];
bool byAtk(troop a,troop b){
	return a.a>b.a;
}
bool byDef(troop a,troop b){
	return a.d>b.d;
}
int solve(){
	scanf("%d%d",&n,&m);
	S.clear();
	for(int i=1;i<=n;i++)
		scanf("%d%d",&a[i].a,&a[i].d);
	for(int i=1;i<=m;i++)
		scanf("%d%d",&e[i].a,&e[i].d);
	sort(e+1,e+1+m,byDef);
	sort(a+1,a+1+n,byAtk);

	int j=1;
	int ans=n;
	for(int i=1;i<=m;i++){
		while(j<=n&&a[j].a>=e[i].d){
			S.insert(a[j].d);
			j++;
		}
		if(S.empty())
			return -1;
		auto it=S.upper_bound(e[i].a);
		if(it==S.end()){
			S.erase(S.begin());
			ans--;
		}else{
			S.erase(it);
		}
	}
	
	
	return ans;
}

int main(){
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case #%d: %d\n",t,solve());
	}
	return 0;
}

