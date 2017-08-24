#include<bits/stdc++.h>
const double pi=acos(-1);
using namespace std;
const double eps=1e-10;
int sgn(double x){return (x>eps)-(x<-eps);}
struct P{
	double x,y;
	P(){}
	P(double _x,double _y):x(_x),y(_y){}
	double len(){return sqrt(x*x+y*y);}
	void print(){
		printf("%.4f %.4f\n",x,y);
	}
	double len2(){
		return (x*x+y*y);
	}
	void read(){
		scanf("%lf%lf",&x,&y);
	}
	P rot(double rad){
		return P(x*cos(rad)-y*sin(rad),x*sin(rad)+y*cos(rad));
	}
};
P operator+(P a,P b){
	return P(a.x+b.x,a.y+b.y);
}
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
double dis(P a,P b){
	return (b-a).len();
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


double ang(P a,P b){
	return acos((a^b)/a.len()/b.len());
}
double ang(P a,P b,P c){//<ABC
	return ang((a-b),(c-b));
}
P A,B,C;

bool check(P p){

	/*if(p.x>0){
		if(p.y<0||p.y>10-p.x)
			return false;
	}
	if(p.x>0){
		if(p.y<0||p.y>10+p.x)
			return false;
	}*/

	P M=(B+C)/2;
	
	double ang1=ang(M,p,B)+ang(A,p,C);
	double ang2=ang(M,p,C)+ang(B,p,A);

	return fabs(ang1-ang2)<1e-4;
}

int test(){



	A=P(0,3);
	B=P(-7,0);
	C=P(7,0);
	
	for(double x=-C.x;x<=C.x;x+=0.01){
		for(double y=-A.y;y<=A.y;y+=0.01){
			if(fabs(x)<0.01)continue;
			if(check(P(x,y)))
				printf("(%.5f,%.5f)\n",x,y);
		}
	}
	return 0;
}
double mysqrt(double x){
	if(x<=0)return 0;
	return sqrt(x);
}
struct Cir{
	P o;
	double r;
	Cir(){}
	double ang(P p){
		return atan2(p.y-o.y,p.x-o.x);
	}
	P at(double rad){
		return P(r,0).rot(rad)+o;
	}
};
bool onLine(P p,P a,P b){
	return sgn((p-a)*(p-b))==0;
}
bool onSeg(P p,P a,P b){
	return onLine(p,a,b) and sgn((a-p)^(b-p))<=0;
}

bool intersect(Cir c,P a,P b,P &p1,P &p2){
	double x=((a-c.o)^(b-a)),
			y=(b-a).len2(),
			d=x*x-y*((a-c.o).len2()-c.r*c.r);
	if(sgn(d)<0)return false;
	d=max(d,0.0);
	P p=a-((b-a)*(x/y)),delta=(b-a)*(sqrt(d)/y);
	p1=p+delta;
	p2=p-delta;
	return true;
}
bool onLeft(P p,P a,P b){
	return sgn((p-a)*(b-a))<=0;
}
bool inTri(P p,P a,P b,P c){
	if(onLeft(p,A,B)&&onLeft(p,B,C)&&onLeft(p,C,A))
		return true;
	return false;
}
double solve(){
	A.read();
	B.read();
	C.read();
	double d=dis(A,B);
	double a=dis(B,C)/2;
	double b=mysqrt(d*d-a*a);
	double r=d;
	Cir c;
	c.r=r*a/b;
	c.o=P(0,-a*a/b);
	
	A=P(0,b);
	B=P(-a,0);
	C=P(a,0);
/*	
	A.print();
	B.print();
	C.print();
	c.o.print();
	cerr<<c.r<<endl;
*/
	double ans=b;
	vector<double>pt;
	P p1,p2;
	if(intersect(c,A,B,p1,p2)){
		if(onSeg(p1,A,B))
			pt.push_back(c.ang(p1));
		if(onSeg(p2,A,B))	
			pt.push_back(c.ang(p2));
	}
	if(intersect(c,B,C,p1,p2)){
		if(onSeg(p1,B,C))
			pt.push_back(c.ang(p1));
		if(onSeg(p2,B,C))	
			pt.push_back(c.ang(p2));
	}
	if(intersect(c,A,C,p1,p2)){
		if(onSeg(p1,A,C))
			pt.push_back(c.ang(p1));
		if(onSeg(p2,A,C))	
			pt.push_back(c.ang(p2));
	}
	
	pt.push_back(0);
	pt.push_back(pi);
	
	sort(pt.begin(),pt.end());
	
	for(int i=0;i<pt.size();i++){
		double t1=pt[i],t2=pt[(i+1)%pt.size()];
		if(t1>t2)t2+=2*pi;
		P p=c.at((t1+t2)/2);
		if(inTri(p,A,B,C))
			ans+=r*(t2-t1);
	}
	return ans;
	
	
}
int main(){
//test();
//return 0;

	int T;cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case #%d: %.4f\n",t,solve());
	}
	return 0;
}

