#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<deque>
#include<cstring>
#include<vector>
using namespace std;
const double eps=1e-10;
int sgn(double x){return (x>eps)-(x<-eps);}
int sgn(double a,double b){return sgn(a-b);}
double sqr(double x){return x*x;}
struct P{
	double x,y;
	P(){}
	P(double x,double y):x(x),y(y){}
	double len2(){
		return sqr(x)+sqr(y);
	}
	double len(){
		return sqrt(len2());
	}
	void print(){
		printf("(%.3f,%.3f)\n",x,y);
	}
	P turn90(){return P(-y,x);}
	P norm(){return P(x/len(),y/len());}
};
bool operator==(P a,P b){
	return !sgn(a.x-b.x) and !sgn(a.y-b.y);
}
/*bool operator<(P a,P b){
	return sgn(a.x-b.x) ? a.x<b.x : a.y<b.y;
}*/
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
double dis(P a,P b){
	return (b-a).len();
}
double Area(vector<P>poly){
	double ans=0;
	for(int i=1;i<poly.size();i++)
		ans+=(poly[i]-poly[0])*(poly[(i+1)%poly.size()]-poly[0]);
	return fabs(ans)/2;
}
struct L{
	P a,b;
	L(){}
	L(P a,P b):a(a),b(b){}
	P v(){return b-a;}
};
bool onLine(P p,L l){
	return sgn((l.a-p)*(l.b-p))==0;
}
bool onSeg(P p,L s){
	return onLine(p,s) and sgn((s.b-s.a)^(p-s.a))>=0 and sgn((s.a-s.b)^(p-s.b))>=0;
}
bool parallel(L l1,L l2){
	return sgn(l1.v()*l2.v())==0;
}
P intersect(L l1,L l2){
	double s1=det(l1.a,l1.b,l2.a);
	double s2=det(l1.a,l1.b,l2.b);
	return (l2.a*s2-l2.b*s1)/(s2-s1);
}
P project(P p,L l){
	return l.a+l.v()*((p-l.a)^l.v())/l.v().len2();
}
double dis(P p,L l){
	return fabs((p-l.a)*l.v())/l.v().len();
}

