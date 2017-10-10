#include<bits/stdc++.h>
using namespace std;
const int maxn=1011;
typedef double LD;
const LD eps=1e-8;
int n;
int sgn(LD x){return (x>eps)-(x<-eps);}
struct P{
	LD x,y;
	P(){}
	P(LD _x,LD _y):x(_x),y(_y){}
	LD len(){return sqrt(x*x+y*y);}
	LD len2(){return (x*x+y*y);}
	P norm(){
		return P(x/len(),y/len());
	}
	P turn90(){
		return P(-y,x);
	}
	
	void read(){
		double tx,ty;
		scanf("%lf%lf",&tx,&ty);
		x=tx;y=ty;
	}
	void print(){
		printf("(%.3f,%.3f)\n",(double)x,(double)y);
	}
};
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
LD operator*(P a,P b){
	return a.x*b.y-a.y*b.x;
}
LD operator^(P a,P b){
	return a.x*b.x+a.y*b.y;
}
bool operator==(P a,P b){
	return sgn(a.x-b.x)==0 and sgn(a.y-b.y)==0;
}
struct C{
	P o;
	LD r;
};
LD fix(LD x){return x<0?0:x;}
bool intersect(C a,C b,P &p1,P &p2){
	LD s1=(a.o-b.o).len();
	if(sgn(s1-a.r-b.r)>0 || sgn((s1-fabs(a.r-b.r))<0))
		return false;
	LD s2=(a.r*a.r-b.r*b.r)/s1;
	LD aa=(s1+s2)/2,bb=(s1-s2)/2;
	P o=(b.o-a.o)*(aa/(aa+bb))+a.o;
	P delta=(b.o-a.o).norm().turn90()*sqrt(fix(a.r*a.r-aa*aa));
	p1=o+delta;
	p2=o-delta;
	return true;
}
P p[maxn],d[maxn];
LD V;
C c[maxn];
LD dis(P a,P b){return (b-a).len();}
bool test(P p){
	for(int i=1;i<=n;i++){
		if(sgn(dis(p,c[i].o)-c[i].r)>0)
			return false;
	}
	return true;
}

bool check(LD t){
	for(int i=1;i<=n;i++){
		c[i].o=p[i]+d[i]*t;
		c[i].r=t*V;
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			P p1,p2;
			if(c[i].o==c[j].o)continue;
			if(intersect(c[i],c[j],p1,p2)){
				if(test(p1))
					return true;
				if(test(p2))
					return true;
			}
		}
	}
	return false;
}
double k[maxn];

struct L{
	P a,b;
	P v(){
		return b-a;
	}
};

bool parallel(L l1,L l2){
	return sgn((l1.a-l1.b)*(l2.a-l2.b))==0;
}
double det(P a,P b,P c){
	return (b-a)*(c-a);
}

P intersect(L l1,L l2){
	double s1=det(l1.a,l1.b,l2.a);
	double s2=det(l1.a,l1.b,l2.b);
	return (l2.a*s2-l2.b*s1)/(s2-s1);
}

P project(P p,L l){
	return l.a+l.v()*((p-l.a)^l.v())/l.v().len2();
}
bool onLine(P p,L l){
	return sgn((p-l.a)*(l.b-l.a))==0;
}
bool onRay(P p,L l){
	return onLine(p,l) && sgn((p-l.a)^(l.b-l.a))>=0;
}
bool onSeg(P p,L l){
	return onRay(p,l) && onRay(p,(L){l.b,l.a});
}
P oppo(P p,L l){
	P pp=project(p,l);
	return p+(pp-p)*2;
}
int main(){	
	while(scanf("%d",&n)==1){
		for(int i=0;i<n;i++){
			p[i].read();
			scanf("%lf",&k[i]);
		}
		
		int cnt=0;
		double I=1;
		
		P now=P(0,0);
		P dir;dir.read();
		int last=-1;
		while(I>=1e-4){
		bool ok=0;
			for(int i=0;i<n;i++){
				if(i==last)continue;
			 	L l1,l2;
			 	l1.a=now;l1.b=dir;
			 	l2.a=p[i];l2.b=p[(i+1)%n];
				if(!parallel(l1,l2)){
					P pp=intersect(l1,l2);
					if(onSeg(pp,l2)&&onRay(pp,l1)){
						cnt++;
						ok=1;
						if(pp==l2.a||pp==l2.b){
							I=0;
							break;
						}
						
						P opp=oppo(now,l2);
						
						now=pp;
						dir=now-opp;
						I=I*k[i];
						last=i;
						break;
					}
				}
			}
			
		}
		cout<<cnt<<endl;
	}
	
	return 0;
}

