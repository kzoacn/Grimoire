#include<bits/stdc++.h>
using namespace std;
const int maxn=222;
int n;
vector<int>lnk[maxn];
int mp[maxn][maxn];
int match[maxn],Queue[maxn],head,tail;
int pred[maxn],base[maxn],sta,fin,nbase;
bool inQ[maxn],inB[maxn];
void push(int u){Queue[tail++]=u;inQ[u]=1;}
int pop(){return Queue[head++];}
int FindCA(int u,int v){
	static bool inP[maxn];
	fill(inP,inP+n,false);
	while(true){u=base[u];inP[u]=1;if(u==sta)break;u=pred[match[u]];}
	while(true){v=base[v];if(inP[v])break;v=pred[match[v]];}
	return v;
}
void RT(int u){
	int v;
	while(base[u]!=nbase){
		v=match[u];
		inB[base[u]]=inB[base[v]]=1;
		u=pred[v];
		if(base[u]!=nbase)pred[u]=v;
	}
}
void BC(int u,int v){
	nbase=FindCA(u,v);
	fill(inB,inB+n,0);
	RT(u);RT(v);
	if(base[u]!=nbase)pred[u]=v;
	if(base[v]!=nbase)pred[v]=u;
	for(int i=0;i<n;i++)
	if(inB[base[i]]){
		base[i]=nbase;
		if(!inQ[i])push(i);
	}
}
bool FindAP(int u){
	bool found=false;
	for(int i=0;i<n;i++){
		pred[i]=-1;base[i]=i;
		inQ[i]=0;
	}
	sta=u;fin=-1;head=tail=0;push(sta);
	while(head<tail){
		int u=pop();
		for(int i=(int)lnk[u].size()-1;i>=0;i--){
			int v=lnk[u][i];
			if(base[u]!=base[v]&&match[u]!=v)
				if(v==sta||(match[v]>=0&&pred[match[v]]>=0))
					BC(u,v);
				else if(pred[v]==-1){
					pred[v]=u;
					if(match[v]>=0)push(match[v]);
					else {fin=v;return true;}
				}
		}
	}	
	return found;
}
void AP(){
	int u=fin,v,w;
	while(u>=0){
		v=pred[u];
		w=match[v];
		match[v]=u;
		match[u]=v;
		u=w;
	}
}
int FindMax(){
	for(int i=0;i<n;i++)match[i]=-1;
	for(int i=0;i<n;i++)if(match[i]==-1)
	if(FindAP(i))
		AP();
	int ans=0;
	for(int i=0;i<n;i++)
		ans+=(match[i]!=-1);
	return ans;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		int m;scanf("%d",&m);
		while(m--){
			int x;scanf("%d",&x);
			mp[i][x]=1;
		}
	}
	for(int i=1;i<=n;i++)
	for(int j=i+1;j<=n;j++){
		if(mp[i][j]&&mp[j][i]){
			lnk[i-1].push_back(j-1);
			lnk[j-1].push_back(i-1);
		}
	}
	int ans=FindMax();
	if(ans==n)puts("YES");
	else puts("NO");
	return 0;
}
