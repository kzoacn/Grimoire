#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n,m,r;
int mn[maxn],c[maxn];
int main(){

	int T;cin>>T;
	for(int t=1;t<=T;t++){
		scanf("%d%d%d",&n,&m,&r);
		for(int i=1;i<=n;i++){
			scanf("%d",&c[i]);
			mn[i]=i<r ? i :r ;
		}
		for(int i=1;i<=m;i++){
			int x,y;
			scanf("%d%d",&x,&y);
			if(x>y)swap(x,y);
			mn[y]=min(mn[y],x);
		}
		if(r!=1)c[1]--;
		
		vector<int>seg;
		for(int i=1;i<=n;i++)if(i!=r){
			seg.push_back(mn[i]);
		}
		
		sort(seg.begin(),seg.end());
		int j=0;
		for(int i=1;i<=n;i++){
			while(j<seg.size()&&i>seg[j])j++;
			while(j<seg.size()){
				if(c[i]&&seg[j]>=i){
					c[i]--;
					j++;
				}else break;
			}
		}
		long long ans=0;
		for(int i=1;i<=n;i++)
			ans+=c[i];
		printf("Case #%d: %lld\n",t,ans);
	}

	return 0;
}
