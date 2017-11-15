#include<bits/stdc++.h>
#define deb(x) cerr<<#x"="<<x<<endl;
using namespace std;
typedef long long LL;
const int maxn=5e4+10;
const int MAGIC=233;

struct P{
	LL x,y;
	int id;
	P(){}
	P(LL _x,LL _y):x(_x),y(_y){}
	void print(){
		printf("(%lld,%lld)\n",x,y);
	}
}p[maxn];
P operator+(P a,P b){
	return P(a.x+b.x,a.y+b.y);
}
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
LL operator*(P a,P b){
	return a.x*b.y - a.y*b.x;
}
LL operator^(P a,P b){
	return a.x*b.x + a.y*b.y;
}
LL det(P a,P b,P c){
	return (b-a)*(c-a);
}
bool operator<(P a,P b){
	return a.x!=b.x ? a.x<b.x : a.y<b.y;
}


P pt[maxn];
struct Convex{
	
	vector<P>ch;
	void convex(P *tmp,int sz) {
//		sort(p.begin(), p.end());
		for(int i=0;i<sz;i++)pt[i]=tmp[i];
		stable_sort(pt,pt+sz);
		vector<P> S;
		for (int i = 0; i < sz; ++i) {
			while (S.size() >= 2 && (det(S[S.size() - 2], S.back(), pt[i])) >= 0)
				S.pop_back();
			S.push_back(pt[i]);
		}
		ch=S;
	}
	
	pair<LL,int> Qmax(P p){
		int l=0,r=(int)ch.size()-1;
		while(r-l>3){
			int mid1=l+(r-l)/3;
			int mid2=r-(r-l)/3;
			if((p^ch[mid1])>=(p^ch[mid2]))
				r=mid2;
			else
				l=mid1;
		}
		pair<LL,int>ans(-(1LL<<60),0);
		for(int i=l;i<=r;i++)
			ans=max(ans,make_pair(p^ch[i],-ch[i].id));
		return ans;
	}
	
};

int n,m;
LL a[maxn];

LL Psum,Nsum;

int bel[maxn],lef[maxn],rig[maxn],bcnt;

Convex ch[maxn/MAGIC+20];

LL sP[maxn],sN[maxn];

void rebuild(int idx){
	
	LL sump=0,sumn=0;
	int len=0;
	for(int i=lef[idx];i<=rig[idx];i++){
		if(a[i]>0)
			sump+=a[i];
		else
			sumn+=a[i];
		p[i]=P(sump,sumn);
		p[i].id=i;
		len++;
		
	//	p[i].print();
	}
	sP[idx]=sump;sN[idx]=sumn;
	
	
	ch[idx].convex(p+lef[idx],len);
	/*cerr<<"convex:"<<endl;
	for(auto p:ch[idx].ch)
		p.print();
	cerr<<"end"<<endl;*/
}

int Qmax(){
	//cerr<<Psum<<" "<<Nsum<<endl; 
	//deb(bcnt);
	//cerr<<bcnt<<endl;
	LL sump=0,sumn=0;
	pair<LL,int>ans(-(1LL<<60),0);
	for(int i=1;i<=bcnt;i++){
		auto pii=ch[i].Qmax(P(llabs(Nsum),Psum));
		ans=max(ans,make_pair(llabs(Nsum)*sump+Psum*sumn+pii.first,pii.second));
		sump+=sP[i];
		sumn+=sN[i];
	}
	return -ans.second;
}

int main(){
//freopen("joker.in","r",stdin);
//freopen("joker.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		if(a[i]>0)Psum+=a[i];
		if(a[i]<0)Nsum+=a[i];
		bel[i]=i/MAGIC+1;
		lef[i]=n+1;
		rig[i]=0;
	}
	bcnt=*max_element(bel+1,bel+1+n);
	
	for(int i=1;i<=n;i++){
		lef[bel[i]]=min(lef[bel[i]],i);
		rig[bel[i]]=max(rig[bel[i]],i);
	}

	for(int i=1;i<=bcnt;i++)
		rebuild(i);
	
	
		printf("%d\n",Qmax());	
	while(m--){
		int ps;LL x;
		scanf("%d%lld",&ps,&x);
		if(a[ps]>0){
			Psum-=a[ps];
		}else{
			Nsum-=a[ps];
		}
		a[ps]=x;
		if(a[ps]>0){
			Psum+=a[ps];
		}else{
			Nsum+=a[ps];
		}
		
		rebuild(bel[ps]);
		
		printf("%d\n",Qmax());	
	}	
	
	return 0;
}
