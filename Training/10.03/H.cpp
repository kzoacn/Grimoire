#include<bits/stdc++.h>
using namespace std;
const long double eps=1e-9;

int sgn(long double x){
	return (x>eps)-(x<-eps);
}

struct P{
	long double x,y;
	P(){}
	P(long double _x,long double _y):x(_x),y(_y){}
	long double len(){return sqrt(x*x+y*y);}
	long double len2(){return (x*x+y*y);}
	void read(){
		double tx, ty;
		scanf("%lf%lf",&tx,&ty);
		x = tx;
		y = ty;
	}
	
	void print(){
		printf("(%.3f,%.3f)\n",(double)x,(double)y);
	}
}p[666];
P operator+(P a,P b){
	return P(a.x+b.x,a.y+b.y);
}
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
long double dis(P a,P b){return (b-a).len();}
long double operator^(P a,P b){
	return a.x*b.x+a.y*b.y;
}
long double operator*(P a,P b){
	return a.x*b.y-a.y*b.x;
}
P operator*(P a,long double b){
	return P(a.x*b,a.y*b);
}
P operator/(P a,long double b){
	return P(a.x/b,a.y/b);
}
long double mysqrt(long double x){
	if(x<=0)return 0;
	return sqrt(x);
}
long double myacos(long double x){
	x=min(x,(long double)1.0);
	x=max(x,(long double)-1.0);
	return acos(x);
}
long double getSectionArea(P a,P b,long double r){
	long double c=(2*r*r-(a-b).len2())/(2*r*r);
	long double alpha=myacos(c);
	return r*r*alpha/2;
}
pair<long double,long double>getSolution(long double a,long double b,long double c){
	long double delta=b*b-4*a*c;
	if(sgn(delta)<0)return make_pair(0,0);
	return make_pair((-b-mysqrt(delta))/(2*a),(-b+mysqrt(delta))/(2*a));
}
pair<P,P> getIntersection(P a,P b,long double r){
	P d=b-a;
	long double A=d^d;
	long double B=2*(d^a);
	long double C=(a^a)-r*r;
	pair<long double,long double>s=getSolution(A,B,C);
	return make_pair(a+d*s.first,a+d*s.second);
		
}
long double getPointDist(P a,P b){
	P d=b-a;
	int sA=sgn(a^d),sB=sgn(b^d);
	if(sA*sB<=0)return (a*b)/dis(a,b);
	return min(a.len(),b.len());
}
long double getArea(P a,P b,long double r){
	long double dA=a^a,dB=b^b,dC=getPointDist(a,b),ans=0;
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
long double getArea(int n,P *p,P c,long double r){
	long double ret=0;
	for(int i=0;i<n;i++)
		ret+=p[i]*p[(i+1)%n];
	if(ret<0)reverse(p,p+n);
	long double res=0;
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

struct L{
	P a,b;
};
struct Cir{
	P o;
	long double r;
};
long double fix(long double x){return sgn(x)?x:0;}
bool intsersect(Cir a,L l,P &p1,P &p2){
	long double x=((l.a-a.o)^(l.b-l.a)),
		y=(l.b-l.a).len2(),
		d=x*x-y*((l.a-a.o).len2()-a.r*a.r);
	if(sgn(d)<0)return false;
	d=max(d,(long double)0.0);
	P p=l.a-((l.b-l.a)*(x/y)),delta=(l.b-l.a)*(mysqrt(d)/y);
	p1=p+delta;
	p2=p-delta;
	return true;
}


int n;
long double k;
int main(){
	long double v0,v1,d,T;
	double a, b, c, cc;
	//while(scanf("%lf%lf%lf%lf",&v0,&v1,&d,&T)==4){
	while(scanf("%lf%lf%lf%lf",&a,&b,&c,&cc)==4){
		v0 = a;
		v1 = b;
		d = c;
		T = cc;
		static int TAT=0;
	
		P A,B,C;
		long double r=v0*T;
		long double theta=asin(v0/v1);
		B.x=r*v0 / v1;
		B.y=d-r*sqrt(v1 * v1 - v0 * v0) / v1;
		long double k=v0 / sqrt(v1 * v1 - v0 * v0);
		
//		cerr<<(B.y-d)/(B.x-x)<<endl;
		
		if(sgn(r-d)<=0||sgn(B.y)>=0){
			printf("Case %d: %.10f\n",++TAT,(double)(acos(-1)*r*r));
			continue;
		}
		
		//y=k(x-B.x)+B.y
		//0=kx-k*B.x+B.y
		A.x=B.x-B.y/k;
		A.y=0;
		{
			L ll;
			ll.a=A;
			ll.b=P(B.x,-B.y);
			
			
			//cerr<<"lla";ll.a.print();
			
			//cerr<<"llb";ll.b.print();
			
			Cir cir;
			cir.r=r;
			cir.o=P(0,d);
			
			P p1,p2;
			if(intsersect(cir,ll,p1,p2)){
				if(p1.x<p2.x)swap(p1,p2);
				C=p1;
			}else {
				assert(0);
			}
		}
		
		long double ans=0;
		P p[3];
		p[0]=A;
		p[1]=B;
		p[2]=C;
		
		
		//A.print();
		//B.print();
		//C.print();
		ans=getArea(3,p,P(0,d),r);
		//cerr<<"ins "<<ans<<endl;
		ans=fabs((C-A)*(B-A))/2-ans;
		
		//cerr<<"area tri "<<fabs((C-A)*(B-A))/2<<endl;
		//cerr<<"area cir "<<acos(-1)*r*r<<endl;
		ans=ans*2+acos(-1)*r*r;
		
		printf("Case %d: %.10f\n",++TAT,(double)ans);
	}
	return 0;
}
