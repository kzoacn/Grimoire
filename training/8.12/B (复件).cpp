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
	return dis(d,p)+dis(d,q);
}
void solve(){
	scanf("%lf",&r);
	p.read();q.read();
	P O(0,0);
	double d=dis(p,O);
	if(!sgn(d)){
		printf("%.8f\n",r*2);
		return ;
	}
	double t1=atan2(p.y,p.x);
	double t2=atan2(q.y,q.x);
	
	if(t1>t2)swap(t1,t2);
	if(fabs(t1-t2)>pi){
		t1+=2*pi;
		if(t1>t2)swap(t1,t2);
	}
	double l=t1,r=(t1+t2)/2;
	int TAT=80;
	while(1){
		double mid1=l+(r-l)*0.495;
		double mid2=r-(r-l)*0.495;
		double res1=calc(mid1);
		double res2=calc(mid2);
		if(fabs(res1-res2)<1e-9)break;
		if(res1>res2)
			l=mid1;
		else
			r=mid2;
	}
	double ans=calc((l+r)/2);
	printf("%.8f\n",ans);
}

int main(){
	int T;cin>>T;
	while(T--)
		solve();

	return 0;
}
