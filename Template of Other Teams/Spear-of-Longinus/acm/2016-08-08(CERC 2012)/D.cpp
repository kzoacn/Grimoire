#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
const int maxn=2e5+5;
int T,n,a[maxn];
vector<int>vec[maxn];
int num[maxn],siz;
bool check(int x,int l,int r){
	return upper_bound(vec[x].begin(),vec[x].end(),r)-lower_bound(vec[x].begin(),vec[x].end(),l)<=1;
}
bool solve(){

	stack<pair<int,int> >S;
	S.push(make_pair(1,n));
	
	while(!S.empty()){
		int l=S.top().first;
		int r=S.top().second;
		S.pop();
		if(l>=r)continue;
		int ok=0;
		int curl=l,curr=r;
		for(int i=l;i<=r;i++){
			if(i&1){
				if(check(a[curl],l,r)){
					ok=1;
					S.push(make_pair(l,curl-1));
					S.push(make_pair(curl+1,r));
					break;
				}
				curl++;
			}else{
				if(check(a[curr],l,r)){
					ok=1;
					S.push(make_pair(l,curr-1));
					S.push(make_pair(curr+1,r));
					break;
				}
				curr--;
			}
		}
		if(!ok)
			return false;
	}
	return true;
}
int main(){
	scanf("%d",&T);
	while(T--){
		siz=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			num[++siz]=a[i];
		}
		sort(num+1,num+1+siz);
		siz=unique(num+1,num+1+siz)-num-1;
		for(int i=1;i<=siz;i++)
			vec[i].clear();
		for(int i=1;i<=n;i++){
			a[i]=lower_bound(num+1,num+1+siz,a[i])-num;
			vec[a[i]].push_back(i);
		}
		puts(solve()?"non-boring":"boring");
	}
	return 0;
}
