#include<bits/stdc++.h>
using namespace std;
const double eps=1e-9;

int sgn(double x){
	return (x>eps)-(x<-eps);
}

struct P{
	double x,y;
	P(){}
	P(double _x,double _y):x(_x),y(_y){}
	double len(){return sqrt(x*x+y*y);}
	double len2(){return (x*x+y*y);}
	void read(){scanf("%lf%lf",&x,&y);}
	
	void print(){
		printf("(%.3f,%.3f)\n",x,y);
	}
}p[666];
P operator+(P a,P b){
	return P(a.x+b.x,a.y+b.y);
}
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
double dis(P a,P b){return (b-a).len();}
double operator^(P a,P b){
	return a.x*b.x+a.y*b.y;
}
double operator*(P a,P b){
	return a.x*b.y-a.y*b.x;
}
P operator*(P a,double b){
	return P(a.x*b,a.y*b);
}
P operator/(P a,double b){
	return P(a.x/b,a.y/b);
}
double mysqrt(double x){
	if(x<=0)return 0;
	return sqrt(x);
}
double myacos(double x){
	x=min(x,1.0);
	x=max(x,-1.0);
	return acos(x);
}
double getSectionArea(P a,P b,double r){
	double c=(2*r*r-(a-b).len2())/(2*r*r);
	double alpha=myacos(c);
	return r*r*alpha/2;
}
pair<double,double>getSolution(double a,double b,double c){
	double delta=b*b-4*a*c;
	if(sgn(delta)<0)return make_pair(0,0);
	return make_pair((-b-mysqrt(delta))/(2*a),(-b+mysqrt(delta))/(2*a));
}
pair<P,P> getIntersection(P a,P b,double r){
	P d=b-a;
	double A=d^d;
	double B=2*(d^a);
	double C=(a^a)-r*r;
	pair<double,double>s=getSolution(A,B,C);
	return make_pair(a+d*s.first,a+d*s.second);
		
}
double getPointDist(P a,P b){
	P d=b-a;
	int sA=sgn(a^d),sB=sgn(b^d);
	if(sA*sB<=0)return (a*b)/dis(a,b);
	return min(a.len(),b.len());
}
double getArea(P a,P b,double r){
	double dA=a^a,dB=b^b,dC=getPointDist(a,b),ans=0;
	if(sgn(dA-r*r)<=0&&sgn(dB-r*r)<=0)
		return (a*b)/2;	
	P tA=a/a.len()*r;
	P tB=b/b.len()*r;
	if(sgn(dC-r)>0)
		return getSectionArea(tA,tB,r);
	pair<P,P>ret=getIntersection(a,b,r);
	if(sgn(dA-r*r)>0&&sgn(dB-r*r)>0){
		ans+=getSectionArea(tA,ret.first,r);
		ans+=(ret.first*ret.second)/2;
		ans+=getSectionArea(ret.second,tB,r);
		return ans;
	}
	if(sgn(dA-r*r)>0)
		return (ret.first*b)/2+getSectionArea(tA,ret.first,r);
	return (a*ret.second)/2+getSectionArea(ret.second,tB,r);
}
double getArea(int n,P *p,P c,double r){
	double ret=0;
	for(int i=0;i<n;i++)
		ret+=p[i]*p[(i+1)%n];
	if(ret<0)reverse(p,p+n);
	double res=0;
	ret/=2;
	for(int i=0;i<n;i++){
		int sign=sgn((p[i]-c)*(p[(i+1)%n]-c));
		if(sign>0)
			res+=getArea(p[i]-c,p[(i+1)%n]-c,r);
		else
			res-=getArea(p[(i+1)%n]-c,p[i]-c,r);
	}
	return fabs(res);
}
int n;
double k;
int main(){
	while(scanf("%d%lf",&n,&k)==2){
		for(int i=0;i<n;i++)
			p[i].read();
		P A,B;
		A.read();
		B.read();
		static int T=0;
		
		P c;double r;
		P near,far;
		near=B+(A-B)*(k/(1+k));
		far=B+(B-A)*(k/(1-k));
		
		c=(near+far)/2;
		r=(near-far).len()/2;
		
		double ans=getArea(n,p,c,r);
		printf("Case %d: %.10f\n",++T,ans);
	}
	return 0;
}
