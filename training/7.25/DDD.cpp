#include<bits/stdc++.h>
#define deb(x) cerr<< #x <<" = "<< x <<endl
using namespace std;
const int maxn=5e5+5;
typedef unsigned long long UL;
UL base=233;
UL h_l[maxn],h[maxn];
UL get(int l,int r){
	return h[r]-h[l-1]*h_l[r-l+1];
}
char s[maxn];
int n;
int lcp(int x,int y){
	int l=1,r=n+1;
	while(l<r){
		int mid=(l+r)>>1;
		if(get(x,x+mid-1)==get(y,y+mid-1))
			l=mid+1;
		else r=mid;
	}
	return l-1;
}
vector<pair<int,int> >Q[maxn];
vector<int>D[maxn];
int ans[maxn];
int main(){
	h_l[0]=1;
	for(int i=1;i<maxn;i++)h_l[i]=h_l[i-1]*base;
	scanf("%s",s+1);
	n=strlen(s+1);s[n+1]=256;
	for(int i=1;i<=n+1;i++)
		h[i]=h[i-1]*base+s[i];

	set<int>S;
	int m;scanf("%d",&m);
	for(int i=1;i<=m;i++){
		int x,y;scanf("%d%d",&x,&y);
		Q[y].push_back({x,i});
	}
	deque<int>dq;
	for(int i=1;i<=n;i++){
		while(dq.size()){
			int LCP=lcp(dq.back(),i);/*
			deb(dq.back());
			deb(i);
			deb(LCP);*/
			if(s[dq.back()+LCP]<s[i+LCP]){
				D[i+LCP].push_back(dq.back());
				dq.pop_back();	
			}else{
				break;
			}
		}
		dq.push_back(i);
		S.insert(i);
		for(auto x:D[i])S.erase(x);
		for(auto q:Q[i])
			ans[q.second]=*S.lower_bound(q.first);
	}
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);

	return 0;
}
