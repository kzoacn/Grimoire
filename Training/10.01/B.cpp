#include<bits/stdc++.h>
using namespace std;
const int maxn=10010;
const int M=1e6+5;
typedef long double LD;
const LD eps=1e-15;
int sgn(LD x){return (x>eps)-(x<-eps);}

struct P{
	LD x,y;
	int id;
	P(){}
	P(LD _x,LD _y):x(_x),y(_y){}
	LD arg(){return atan2(y,x);}
	LD len(){return sqrt(x*x+y*y);}
	void read(){
		double tx,ty;
		scanf("%lf%lf",&tx,&ty);
		x=tx;y=ty;
	}
	
	void print(){
		printf("(%.3f,%.3f)\n",x,y);
	}
}p[maxn];


P operator+(P a,P b){
	return P(a.x+b.x,a.y+b.y);
}
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
P operator*(P a,LD b){
	return P(a.x*b,a.y*b);
}
P operator/(P a,LD b){
	return P(a.x/b,a.y/b);
}
LD operator^(P a,P b){
	return a.x*b.x+a.y*b.y;
}
LD operator*(P a,P b){
	return a.x*b.y-a.y*b.x;
}
LD det(P a,P b,P c){
	return (b-a)*(c-a);
}

LD dis(P a,P b){
	return (b-a).len();
}
P st;
bool cmp(P a,P b){
	return dis(st,a)<dis(st,b);
}

bool operator<(P a,P b){
	return sgn(a.x-b.x) ? a.x<b.x : a.y<b.y;
}
bool operator==(P a,P b){
	return sgn(a.x-b.x)==0 and sgn(a.y-b.y)==0;
}
int n;


struct L{
	P a,b;
	L(){}
	L(P a,P b):a(a),b(b){}
};
bool onLine(P p,L l){
	return sgn((l.a-p)*(l.b-p))==0;
}
bool onSeg(P p,L s){
	return onLine(p,s) and sgn((s.b-s.a)^(p-s.a))>=0 and sgn((s.a-s.b)^(p-s.b))>=0;
}
bool parallel(L l1,L l2){
	return sgn((l1.a-l1.b)*(l2.a-l2.b))==0;
}
int dir(P p,L l){
	int t=sgn((p-l.b)*(l.b-l.a));
	if(t<0)return -1;
	if(t>0)return 1;
	return 0;
}
P intersect(L l1,L l2){
	LD s1=det(l1.a,l1.b,l2.a);
	LD s2=det(l1.a,l1.b,l2.b);
	return (l2.a*s2-l2.b*s1)/(s2-s1);
}
bool segIntersect(L l1,L l2){
	if(dir(l2.a,l1)*dir(l2.b,l1)<0 && dir(l1.a,l2)*dir(l1.b,l2)<0)
		return true;
	return false;
}
struct edgelist{
	int other[M],succ[M],last[M],sum;
	void clear(){
		memset(last,-1,sizeof last);
		sum=0;
	}
	set<pair<int,int> >S;
	void addEdge(int a,int b){
		if(a>b)swap(a,b);
		if(S.count(make_pair(a,b)))return ;
		S.insert(make_pair(a,b));
	//cerr<<a<<" "<<b<<endl;
		other[sum]=b;succ[sum]=last[a];last[a]=sum++;
		other[sum]=a;succ[sum]=last[b];last[b]=sum++;
	}
}e;

vector<pair<int,LD> >vecs;
vector<int>ee[M];
vector<pair<LD,pair<int,int> > >edges;
int nxt[M],vis[M];
int main(){
	scanf("%d",&n);
	
	
	for(int i=1;i<=n;i++){
		p[i].read();
		p[i].id=i;
	}
	int m=n;
	e.clear();
	
	int sz=0;
	static P pt[M];
	
	for(int i=1;i<n;i++){
		for(int j=i+1;j<n;j++){
			L l1=L(p[i],p[i+1]);
			L l2=L(p[j],p[j+1]);
			if(!parallel(l1,l2)){
				P tmp=intersect(l1,l2);
				if(onSeg(tmp,l1)&&onSeg(tmp,l2)){
					pt[++sz]=tmp;
				}
			}
		}
	}
	sort(pt+1,pt+1+sz);
	sz=unique(pt+1,pt+1+sz)-pt-1;
	for(int j=1;j<=sz;j++)pt[j].id=j;
	
	for(int i=1;i<n;i++){
		vector<P>vec;
		L l=L(p[i],p[i+1]);
		for(int j=1;j<=sz;j++){
			if(onSeg(pt[j],l)){
				vec.push_back(pt[j]);
			}
		}
		st=p[i];
		sort(vec.begin(),vec.end(),cmp);
		for(int j=1;j<vec.size();j++)
			e.addEdge(vec[j-1].id,vec[j].id);
	}
	
	
	
	n=sz;
	
	//cerr<<sz<<endl;
	//for(int i=1;i<=sz;i++)
	///	pt[i].print();
	LD ans=0;
	for(int x=1;x<=n;x++){
		vector<pair<LD,int> >pairs;
		for(int i=e.last[x];~i;i=e.succ[i]){
			int y=e.other[i];
			assert(!(pt[y]==pt[x]));
			pairs.push_back(make_pair((pt[y]-pt[x]).arg(),i));
		}
		sort(pairs.begin(),pairs.end());
		for(int i=0;i<pairs.size();i++){
			nxt[pairs[(i+1)%pairs.size()].second^1]=pairs[i].second;
		}
	}
	memset(vis,0,sizeof vis);
	LD tot=0;
	for(int start=0;start<e.sum;start++){
		if(vis[start])continue;
		LD total=0;
		int now=start;
		vecs.clear();
		while(!vis[now]){
			vis[now]=1;
			total+=pt[e.other[now^1]]*pt[e.other[now]];
			now=nxt[now];
		}
		if(now==start&&total>0){
			ans+=total;
		}
	}
	
	printf("%.10f\n",(double)ans/2);
	
	return 0;
}
