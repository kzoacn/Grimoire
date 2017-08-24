#include<bits/stdc++.h>
#define deb(x) cerr<< #x << " = " <<x<<endl;

#define __advance __attribute__((optimize("O3"))) __inline 

using namespace std;
const int maxn=1e5+5;
typedef unsigned int UL;
const UL base=233;
UL h_l[maxn];
int siz[maxn],f[maxn],dep[maxn],cant[maxn],root,All,d[maxn];
vector<int>G[maxn];
char c[maxn],str[maxn];
int n,m;

struct Hash{
	int len;
	UL h;
	Hash(){len=0;h=0;}
	Hash(char c){len=1;h=c;}
	__advance void push_back(char c){
		h=h*base+c;
		len++;
	}
	__advance void push_front(char c){
		h+=h_l[len]*c;
		len++;
	}
	__advance bool operator<(const Hash &oth)const{
		return h<oth.h;
	}
	__advance bool operator==(const Hash &oth)const{
		return h==oth.h;
	}
	
};
struct ha{
	__advance UL operator()(const Hash &h)const{
		return h.h;
	}
};
unordered_set<Hash,ha>P,S,pre;
unordered_map<Hash,Hash,ha>oppo;
/*__advance void makert(int u,int fa){
	siz[u]=1;f[u]=0;
	for(auto v:G[u]){
		if(v==fa||cant[v])continue;
		dep[v]=dep[u]+1;
		makert(v,u);
		siz[u]+=siz[v];
		f[u]=max(f[u],siz[v]);
	}
	f[u]=max(f[u],All-f[u]);
	if(f[root]>f[u])
		root=u;
}*/


__advance void getsz(int u,int fa){
	siz[u]=1;f[u]=0;
	for(auto v:G[u]){
		if(v==fa||cant[v])continue;
		dep[v]=dep[u]+1;
		getsz(v,u);
		siz[u]+=siz[v];
	}
}
__advance int getrt(int u,int fa){
	for(auto v:G[u]){
		if(v==fa||cant[v])continue;
		if(siz[v]*2>=All){
			return root=getrt(v,u);
		}
	}
	return root=u;
}
__advance void makert(int u,int fa){
	getsz(u,fa);
	getrt(u,fa);
}

int sz1=0,sz2=0;
Hash odata[maxn],rdata[maxn];
__advance void dfs(int u,int fa,Hash ori,Hash rev){
	odata[++sz1]=ori;
	rdata[++sz2]=rev;

	for(auto v:G[u]){
		if(v==fa||cant[v])continue;
		
		Hash tori=ori;
		Hash trev=rev;
		
		tori.push_back(c[v]);
		trev.push_front(c[v]);
		
		dfs(v,u,tori,trev);
	}
}
int flag=0;
int mxdep=0;
__advance void dfsdep(int u,int fa){
	mxdep=max(mxdep,dep[u]);
	for(auto v:G[u]){
		if(v==fa||cant[v])continue;
		dfsdep(v,u);
	}
}



__advance void calc(int u){
//cerr<<u<<endl;



	int mx1=0,mx2=0;
	for(auto v:G[u]){
		mxdep=0;
		if(cant[v])continue;
		dfsdep(v,u);
		if(mxdep>=mx1){
			mx2=mx1;
			mx1=mxdep;
		}else if(mxdep>=mx2){
			mx2=mxdep;
		}
	}
	if(mx1+mx2+2<m)return ;
	


	pre.clear();
	pre.insert(Hash(c[u]));
	for(auto v:G[u]){
		if(cant[v])continue;
		sz1=sz2=0;
		dfs(v,u,Hash(c[v]),Hash(c[v]));
		odata[++sz1]=Hash();
		for(int i=1;i<=sz1;i++){
		
			if(P.count(odata[i])){
				if(pre.count(oppo[odata[i]])){
					flag=1;
					return;
				}
			}
		}
		for(int i=1;i<=sz2;i++){
			rdata[i].push_back(c[u]);
			if(S.count(rdata[i]))
				pre.insert(rdata[i]);
		}
		
		
		
	}
	
}
__advance void solve(int u){
	if(flag||siz[u]<m-1)return ;
	
	//cout<<u<<endl;
	calc(u);cant[u]=1;
	for(auto v:G[u]){
		if(cant[v])continue;
		All=siz[v];
		f[root=0]=n+1;
		makert(v,0);
		solve(root);
	}
}


UL has[maxn];
__advance UL get(int l,int r){
	return has[r]-has[l-1]*h_l[r-l+1];
}

__advance bool solve(char *str,int m){
	P.clear();
	oppo.clear();
	for(int i=1;i<=n;i++){
		cant[i]=0;
		
	}
	for(int i=1;i<=m;i++){
		has[i]=has[i-1]*base+str[i];
	}
	for(int i=0;i<=m;i++){
		Hash h1,h2;
		h1.len=i;h2.len=m-i;
		h1.h=get(1,i);
		h2.h=get(i+1,m);
		S.insert(h1);
		P.insert(h2);
		oppo[h2]=h1;
		
	}
	
	
	All=n;
	f[root=0]=n+1;
	makert(1,1);
	flag=0;
	solve(root);
	return flag;
}

__advance int getint(){
	char c=getchar();int x=0;
	while(!isdigit(c))c=getchar();
	while(isdigit(c))x=x*10+c-'0',c=getchar();
	return x;
}

__advance void solve(){
	
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		G[i].clear();
	}
	for(int i=1;i<n;i++){
		int u=getint(),v=getint();
		G[u].push_back(v);
		G[v].push_back(u);
	}
	scanf("%s",c+1);
	scanf("%s",str+1);
	m=strlen(str+1);

	if(solve(str,m)){
		puts("Find");
		return ;
	}
	reverse(str+1,str+1+m);
	if(solve(str,m)){
		puts("Find");
		return ;
	}
	puts("Impossible");
}
int main(){
	h_l[0]=1;
	for(int i=1;i<maxn;i++)
		h_l[i]=h_l[i-1]*base;
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case #%d: ",t);
		solve();
	}
}

