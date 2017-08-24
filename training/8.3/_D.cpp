#include<bits/stdc++.h>
#define deb(x) cerr << #x <<" = "<<x<<endl
using namespace std;
typedef long long LL;
const int N=2e4+4;
LL sgn(LL x){
	if(x>0)return 1;
	if(x<0)return -1;
	return 0;
}
LL norm(LL x){
	//TODO
	return x*x;
}
struct P{
	LL x,y;
	int id;
	P(){}
	P(LL _x,LL _y):x(_x),y(_y){}
	LL& operator[](int t){
		if(t==0)
			return x;
		return y;
	}
	void read(){
		scanf("%lld%lld",&x,&y);
	}
	friend LL dist(P a,P b){
		LL res=0;
		for(int i=0;i<2;i++)
			res+=norm(a[i]-b[i]);
		return res;
	}
};
P operator+(P a,P b){
	return P(a.x+b.x,a.y+b.y);
}
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
LL operator*(P a,P b){
	return a.x*b.y-a.y*b.x;
}
LL operator^(P a,P b){
	return a.x*b.x+a.y*b.y;
}
LL det(P a,P b,P c){
	return (b-a)*(c-a);
}
bool onLine(P p,P a,P b){
	return det(a,b,p)==0;
}
bool onSeg(P p,P a,P b){
	return onLine(p,a,b) && ((a-p)^(b-p))<=0;
}
bool inPoly(P p,P* poly,int n){
	int cnt=0;
	for(int i=0;i<n;i++){
		P a=poly[i],b=poly[(i+1)%n];
		if(onSeg(p,a,b))
			return true;
		int x=sgn(det(a,p,b));
		int y=sgn(a.y-p.y);
		int z=sgn(b.y-p.y);
		cnt+=(x>0&&y<=0&&z>0);
		cnt-=(x<0&&z<=0&&y>0);
	}
	return cnt;
}
struct Rec{
	LL mn[2],mx[2];
	Rec(){
		mn[0]=mn[1]=INT_MAX;
		mx[0]=mx[1]=INT_MIN;
	}
	void add(P p){
		for(int i=0;i<2;i++){
			mn[i]=min(mn[i],p[i]);
			mx[i]=max(mx[i],p[i]);
		}
	}
	LL dist(P p){
		LL res=0;
		for(int i=0;i<2;i++)
			res+=norm(min(max(p[i],mn[i]),mx[i])-p[i]);
		return res;
	}
};

struct Node{
	P sep;
	Rec rec;
	int c[2];
	void reset(P p){
		sep=p;
		rec=Rec();
		rec.add(p);
		c[0]=c[1]=0;
	}
}tree[N<<1];
int size,pivot;
bool compare(P a,P b){
	if(a[pivot]!=b[pivot])
		return a[pivot]<b[pivot];
	return a.id<b.id;
}
P point[N];
int build(int l,int r,int type,P *point){
	pivot=type;
	if(l>=r)return 0;
	int x=++size;
	int mid=(l+r)>>1;
	nth_element(point+l,point+mid,point+r,compare);
	tree[x].reset(point[mid]);
	for(int i=1;i<r;i++)
		tree[x].rec.add(point[i]);
	tree[x].c[0]=build(l,mid,type^1,point);
	tree[x].c[1]=build(mid+1,r,type^1,point);
	return x;
}
//priority_queue<pair<LL,int> >answer;

pair<LL,int>answer[3];

void query(int x,P p,int k,int type=1){
//cerr<<"Q "<<x<<" ing "<<endl;
	pivot=type;
	if(x==0)
		return ;
	if(answer[1].second&&tree[x].rec.dist(p)>answer[1].first)
		return ;
	
	pair<LL,int>y=make_pair(dist(tree[x].sep,p),tree[x].sep.id);
	if(y<answer[1]){
		answer[2]=answer[1];
		answer[1]=y;
	}else if(y<answer[2]){
		answer[2]=y;
	}
	
	if(compare(p,tree[x].sep)){
		query(tree[x].c[0],p,k,type^1);
		query(tree[x].c[1],p,k,type^1);
	}else{
		query(tree[x].c[1],p,k,type^1);
		query(tree[x].c[0],p,k,type^1);
	}
}


P pt[N];

P poly[33];
int n;
void solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		pt[i].read();
		pt[i].id=i;
	}
	int R;scanf("%d",&R);
	for(int r=1;r<=R;r++){
		printf("Region %d\n",r);
		int b;scanf("%d",&b);
		for(int i=0;i<b;i++)
			poly[i].read();
		int sz=0;
		for(int i=1;i<=n;i++){
			if(inPoly(pt[i],poly,b))	
				point[++sz]=pt[i];
		}
		size=0;
		build(1,sz+1,1,point);
		int m;scanf("%d",&m);
		while(m--){
			P p;p.read();
//			answer.clear();
			answer[1].first=INT_MAX;
			answer[1].second=0;
			answer[2].first=INT_MAX;
			answer[2].second=0;
			
			query(1,p,2);
			
			printf("%d %d\n",answer[1].second,answer[2].second);
		}
		
	}
}

int main(){
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case #%d:\n",t);
		solve();
	}
	return 0;
}
