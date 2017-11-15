#include<bits/stdc++.h>
using namespace std;

const int maxn=1e5+5;
int a[maxn];
struct cmp{
	bool operator()(int x,int y){
		if(a[x]!=a[y])
			return a[x]<a[y];
		return x<y;
	}
};
set<int,cmp>S;
int n,fa[maxn],deg[maxn],head[maxn];
vector<int>ans[maxn];
int main(){
	int T;cin>>T;
	while(T--){
		scanf("%d",&n);
		S.clear();
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		for(int i=1;i<=n;i++)fa[i]=0,deg[i]=2;
		for(int i=1;i<=n;i++){
			set<int,cmp>::iterator it=S.upper_bound(i);
			if(it==S.begin()){
				
			}else{
				it--;
				fa[i]=*it;
				if(!--deg[*it])
					S.erase(it);
			}
			S.insert(i);
		}
		vector<int>hd;
		for(int i=1;i<=n;i++){
			if(!fa[i]){
				head[i]=i;
				hd.push_back(i);
			}else{
				head[i]=head[fa[i]];
			}
			ans[head[i]].push_back(i);
		}
		printf("%d\n",(int)hd.size());
		for(int i=0;i<hd.size();i++){
			int x=hd[i];
			printf("%d",(int)ans[x].size());
			for(int i=0;i<ans[x].size();i++)
				printf(" %d",ans[x][i]);
			puts("");
			ans[x].clear();
		}
				
	}
	return 0;
}
