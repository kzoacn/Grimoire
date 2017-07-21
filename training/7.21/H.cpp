#include<bits/stdc++.h>
using namespace std;
const double eps=1e-9;
int sgn(double x){return (x>eps)-(x<-eps);}
struct P{
	double x,y;
	P(){}
	P(double _x,double _y):x(_x),y(_y){}
	double len(){return sqrt(x*x+y*y);}
	double len2(){return x*x+y*y;}
	void read(){
		scanf("%lf%lf",&x,&y);
	}
	P norm(){
		return P(x/len(),y/len());
	}
};
P operator+(P a,P b){
	return P(a.x+b.x,a.y+b.y);
}
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
double operator*(P a,P b){
	return a.x*b.y-a.y*b.x;
}
double operator^(P a,P b){
	return a.x*b.x+a.y*b.y;
}
P operator*(P a,double b){
	return P(a.x*b,a.y*b);
}
P operator/(P a,double b){
	return P(a.x/b,a.y/b);
}
double dis(P a,P b){
	return (b-a).len();
}
double det(P a,P b,P c){
	return (b-a)*(c-a);
}
double ang(P a,P b){
	return acos((a^b)/a.len()/b.len());
}
struct L{
	P a,b;
	L(){}
	L(P a,P b):a(a),b(b){}
	P v(){return b-a;}
};
P intersect(L l1,L l2){
	double s1=det(l1.a,l1.b,l2.a);
	double s2=det(l1.a,l1.b,l2.b);
	return (l2.a*s2-l2.b*s1)/(s2-s1);
}
bool para(L l1,L l2){
	return sgn(l1.v()*l2.v())==0;
}
struct C{
	P o;
	double r;
	C(){}
	C(P _o,double _r):r(_r),o(_o){}
};
double fix(double x){return sgn(x)?x:0;}
bool intersect(C a,L l,P &p1,P &p2){
	double x=((l.a-a.o)^(l.b-l.a)),	
		y=(l.b-l.a).len2(),
		d=x*x-y*((l.a-a.o).len2()-a.r*a.r);
	if(sgn(d)<0)return false;
	d=max(d,0.0);
	P p=l.a-((l.b-l.a)*(x/y)),delta=(l.b-l.a)*(sqrt(d)/y);
	p1=p+delta;
	p2=p-delta;
	return true;
}

bool near(C c,L l,P &p){
	P p1,p2;
	if(!intersect(c,l,p1,p2))
		return false;
	if(dis(p1,l.a)<dis(p2,l.a))
		p=p1;
	else
		p=p2;
	return true;
}

bool far(C c,L l,P &p){
	P p1,p2;
	if(!intersect(c,l,p1,p2))
		return false;
	if(dis(p1,l.a)<dis(p2,l.a))
		p=p2;
	else
		p=p1;
	return true;
}

double W,la,h,r;
C c[4];
P hl,hr;
void bomb(){
	puts("impossible");
	exit(0);
}
P project(P p,L l){
	return l.a+l.v()*((p-l.a)^l.v())/l.v().len2();
}
P reflect(P p,L l){
	P pro=project(p,l);
	P np=p+(pro-p)*2;
	return np;
}
int main(){
	scanf("%lf%lf",&W,&la);
	scanf("%lf",&r);
	c[1].o.read();c[1].r=r;
	c[2].o.read();c[2].r=r;
	c[3].o.read();c[3].r=r;
	scanf("%lf",&h);	
	
	if(!(c[2].o.x<c[1].o.x && c[1].o.x<c[3].o.x))
		bomb();
	if(!(c[2].o.y>=c[1].o.x && c[3].o.y>=c[1].o.y))
		bomb();
	
	
	
	hl=P(0,la);
	hr=P(W,la);
	
	
	L lr3=L(hr,c[3].o);
	P p3;
	
	if(!far(c[3],lr3,p3))bomb();
	
	p3=p3+(p3-c[3].o);
	
	L l31=L(p3,c[1].o);
	P p1,p0;
	if(!far(c[1],l31,p1))bomb();

	p0=p1+(p1-c[1].o);

	L ll2=L(hl,c[2].o);
	P p2;
	if(!far(c[2],ll2,p2))bomb();
	
	p2=p2+(p2-c[2].o);
	
	P pp=reflect(p2,L(p0,c[1].o));
	
	L l=L(pp,p0);
	
	L line=L(P(0,h),P(W,h));

	if(para(l,line))bomb();
	P p=intersect(l,line);
	double d=dis(p,P(0,h));
	
	if(sgn(d-r)>=0&&sgn(d-(W-r))<=0&&sgn((p0-pp)^(c[1].o-p0))>=0){
		double theta;
		
		theta=ang(l.v(),line.v());
		
		double pi=acos(-1);
		printf("%.2f %.2f\n",d,theta*180/pi);
	}else bomb();
	
	return 0;
}
