#include<bits/stdc++.h>
using namespace std;
const int maxn=111;
const double eps=1e-9;
int sgn(double x){return (x>eps)-(x<-eps);}
struct P{
	double x,y;
	P(){}
	P(double _x,double _y):x(_x),y(_y){}
	double len(){return sqrt(x*x+y*y);}
	P norm(){
		return P(x/len(),y/len());
	}
	P turn90(){
		return P(-y,x);
	}
	
	void read(){
		scanf("%lf%lf",&x,&y);
	}
	void print(){
		printf("(%.3f,%.3f)\n",x,y);
	}
};
P operator+(P a,P b){
	return P(a.x+b.x,a.y+b.y);
}
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
P operator*(P a,double b){
	return P(a.x*b,a.y*b);
}
double operator*(P a,P b){
	return a.x*b.y-a.y*b.x;
}
double operator^(P a,P b){
	return a.x*b.x+a.y*b.y;
}
bool operator==(P a,P b){
	return sgn(a.x-b.x)==0 and sgn(a.y-b.y)==0;
}
struct C{
	P o;
	double r;
};
double fix(double x){return x<0?0:x;}
bool intersect(C a,C b,P &p1,P &p2){
	double s1=(a.o-b.o).len();
	if(sgn(s1-a.r-b.r)>0 || sgn((s1-fabs(a.r-b.r))<0))
		return false;
	double s2=(a.r*a.r-b.r*b.r)/s1;
	double aa=(s1+s2)/2,bb=(s1-s2)/2;
	P o=(b.o-a.o)*(aa/(aa+bb))+a.o;
	P delta=(b.o-a.o).norm().turn90()*sqrt(fix(a.r*a.r-aa*aa));
	p1=o+delta;
	p2=o-delta;
	return true;
}
P p[maxn],d[maxn];
int n;
double V;
C c[maxn];
double dis(P a,P b){return (b-a).len();}
bool test(P p){
	for(int i=1;i<=n;i++){
		if(sgn(dis(p,c[i].o)-c[i].r)>0)
			return false;
	}
	return true;
}

bool check(double t){
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

int main(){
	while(scanf("%d%lf",&n,&V)==2){
		for(int i=1;i<=n;i++){
			p[i].read();
			d[i].read();
			d[i]=d[i].norm();
			double v;scanf("%lf",&v);
			d[i]=d[i]*v;
		}
		
		double t=1.0/3;
		
		
		P a=(p[1]+d[1]*t);
		P b=(p[2]+d[2]*t);
		
		
		double l=0,r=2000;
		
		while(r-l>1e-6){
			double mid=(l+r)/2;
			if(check(mid))
				r=mid;
			else
				l=mid;
		}
		printf("%.4f\n",l);
	}
	
	
	
	return 0;
}

/*
(2.000,0.000)
(1.000,0.000)
(2.333,0.000)
(0.316,0.105)
2.01986
0.666667
0.7158
(0.000,0.000)
(0.000,1.000)
(0.000,0.333)
(0.000,1.667)
1.33333
0.666667
0.5000

*/
