#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>

//#define print(x) cout<< #x << " is "<< x <<endl;

using namespace std;
const double eps=1e-9;
int sgn(double x){
	return (x>eps)-(x<-eps);
}
struct P{
	double x,y;
	P(){}
	P(double _x,double _y){x=_x;y=_y;}
	P turn90(){
		double tx=-y,ty=x;
		x=tx;y=ty;
		return *this;
	}
	void print(){
		//printf("%.3f %.3f\n",x,y);
	}
	double len(){
		return sqrt(x*x+y*y);
	}
};
P operator+(P a,P b){
	return P(a.x+b.x,a.y+b.y);
}
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
P operator/(P a,double p){
	return P(a.x/p,a.y/p);
}
P operator*(P a,double p){
	return P(a.x*p,a.y*p);
}
double operator^(P a,P b){
	return a.x*b.x+a.y*b.y;
}
double operator*(P a,P b){
	return a.x*b.y-a.y*b.x;
}
P rot(P p,double rad){
	return P(p.x*cos(rad)-p.y*sin(rad),p.x*sin(rad)+p.y*cos(rad));
}
double det(P a,P b,P c){
	return (b-a)*(c-a);
}
struct L{
	P a,b;
	P v(){
		return b-a;
	}
	L(){}
	void print(){
		//puts("L:");
		//a.print();
		//b.print();
	}
};
P Cross(L l1,L l2){
	double s1=det(l1.a,l1.b,l2.a);
	double s2=det(l1.a,l1.b,l2.b);
	return (l2.b*s1-l2.a*s2)/(s1-s2);
}

bool Para(L a,L b){
	return sgn(a.v()*b.v())==0;
}
P p[4];
L s[4];
L f(L ray,L seg,double n1,double n2){
	P p=Cross(ray,seg);
	
	//printf("p is\n");
	p.print();
	
	P law=seg.v().turn90();
	
	//puts("law is");
	law.print();
	if(sgn(law^ray.v())<=0){
		law.turn90();
		law.turn90();
	}
	law.print();
	//puts("law end");
	
	law=law/law.len();
	
	
	double theta1=acos(fabs(ray.v()^law)/ray.v().len());
	double theta2=asin(sin(theta1)*n1/n2);
	
	//puts("01 02");
	//cout<<theta1<<endl;
	//cout<<theta2<<endl;
	
	L newL;
	newL.a=p;
	if(sgn(rot(law,theta2)*law)*sgn(ray.v()*law)>=0){
		newL.b=p+rot(law,theta2);
	}else{
		newL.b=p+rot(law,-theta2);
	}
	return newL;	
}
bool Onseg(P p,L l){
	return sgn((p-l.a)*l.v())==0
			&&sgn((p-l.b)*l.v())==0
			&&sgn((l.a-p)^(l.b-p))<=0;
}
bool found;
L findseg(L ray){
	found=0;
	L ans;
	double dis=1e30;
	for(int i=1;i<=3;i++){
		if(Para(ray,s[i]))continue;
		P p=Cross(ray,s[i]);
		if(!Onseg(p,s[i]))continue;
		if(sgn((ray.v())^(p-ray.a))<=0)continue;	
		if(dis>(p-ray.a).len()){
			dis=(p-ray.a).len();
			ans=s[i];
		}
		found=1;
	}
	return ans;
}
void CY(L ray){
	if(sgn(ray.v().y)>=0){
		puts("Error");
		return;
	}
	P a=ray.a;
	P b=ray.b;
	if(!sgn(a.x-b.x)){
		printf("%.3f\n",a.x);
		return;
	}
	double k=(a.y-b.y)/(a.x-b.x);
	double B=-k*a.x+a.y;
	printf("%.3f\n",-B/k);
}
void solve(){
	L l1,l2,l3;
	cin>>l1.a.x>>l1.a.y;
	cin>>l1.b.x>>l1.b.y;	
	cin>>p[1].x>>p[1].y;	
	cin>>p[2].x>>p[2].y;	
	cin>>p[3].x>>p[3].y;
	
	s[1].a=p[1];s[1].b=p[2];
	s[2].a=p[2];s[2].b=p[3];
	s[3].a=p[3];s[3].b=p[1];
	
	L s1,s2,s3;
	double n;
	cin>>n;
	
//	n=1/n;
	
	s1=findseg(l1);	
	
	s1.print();

	
	if(!found){
		CY(l1);
		return;
	}
	
	l2=f(l1,s1,1,n);
	
	l2.print();
	
	s2=findseg(l2);
	
	s2.print();
	
	l3=f(l2,s2,n,1);
	
	l3.print();
	
	if(sgn(l3.v().y)>=0){
		puts("Error");
	}else{
		if(!sgn(l3.v().x)){
			printf("%.3f\n",l3.a.x);
		}else{
			CY(l3);
		}
	}
}
int main(){
	int T;scanf("%d",&T);
	while(T--)
		solve();
}


