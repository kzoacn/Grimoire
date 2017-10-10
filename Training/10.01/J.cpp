#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+6;
int fa[maxn];
int a[maxn],dep[maxn],sum[maxn];
int n,pos[maxn];
vector<int>G[maxn];
bool cmp(int x,int y){
	if(dep[x]!=dep[y])
		return dep[x]>dep[y];
	return sum[x]>sum[y];
}

long long calc(int s){
	
	queue<int>q;q.push(s);
	dep[s]=1;
	static int id[maxn];
	int sz=0;
	while(!q.empty()){
		int u=q.front();q.pop();
		id[++sz]=u;
		for(int i=0;i<G[u].size();i++){
			int v=G[u][i];
			if(!dep[v]){
				dep[v]=dep[u]+1;
				q.push(v);
			}
		}
	}
	sort(id+1,id+1+sz,cmp);
	for(int i=1;i<=sz;i++){
		int u=id[i];
		sum[u]+=a[u];
		sum[fa[u]]+=sum[u];
	}	
	
	static int tmp[maxn];
	long long ans=0;
	for(int i=1;i<=sz;i++){
		int u=id[i];
		for(int j=0;j<G[u].size();j++){
			int v=G[u][j];
			tmp[j]=sum[v];
		}	
		sort(tmp,tmp+G[u].size());
		reverse(tmp,tmp+G[u].size());
		for(int j=0;j<G[u].size();j++)
			ans+=j*tmp[j];
	}
	
	return ans;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&a[i],&fa[i]);
		fa[i]++;
		G[fa[i]].push_back(i);
	}
	long long ans=0;
	for(int i=1;i<=n;i++)if(!dep[i]){
		ans+=calc(i);
	}
	cout<<ans<<endl;

	return 0;
}
