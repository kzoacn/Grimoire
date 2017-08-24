#include<bits/stdc++.h>
using namespace std;
int n;
vector<int>G[44];
int greed(){
	int use[60],deg[60];
	for (int i = 1; i <= n; ++i) {
	  use[i] = false;
		deg[i] = G[i].size();
	}
	int ans = 0;
	while (true) {
	  int mx = -1, u;
		for (int i = 1; i <= n; ++i) {
		  if (use[i])
		      continue;
		    if (deg[i] >= mx) {
		      mx = deg[i];
		        u = i;
		    }
		}
		if (mx <= 0)
		  break;
		++ans;
		use[u] = true;
		for (auto v:G[u])
		  --deg[v];
	}
	return ans;
}

bool check(int S){
	for(int i=1;i<=n;i++){
		if(S>>(i-1)&1)continue;
		for(auto v:G[i]){
			if(!((S>>(v-1))&1))
				return false;
		}
	}
	return true;
}
int bf(){
	int ans=n+1;
	for(int S=1;S<(1<<n);S++){
		int res=__builtin_popcount(S);
		if(res>=ans)continue;
		if(check(S)){
			ans=min(ans,res);
		}
	}
	return ans;
}

pair<int,int>pack(int a,int b){
	if(a>b)swap(a,b);
	return make_pair(a,b);
}
void randGraph(){
	for(int i=1;i<=n;i++)
		G[i].clear();
	vector<pair<int,int> >E;
	int m=rand()%(n*n)+1;
	while(m--){
		int u=rand()%n+1;
		int v=rand()%n+1;
		while(u==v){
			u=rand()%n+1;
			v=rand()%n+1;
		}
		E.push_back(pack(u,v));
	}
	sort(E.begin(),E.end());
	E.erase(unique(E.begin(),E.end()),E.end());
	for(auto e:E){
		G[e.first].push_back(e.second);
		G[e.second].push_back(e.first);
	}
}
void output(){
	for(int i=1;i<=n;i++){
		for(auto v:G[i]){
			if(v>i)
				printf("%d %d\n",v,i);
		}
	}
	puts("");
}

int main(){
srand(time(0));
	int TAT=5000000;
	double mx=0;
	while(TAT--){
		n=rand()%15+3;;
		randGraph();
		int ans1=greed();
		int ans2=bf();
		if((double)ans1/ans2>mx){
			mx=(double)ans1/ans2;
			
			output();
			cerr<<"best is "<<mx<<endl;
		}
	}

	return 0;
}
