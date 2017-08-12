#include<bits/stdc++.h>
using namespace std;
const double eps=1e-9;
const double pi=acos(-1);
int sgn(double x){
	return (x>eps)-(x<-eps);
}
struct P{
	double x,y;
	P(){}
	P(double _x,double _y):x(_x),y(_y){}
	void read(){
		scanf("%lf%lf",&x,&y);
	}
	P rot(double rad){
		return P(x*cos(rad)-y*sin(rad),x*sin(rad)+y*cos(rad));
	}
	double len(){
		return sqrt(x*x+y*y);
	}
}p,q;
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
double dis(P a,P b){
	return (b-a).len();
}
double r;

double calc(double t){
	P d=P(r,0).rot(t);
//printf("x and y: %.10f %.10f\n", ()d.x, (double)d.y);
	return dis(d,p)+dis(d,q);
}

double sqr(double x){return x*x;}
double mysqrt(double x){
	if(sgn(x)<=0)return 0;
	return sqrt(x);
}

bool solve(double A,double B,double C,double &x1,double &x2){
	double delta=B*B-4*A*C;
	if(sgn(delta)<0)return false;
	
	x1=(-B+mysqrt(delta))/2/A;
	x2=(-B-mysqrt(delta))/2/A;
	
	return true;
}
double myasin(double x){
	if(sgn(x-1)>=0)return asin(1);
	if(sgn(x+1)<=0)return asin(-1);
	return asin(x);
}

void solve(){
	scanf("%lf",&r);
	p.read();q.read();
	P O(0,0);
	double d=dis(p,O);
	if(!sgn(d)){
		printf("%.10f\n",r*2);
		return ;
	}
	
	double l=dis(p,q);
	double a=l/2;
	double b=mysqrt(sqr(d)-sqr(l/2));
	q=P(a,b);	
	p=P(-a,b);	
	
	double x1,x2,A,B,C;
	
	A=(sqr(a)+sqr(b))*r;
	B=-b*(sqr(a)+sqr(b)+sqr(r));
	C=r*sqr(b);
	
	double ans=calc(pi/2);
	if(solve(A,B,C,x1,x2)){
	//printf("%.10f %.10f\n", (double)x1, (double)x2);
		ans=min(ans,calc(myasin(x1)));	
		ans=min(ans,calc(myasin(x2)));	
	}
	
	
	printf("%.10f\n",ans);
}

int main(){
	int T;cin>>T;
	while(T--)
		solve();

	return 0;
}
