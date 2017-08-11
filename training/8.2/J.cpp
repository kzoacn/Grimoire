#include<bits/stdc++.h>
const int maxn=30030;
using namespace std;
int m,n;

struct seg{
	int l,r;
};
vector<seg>se[maxn];

void push(int x,int l,int r){
	if(x<0||x>=m)return ;
	l=max(l,0);
	r=min(r,m-1);
	if(l>=m||r<0)return ;
	se[x].push_back((seg){l,r});
}

struct BIT{
	int d[maxn];
	int vis[maxn],T;
	BIT(){T=1;}
	void clear(){
		T++;
	}
	void add(int x,int y){
		while(x<maxn){
			if(vis[x]!=T){
				vis[x]=T;
				d[x]=0;
			}
			d[x]+=y;
			x+=x&-x;
		}
	}
	void add(int l,int r,int y){
	
		l++;r++;
	
		add(l,y);
		add(r+1,-y);
	}
	int get(int x){
	
		x++;
	
		int ans=0;
		while(x){
			if(vis[x]!=T){
				vis[x]=T;
				d[x]=0;
			}
			ans+=d[x];
			x-=x&-x;
		}
		return ans;
	}
}T;

long long calc(vector<seg>&se){
	T.clear();
	static int tmp[maxn*2];
	int sz=0;
	for(auto inter:se){
		T.add(inter.l,inter.r,1);
//		cerr<<inter.l<<" "<<inter.r<<endl;
		tmp[++sz]=inter.l;
		tmp[++sz]=inter.r+1;
	}
	
	//for(int i=0;i<=5;i++)
	//	cerr<<i<<":"<<T.get(i)<<endl;
	
	sort(tmp+1,tmp+1+sz);
	sz=unique(tmp+1,tmp+1+sz)-tmp-1;
	long long ans=0;
	for(int i=1;i+1<=sz;i++){
		ans+=(tmp[i+1]-tmp[i])*(T.get(tmp[i])%2);
	}
	return ans;
}

int main(){
freopen("J.in","r",stdin);
	scanf("%d%d",&m,&n);
	for(int k=1;k<=n;k++){
		int x,y,p,dir;
		scanf("%d%d%d%d",&x,&y,&p,&dir);
		if(dir==0)y--;
		if(dir==2)x--;
		if(dir==3)x--,y--;
		for(int i=0;i<p;i++){
			if(dir==0){
				push(x+i,y-p+1+i,y);
			}
			if(dir==1){
				push(x+i,y,y+p-1-i);
			}
			if(dir==2){
				push(x-i,y,y+p-1-i);
			}
			if(dir==3){
				push(x-i,y-p+1+i,y);
			}
		}
	}
	

//	cerr<<calc(se[2])<<endl;
//	return 0;
	long long ans=0;
	for(int i=0;i<m;i++){
//		cerr<<"i="<<i<<endl;
//		cerr<<calc(se[i])<<endl;
		ans+=calc(se[i]);
	}
	cout<<ans<<endl;
	return 0;
}
