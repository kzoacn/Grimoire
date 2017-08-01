#include<bits/stdc++.h>
#define deb(x) cerr<< #x <<" = "<<x<<endl
using namespace std;
const double eps=1e-11;
int sgn(double x){return (x>eps)-(x<-eps);}
double sqr(double x){return x*x;}
struct P{
	double x,y;
	P(){}
	P(double _x,double _y):x(_x),y(_y){}
	P turn90(){
		return P(-y,x);
	}
	double len(){
		return sqrt(x*x+y*y);
	}
	P norm(){
		return P(x/len(),y/len());
	}
	void read(){
		scanf("%lf%lf",&x,&y);
	}
	P rot(double rad){
		return P(x*cos(rad)-y*sin(rad),x*sin(rad)-y*cos(rad));
	}
	void print(){
		fprintf(stderr,"(%.5f,%.5f)\n",x,y);
	}
};
bool operator==(P a,P b){
	return !sgn(a.x-b.x) && !sgn(a.y-b.y);
}
bool operator!=(P a,P b){
	return !(a==b);
}
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
double det(P a,P b,P c){
	return (b-a)*(c-a);
}
double dis(P a,P b){
	return (b-a).len();
}
struct C{
	P o;
	double r;
	C(){}
}c[12][12][2];
C cir[2222];

bool operator==(C a,C b){
	return a.o==b.o && !sgn(a.r-b.r);
}
bool operator!=(C a,C b){
	return !(a==b);
}
bool onLeft(P p,P a,P b){
	return sgn((p-a)*(b-a))<=0;
}
bool onRight(P p,P a,P b){
	return sgn((p-a)*(b-a))>=0;
}

double fix(double x){return sgn(x)==1?x:0;}
bool intersect(C a,C b,P &p1,P &p2){
	double s1=(a.o-b.o).len();
	if(sgn(s1-a.r-b.r)>0||sgn(s1-fabs(a.r-b.r))<0)return false;
	double s2=(a.r*a.r-b.r*b.r)/s1;
	double aa=(s1+s2)/2,bb=(s1-s2)/2;
	P o=(b.o-a.o)*(aa/(aa+bb))+a.o;
	P delta=(b.o-a.o).norm().turn90()*sqrt(fix(a.r*a.r-aa*aa));
	//if(a.r*a.r-aa*aa<eps)cerr<<a.r*a.r-aa*aa<<endl;
	p1=o+delta;p2=o-delta;
	return true;
}
P p[11];
int n;
P ansP;
double angDot(P p,P a,P b){
	double dot=(a-p)^(b-p);
	return dot/(a-p).len()/(b-p).len();
}
C get(P a,P b,double theta,int dir){
	double d=dis(a,b);
	double r=d/2/sin(theta);
	double h=sqrt(fix(r*r-(d/2)*(d/2)));
	P m=(a+b)/2;
	C c;
	if(dir==1)
		c.o=m+(b-a).turn90().norm()*h;
	else
		c.o=m+(b-a).turn90().turn90().turn90().norm()*h;
	c.r=r;
	return c;
}
int sz=0;
bool inC(P p,C c,bool strict){
	double d=dis(p,c.o);
	if(strict)	
		return sgn(d-c.r)<0;
	else
		return sgn(d-c.r)<=0;
}
bool test(P pt,double theta){
	for(int i=1;i<=n;i++){
		if(sgn(dis(pt,p[i])-1)<0)
			return false;
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(angDot(pt,p[i],p[j])>1e-8+cos(theta))
				return false;
		}
	}
	return true;
}
const double pi=acos(-1);
bool check(P pt,double theta){

	return test(pt,theta);
	
	int QAQ=3;
	for(int i=0;i<=QAQ;i++){
		if(test(pt+P(1e-11,0).rot(2*pi/QAQ*i),theta))
			return true;
	}
	return false;
}

bool check(double theta){
	sz=0;
	for(int i=1;i<=n;i++)
	for(int j=i+1;j<=n;j++)if(p[i]!=p[j]){
		c[i][j][0]=get(p[i],p[j],theta,1);
		c[i][j][1]=get(p[i],p[j],theta,-1);
//		c[i][j][0].r+=eps;
//		c[i][j][1].r+=eps;
		cir[++sz]=c[i][j][0];
		cir[++sz]=c[i][j][1];
	}
	for(int i=1;i<=n;i++){
		++sz;
		cir[sz].o=p[i];
		cir[sz].r=1;
	}
	
	for(int i=1;i<=sz;i++){
		for(int j=i+1;j<=sz;j++){
			if(cir[i]!=cir[j]){
				P p1,p2;
				if(intersect(cir[i],cir[j],p1,p2)){
					if(check(p1,theta)){
						ansP=p1;
						/*if(isnan(p1.x)){
						assert(false);
							cir[i].o.print();
							deb(cir[i].r);
							cir[j].o.print();
							deb(cir[j].r);
						}*/
						return true;
					}
					if(check(p2,theta)){
						ansP=p2;
						return true;
					}
				}
			}
		}
	}
	return false;	
}
int main(){
	ansP.x=ansP.y=10000;
	assert(scanf("%d",&n)==1);
	for(int i=1;i<=n;i++)
		p[i].read();
		
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++)
			if(p[i]==p[j]){
				printf("%.10f %.10f\n",ansP.x,ansP.y);
				return 0;
			}
	}
	
/*	check(0.7853981634);
	cerr<<"ans="<<endl;
	cerr<<ansP.x<<" "<<ansP.y<<endl;
	return 0;
*/	double l=0,r=acos(-1);
	int TAT=100;
	while(TAT--){
		double mid=(l+r)/2;
		if(check(mid))
			l=mid;
		else
			r=mid;
	}
//	cerr<<l<<endl;
//	cerr<<ang(ansP,)
	
	printf("%.10f %.10f\n",ansP.x,ansP.y);
	return 0;
}
