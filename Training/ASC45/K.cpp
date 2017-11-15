#include<bits/stdc++.h>
using namespace std;
const int maxn=212;
const double eps=1e-9;
int sgn(double x){return (x>eps)-(x<-eps);}
struct P{
	double x,y;
	P(){}
	P(double _x,double _y):x(_x),y(_y){}
	double len(){return sqrt(x*x+y*y);}
	P turn90(){
		return P(-y,x);
	}
	P norm(){
		return P(x/len(),y/len());
	}
	int quad()const{
		return sgn(y)==1 || (sgn(y)==0&&sgn(x)>=0);
	}
	void read(){
		scanf("%lf%lf",&x,&y);
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
P operator*(P a,double b){
	return P(a.x*b,a.y*b);
}
P operator/(P a,double b){
	return P(a.x/b,a.y/b);
}
double operator^(P a,P b){
	return a.x*b.x + a.y*b.y;
}
double operator*(P a,P b){
	return a.x*b.y - a.y*b.x;
}
double det(P a,P b,P c){
	return (b-a)*(c-a);
}


struct L{
	P a,b;
	L(){}
	L(P _a,P _b):a(_a),b(_b){}
	bool onLeft(P p){return sgn((b-a)*(p-a))>0;}
	L push(){
		const double eps=1e-10;
		P delta=(b-a).turn90().norm()*eps;
		return L(a-delta,b-delta);
	}
	P v(){return b-a;}
};

bool parallel(L l1,L l2){
	return sgn(l1.v()*l2.v())==0;
}
P intersect(L l1,L l2){
	double s1=det(l1.a,l1.b,l2.a);
	double s2=det(l1.a,l1.b,l2.b);
	return (l2.a*s2-l2.b*s1)/(s2-s1);
}

bool sameDir(L l0,L l1){
	return parallel(l0,l1) && sgn((l0.b-l0.a)^(l1.b-l1.a))==1;
}
bool operator<(P a,P b){
	if(a.quad()!=b.quad())
		return a.quad()<b.quad();
	else
		return sgn(a*b)>0;
}
bool operator<(L l0,L l1){
	if(sameDir(l0,l1))
		return l1.onLeft(l0.a);
	else
		return (l0.b-l0.a)<(l1.b-l1.a);
}
bool check(L u,L v,L w){
	return w.onLeft(intersect(u,v));
}
vector<P> intersection(vector<L> &l){
	sort(l.begin(),l.end());
	deque<L>q;
	for(int i=0;i<l.size();i++){
		if(i&&sameDir(l[i],l[i-1]))
			continue;
		while(q.size()>1
			&&!check(q[q.size()-2],q[q.size()-1],l[i]))
				q.pop_back();
		while(q.size()>1
			&&!check(q[1],q[0],l[i]))
				q.pop_front();
		q.push_back(l[i]);
	}
	while(q.size()>2
		&&!check(q[q.size()-2],q[q.size()-1],q[0]))
			q.pop_back();
	while(q.size()>2
		&&!check(q[1],q[0],q[q.size()-1]))
			q.pop_front();
	vector<P>ret;
	for(int i=0;i<q.size();i++)
		ret.push_back(intersect(q[i],q[(i+1)%q.size()]));
	return ret;
}
int n;
P p1,p2;
bool check(double r){
	vector<L>l;
	l.emplace_back(P(-20000,-20000),P(20000,-20000));
	l.emplace_back(P(20000,-20000),P(20000,20000));
	l.emplace_back(P(20000,20000),P(-20000,20000));
	l.emplace_back(P(-20000,20000),P(-20000,-20000));
	for(int i=0;i<n;i++){
		L l0=L(p[i],p[(i+1)%n]);
		
		P v=l0.v().turn90().norm()*r;
		l0.a=l0.a+v;
		l0.b=l0.b+v;
		l.push_back(l0);
	}
	vector<P>p=intersection(l);
	double ans=0;
	
	
	//for(auto pt:p)
	//	pt.print();
	
	P tp1,tp2;
	for(int i=0;i<p.size();i++){
		for(int j=0;j<i;j++){
			double d=(p[i]-p[j]).len();
			if(d>ans){
				ans=d;
				tp1=p[i];
				tp2=p[j];
			}
		}
	}
	if(ans>=2*r)
		p1=tp1,
		p2=tp2;
	return ans>=2*r;
	
}

int main(){
freopen("kabbalah.in","r",stdin);
freopen("kabbalah.out","w",stdout);

	while(scanf("%d",&n)==1&&n){
		for(int i=0;i<n;i++)
			p[i].read();
		
		
		//check(2.8);
		//return 0;
		
		double l=0,r=1e6;
		int TAT=200;
		while(TAT--){
			double mid=(l+r)/2;
			if(check(mid))
				l=mid;
			else
				r=mid;
		}
		
		
		printf("%.10f\n",r);
		printf("%.10f %.10f\n",p1.x,p1.y);	
		printf("%.10f %.10f\n",p2.x,p2.y);	
			
	}
	return 0;
}
