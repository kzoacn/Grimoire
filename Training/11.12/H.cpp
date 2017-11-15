#include<bits/stdc++.h>
using namespace std;
typedef long double LD;
const LD eps=1e-10;
const int maxn=233;
int sgn(LD x){return (x>eps)-(x<-eps);}

struct P{
	LD x,y;
	P(){}
	P(LD _x,LD _y):x(_x),y(_y){}
	LD len(){return sqrtl(x*x+y*y);}
	void read(){
		double tx,ty;
		scanf("%lf%lf",&tx,&ty);
		x=tx;y=ty;
	}
	
	P norm(){
		return P(x/len(),y/len());
	}
	P turn90(){
		return P(-y,x);
	}
	
}pA,pB,p[maxn];
bool operator==(P a,P b){
	return sgn(a.x-b.x)==0 && sgn(a.y-b.y)==0;
}

P operator+(P a,P b){
	return P(a.x+b.x,a.y+b.y);
}

P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
P operator*(P a,LD b){
	return P(a.x*b,a.y*b);
}
P operator/(P a,LD b){
	return P(a.x/b,a.y/b);
}
LD dis(P a,P b){return (b-a).len();}


double operator^(P a,P b){
	return a.x*b.x + a.y*b.y;
}
double operator*(P a,P b){
	return a.x*b.y - a.y*b.x;
}


int n;

LD fix(LD x){return x<0?0:x;}

bool intersect(P a,P b,LD r,P &p1,P &p2){
	LD s1=(a-b).len();
	if(sgn(s1-r-r)>0 || sgn(s1-fabs(r-r))<0)return false;
	LD s2=(r*r-r*r)/s1;
	LD aa=(s1+s2)/2,bb=(s1-s2)/2;
	P o=(b-a)*(aa/(aa+bb))+a;
	P delta=(b-a).norm().turn90()*sqrtl(fix(r*r-aa*aa));
	p1=o+delta;
	p2=o-delta;
	return true;
}
bool intersectX(P a,LD r,LD x,P &p1,P &p2){
	if(sgn(fabs(x-a.x)-r)>0)return false;
	LD d=r*r-(x-a.x)*(x-a.x);
	d=sqrtl(fix(d));
	p1.x=x;p1.y=d+a.y;
	p2.x=x;p2.y=-d+a.y;
	return true;
}


bool intersectY(P a,LD r,LD y,P &p1,P &p2){
	if(sgn(fabs(y-a.y)-r)>0)return false;
	LD d=r*r-(y-a.y)*(y-a.y);
	d=sqrtl(fix(d));
	p1.y=y;p1.x=d+a.x;
	p2.y=y;p2.x=-d+a.x;
	return true;
}

bool check(P p,long long r){
	if(sgn(p.x-pA.x)<0||sgn(p.x-pB.x)>0)return false;
	if(sgn(p.y-pA.y)<0||sgn(p.y-pB.y)>0)return false;
	for(int i=1;i<=n;i++){
		LD d=dis(p,::p[i]);
		if(sgn(d-r)<0)
			return false;
	}
	return true;
}

bool check(long long r){

	static P pt[int(1e5+5)];
	int sz=0;

	pt[++sz]=P(pA.x,pA.y);
	pt[++sz]=P(pA.x,pB.y);
	pt[++sz]=P(pB.x,pA.y);
	pt[++sz]=P(pB.x,pB.y);
	P p1,p2;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(p[i]==p[j])continue;
			if(intersect(p[i],p[j],r,p1,p2)){
				pt[++sz]=p1;
				pt[++sz]=p2;
			}
		}
		if(intersectX(p[i],r,pA.x,p1,p2)){
			pt[++sz]=p1;
			pt[++sz]=p2;
		}
		if(intersectX(p[i],r,pB.x,p1,p2)){
			pt[++sz]=p1;
			pt[++sz]=p2;
		}
		
		if(intersectY(p[i],r,pA.y,p1,p2)){
			pt[++sz]=p1;
			pt[++sz]=p2;
		}
		if(intersectY(p[i],r,pB.y,p1,p2)){
			pt[++sz]=p1;
			pt[++sz]=p2;
		}
		
	}

	for(int i=1;i<=sz;i++)if(check(pt[i],r))
		return false;
	return true;
}

int main(){
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		pA.read();
		pB.read();
		scanf("%d",&n);

		for(int i=1;i<=n;i++){
			p[i].read();
		}
		long long l=1,r=1e16;
		while(l<r){
			long long mid=(l+r)/2;
			if(check(mid))	
				r=mid;
			else
				l=mid+1;
		}
		printf("Case #%d: %lld\n",t,l);
	}
	return 0;
}
