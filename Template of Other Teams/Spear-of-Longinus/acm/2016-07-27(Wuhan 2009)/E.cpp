#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>
#include<cctype>
#include<map>
#include<cassert>
using namespace std;
const int maxn=200005;
int n,Qs,t;
char cmd[200001];
int a[2005];
int value[maxn];
int cur;
int len=0;
int getn(){
	int r=0;static char c=cmd[cur++];
	while(!isdigit(c))c=cmd[cur++];
	while(cur<len&&isdigit(c))r=r*10+c-'0',c=cmd[cur++];
	return r;
}
int fa[maxn],siz[maxn],known[maxn];
int find(int x){
	if(fa[x] == x) {
		return x;
	}
	fa[x] = find(fa[x]);
	return fa[x];
}
void merg(int x,int y){
	int fy = find(y);
	int fx = find(x);
	siz[fy]+=siz[fx];
	fa[fx]=fy;
}
void Q(int k){

	static map<int,int>M;
	M.clear();
	
	for(int i=0;i<k;i++){
		M[find(a[i])]++;
	}
	
	int ans=0;
	for(map<int,int>::iterator it=M.begin();it!=M.end();it++){
		if(!known[it->first]&&it->second%2==1){
			puts("I don't know.");
			return;
		}	
	}	
	
	for(int i=0;i<k;i++){
		if(known[a[i]]){
			ans^=value[a[i]];
		}else{
			ans^=value[a[i]];
		}
	}
	
	printf("%d\n",ans);
}
struct edge{
	int u,v,w;
};
vector<edge>G[maxn];


int Know=0;

void dfs(int u,int fa,int val){
	value[u]=val;
	
	known[u]=Know;
	
	for(int i=0;i<G[u].size();i++){
		edge e=G[u][i];
		if(e.v==fa)continue;
		dfs(e.v,u,val^e.w);
	}
}
bool I(int p,int v){
	if(known[p]){
		if(value[p]!=v)
			return false;
		else {
			return true;
		}
	}else{
		Know=1;
		value[p]=v;
		dfs(p,-1,v);
		return true;
	}
}
bool I(int p,int q,int v){

	//cerr<<p<<" "<<q<<" "<<v<<endl;

	int fp = find(p);
	int fq = find(q);
	
	if(fp==fq){
		if((value[p]^value[q])!=v)
			return false;
		else
			return true;
	}
		G[p].push_back((edge){p,q,v});
		G[q].push_back((edge){q,p,v});

	if(!known[p]&&!known[q]){
		if(siz[fp]>siz[fq])
			swap(p,q);
		merg(p,q);
		
		Know=0;
		dfs(p,q,v^value[q]);

	}else{
		if(known[p]&&known[q]){
			merg(p,q);
			if((value[p]^value[q])!=v)
				return false;
			else 
				return true;
		}
		if(known[q])
			swap(p,q);
		
		merg(q,p);
		Know=1;
		dfs(q,p,v^value[p]);
		
	}
	return true;
}
int main(){
	while(scanf("%d%d",&n,&Qs)==2){
		if(!n&&!Qs)break;
		printf("Case %d:\n",++t);
		bool conflicting=0;
		int facts=0;
		for(int i=0;i<n;i++){
			fa[i]=i;
			siz[i]=1;
			known[i]=0;
			value[i]=0;
			G[i].clear();
		}
		while(Qs--){
			len=0;
			char c=getchar();
			while(c!=' '&&!isalpha(c)&&!isdigit(c))
				c=getchar();			
			while(c==' '||isalpha(c)||isdigit(c))
				cmd[len++]=c,c=getchar();
			
			if(conflicting)continue;
			
//			puts("value");
//			for(int i=0;i<n;i++)
//				printf("%d%c",value[i]," \n"[i+1==n]);
			
			
			//len=strlen(cmd);
			cmd[len++]=' ';
			cmd[len]='\0';
			
			//cerr<<cmd<<endl;
			
			int p=0,q=0,v=0;
			if(cmd[0]=='Q'){
				cur=0;
				int k=getn();
				for(int i=0;i<k;i++){
					a[i]=getn();	
					//cerr<<a[i]<<" \n"[i+1==k];
				}
				Q(k);		
			}else{
				facts++;
				int blanks=0;
				cur=0;
				for(int i=1;i<len;i++) {
					if(cmd[i] != cmd[i - 1] && cmd[i] == ' ') {
						blanks++;
					}
				}
				if(blanks==3){
					p=getn();v=getn();
					
					if(!I(p,v)){
						printf("The first %d facts are conflicting.\n",facts);
						conflicting=1;
					}
				}else{
					p=getn();q=getn();v=getn();
					
					
					if(!I(p,q,v)){
						printf("The first %d facts are conflicting.\n",facts);
						conflicting=1;
					}
				}
			}
		}
			puts("");
	}
	return 0;
}


