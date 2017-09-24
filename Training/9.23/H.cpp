#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n,m,w;
pair<long long,int>a[maxn],b[maxn];
bitset<maxn>bs,ans;
bitset<1005>bs1,ans1;


long long calc(long long x, long long y) {
	if (!x || !y) {
		return 0;
	}
	if (x == 1) return y;
	if (y == 1) return x;
	return x + y;
}

void solve(){
	scanf("%d%d%d",&n,&m,&w);
	for(int i=0;i<n;i++){
		scanf("%lld",&a[i].first);
		a[i].second=i;
	}
	for(int i=0;i<m;i++){
		scanf("%lld",&b[i].first);
		b[i].second=i;
	}
	sort(a,a+n);
	sort(b,b+m);
	if (n + m <= 1000) {
		ans1.reset();	
		bs1.reset();
		for(int i=0,j=m-1;i<n;i++){
			while(j>=0&&calc(a[i].first,b[j].first)>w){
				bs1[b[j].second]=1;
				j--;
			}
			ans1|=(bs1<<a[i].second);
		}
	
		for(int i=0;i+1<n+m;i++)
			printf("%c",ans1[i]?'Y':'N');
		puts("");
		return;
	}
	
	ans.reset();	
	bs.reset();
	for(int i=0,j=m-1;i<n;i++){
		while(j>=0&&calc(a[i].first,b[j].first)>w){
			bs[b[j].second]=1;
			j--;
		}
		ans|=(bs<<a[i].second);
	}
	
	for(int i=0;i+1<n+m;i++)
		printf("%c",ans[i]?'Y':'N');
	puts("");
}

int main(){
	int T;cin>>T;
	while(T--)
		solve();
	return 0;
}
