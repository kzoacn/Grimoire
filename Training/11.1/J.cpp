#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=5e4+4;
const double eps=1e-9;
int sgn(double x){return (x>eps)-(x<-eps);}
template <class T>
inline T sqr(const T &x) {
	return x * x;
}
int n,q;
int id(int l,int r){return l+r|l!=r;}

struct node{
	
}t[maxn*2];


struct P{
	double x, y;
	P() {}
	P(double x, double y): x(x), y(y) {}
	double len2() { return sqr(x) + sqr(y); }
	double len() { return sqrt(len2()); }
	void print() { printf("(%.3f,%.3f)\n", x, y); }
	P turn90() { return P(-y, x); }
	P norm() { return P(x / len(), y / len()); }
	
	int quad()const{
		return sgn(y)==1 || (sgn(y)==0&&sgn(x)>=0);
	}
};
bool operator == (P a, P b) {
	return !sgn(a.x - b.x) && !sgn(a.y - b.y);
}
P operator + (P a, P b) {
	return P(a.x + b.x, a.y + b.y);
}
P operator - (P a, P b) {
	return P(a.x - b.x, a.y - b.y);
}
P operator * (P a, double b) {
	return P(a.x * b, a.y * b);
}
P operator / (P a, double b) {
	return P(a.x / b, a.y / b);
}
double operator ^ (P a, P b) {
	return a.x * b.x + a.y * b.y;
}
double operator * (P a, P b) {
	return a.x * b.y - a.y * b.x;
}
double det(P a, P b, P c) {
	return (b - a) * (c - a);
}
double dis(P a, P b) {
	return (b - a).len();
}
double Area(vector<P> poly) {
	double ans = 0;
	for (int i = 1; i < poly.size(); ++i)
		ans += (poly[i] - poly[0]) * (poly[(i + 1) % poly.size()] - poly[0]);
	return fabs(ans) / 2;
}
struct L{
	P a, b;
	L() {}
	L(P a, P b): a(a), b(b) {}
	P v() { return b - a; }
	bool onLeft(const P &p)const{
		return sgn((b-a)*(p-a))>0;
	}
	L push()const{
		const double eps=1e-10;
		P delta=(b-a).turn90().norm()*eps;
		return L(a-delta,b-delta);
	}
	
};
bool onLine(P p, L l) {
	return sgn((l.a - p) * (l.b - p)) == 0;
}
bool onSeg(P p, L s) {
	return onLine(p, s) && sgn((s.b - s.a) ^ (p - s.a)) >= 0 && sgn((s.a - s.b) ^ (p - s.b)) >= 0;
}
bool parallel(L l1, L l2) {
	return sgn(l1.v() * l2.v()) == 0;
}
P intersect(L l1, L l2) {
	double s1 = det(l1.a, l1.b, l2.a);
	double s2 = det(l1.a, l1.b, l2.b);
	return (l2.a * s2 - l2.b * s1) / (s2 - s1);
}
bool sameDir(const L &l0,const L &l1){
	return parallel(l0,l1) && sgn((l0.b-l0.a)^(l1.b-l1.a))==1;
}
bool operator < (const P &a, const P &b) {
	if (a.quad() != b.quad())
		return a.quad() < b.quad();
	else
		return sgn(a * b) > 0;
}
bool operator<(const L &l0,const L &l1){
	if(sameDir(l0,l1))
		return l1.onLeft(l0.a);
	else
		return (l0.b-l0.a)<(l1.b-l1,a);
}
bool check(L u,L v,L w){
	return w.onLeft(intersect(u,v));
}
vector<P>intersection(vector<L> &l){
	sort(l.begin(), l.end());
	deque<L> q;
	for (int i = 0; i < (int)l.size(); ++i) {
		if (i && sameDir(l[i], l[i - 1])) continue;
		while (q.size() > 1 && !check(q[q.size() - 2], q[q.size() - 1], l[i]))
			q.pop_back();
		while (q.size() > 1 && !check(q[1], q[0], l[i]))
			q.pop_front();
		q.push_back(l[i]);
	}
	while (q.size() > 2 && !check(q[q.size() - 2], q[q.size() - 1], q[0]))
		q.pop_back();
	while (q.size() > 2 && !check(q[1], q[0], q[q.size() - 1]))
		q.pop_front();
	vector<P> ret;
	for (int i = 0; i < (int)q.size(); ++i)
		ret.push_back(intersect(q[i], q[(i + 1) % q.size()]));
	return ret;
}


struct qes{
	int op;
	int l,r;
	
};

void build(int l,int r){
	int x=id(l,r);
	
	if(l==r){
		return ;
	}
	int mid=(l+r)>>1;
	build(l,mid);
	build(mid+1,r);
}

int main(){
	int T;cin>>T;
	while(T--){
		scanf("%d%d",&n,&q);
		build(1,q);	
		multimap<pair<int,int>,int>M;
		for(int i=1;i<=n;i++){
			pair<int,int>l;
			scanf("%d%d",&l.first,&l.second);
			M[l]=1;
		}
		for(int i=1;i<=q;i++){
			int op,a,b;
			scanf("%d%d%d",&op,&a,&b);
			Q[i].op=op;
			if(op==0){
				Q[i].l=a;
				Q[i].l=b;
			}else if(op==1){
				M[];
			}else{
			
			}
		}
	}
	return 0;
}
