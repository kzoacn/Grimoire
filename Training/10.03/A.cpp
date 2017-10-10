#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=5e4+4;
struct P{
	LL x,y;
	P(){}
	P(LL _x,LL _y):x(_x),y(_y){}
	void read(){
		scanf("%lld%lld",&x,&y);
	}
};
bool operator<(P a,P b){
	return a.x!=b.x ? a.x<b.x : a.y<b.y;
}
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
LL operator^(P a,P b){
	return a.x*b.x+a.y*b.y;
}
LL operator*(P a,P b){
	return a.x*b.y-a.y*b.x;
}
LL det(P a,P b,P c){
	return (b-a)*(c-a);
}
struct CH{
	vector<P>ch,up,dw;
	void clear(){
		ch.clear();
		up.clear();
		dw.clear();
		
	}
	void build(){
		sort(ch.begin(),ch.end());
		for(int i=0;i<ch.size();i++){
			while(dw.size()>=2&&det(dw[dw.size()-2],dw.back(),ch[i])<=0)
				dw.pop_back();
			dw.push_back(ch[i]);
		}
		for(int i=0;i<ch.size();i++){
			while(up.size()>=2&&det(up[up.size()-2],up.back(),ch[i])>=0)
				up.pop_back();
			up.push_back(ch[i]);
		}
	}
	
	
	LL Qmax(vector<P>&ch,P p){
		int l=0,r=(int)ch.size()-1;
		LL ans=-3e18;
		while(r-l>3){
			int mid1=l+(r-l)/3;
			int mid2=r-(r-l)/3;
			if((p^ch[mid1])>(p^ch[mid2]))
				r=mid2;
			else
				l=mid1;
		}
		for(int i=l;i<=r;i++)
			ans=max(ans,p^ch[i]);
		return ans;
	}
	
	LL Qmax(P p){
		return max(Qmax(up,p),Qmax(dw,p));
	}
};




int n;


P p[maxn];
int ty[maxn];

int id(int l,int r){
	return l+r|l!=r;
}
CH t[maxn*2];

void Add(int l,int r,int l0,int r0,P p){
	if(l0<=l&&r0>=r){
		t[id(l,r)].ch.push_back(p);
		return;
	}
	int mid=(l+r)>>1;
	if(l0<=mid)Add(l,mid,l0,r0,p);
	if(r0>mid)Add(mid+1,r,l0,r0,p);
	
}

void build(int l,int r){
	t[id(l,r)].build();
	if(l==r)return ;
	int mid=(l+r)>>1;
	build(l,mid);
	build(mid+1,r);
}
void init(int l,int r){
	t[id(l,r)].clear();
	if(l==r)return ;
	int mid=(l+r)>>1;
	init(l,mid);
	init(mid+1,r);
}
LL Q(int l,int r,int ps,P p){
	if(l==r)
		return t[id(l,r)].Qmax(p);
	LL ans=t[id(l,r)].Qmax(p);
	int mid=(l+r)>>1;
	if(ps<=mid)return max(ans,Q(l,mid,ps,p));
	else return max(ans,Q(mid+1,r,ps,p));
}

int main(){
	while(scanf("%d",&n)==1&&n){
		init(1,n);
		map<P,int>M;
		for(int i=1;i<=n;i++){
			scanf("%d",&ty[i]);
			p[i].read();
			if(ty[i]==1){
				M[p[i]]=i;	
			}else if(ty[i]==-1){
				Add(1,n,M[p[i]],i,p[i]);
				M.erase(p[i]);
			}
		}
		for(auto p:M)
			Add(1,n,p.second,n,p.first);
		build(1,n);
		
		for(int i=1;i<=n;i++){
			if(ty[i]==0)
				printf("%lld\n",Q(1,n,i,p[i]));
		}
	}
	return 0;
}
