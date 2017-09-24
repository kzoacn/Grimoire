#include<bits/stdc++.h>
using namespace std;

typedef long double LD;

const LD eps=1e-7;
int sgn(LD x){
	return (x>eps)-(x<-eps);
}

struct P{
	LD x,y;
	P(){}
	P(LD _x,LD _y):x(_x),y(_y){}
	LD len(){
		return sqrt(x*x+y*y);
	}
	void read(){
		double tx,ty;
		scanf("%lf%lf",&tx,&ty);
		x=tx;y=ty;
	}
	
};


P operator+(P a,P b){
	return P(a.x+b.x,a.y+b.y);
}
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
LD operator*(P a,P b){
	return a.x*b.y-a.y*b.x;
}
LD operator^(P a,P b){
	return a.x*b.x+a.y*b.y;
}

P operator*(P a,LD b){
	return P(a.x*b,a.y*b);
}
P operator/(P a,LD b){
	return P(a.x/b,a.y/b);
}

struct L{
	P a,b;
	L(){}
	L(P a,P b):a(a),b(b){}
	P v(){return b-a;}
};
P p[2][3];
P dir[2];


LD det(P a,P b,P c){
	return (b-a)*(c-a);
}	

bool onLine(P p,P a,P b){
	return sgn(det(p,a,b))==0;
}

bool onRay(P p,P a,P b){
	return onLine(p,a,b) && sgn((p-a)^(b-a))>=0;
}
bool onSeg(P p,P a,P b){
	return onRay(p,a,b) && onRay(p,b,a);
}
bool onSeg(P p,L l){
	return onSeg(p,l.a,l.b);
}


bool para(L l1,L l2){
	return sgn(l1.v()*l2.v())==0;
}

P intersect(L l1,L l2){
	LD s1=det(l1.a,l1.b,l2.a);
	LD s2=det(l1.a,l1.b,l2.b);
	return (l2.a*s2-l2.b*s1)/(s2-s1);
}

bool is_intersect(L l1,L l2){
	if(para(l1,l2)){
		return onSeg(l1.a,l2) || onSeg(l1.b,l2) || onSeg(l2.a,l1) || onSeg(l2.b,l1);
	}
	P p=intersect(l1,l2);
	return onSeg(p,l1) && onSeg(p,l2);
}

bool onLeft(P p,L l){
	return sgn((l.b-l.a)*(p-l.a))>=0;
}


bool check(P p,P a,P b,P dir){
	if(!sgn(dir.len()))
		return onSeg(p,a,b);
	L l1=L(p,p+dir);
	L l2=L(a,b);
	if(para(l1,l2))
		return onRay(a,p,p+dir) || onRay(b,p,p+dir);
	P pp=intersect(l1,l2);
	return onRay(pp,p,p+dir) && onSeg(pp,a,b);	
}


LD area(P *p){
	LD ans=0;
	for(int i=0;i<3;i++)
		ans+=p[i]*p[(i+1)%3];
	return ans;
}

int main(){
	int T;cin>>T;
	while(T--){
		for(int j=0;j<2;j++){
			for(int i=0;i<3;i++)
				p[j][i].read();
			dir[j].read();
			if(area(p[j])<0)
				reverse(p[j],p[j]+3);
				
			assert(sgn(det(p[j][0],p[j][1],p[j][2])));
		}
		
		bool ok=false;
		
		
		for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			if(is_intersect(L(p[0][i],p[0][(i+1)%3]),L(p[1][j],p[1][(j+1)%3])))
				ok=true;
		
		
		for(int k=0;k<2;k++){
			for(int i=0;i<3;i++){
				bool tmp=true;
				for(int j=0;j<3;j++){
					if(!onLeft(p[k][i],L(p[k^1][j],p[k^1][(j+1)%3])))
						tmp=false;
				}
				ok|=tmp;
			}
		}
		
		for(int k=0;k<2;k++)
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				ok|=check(p[k][i],p[k^1][j],p[k^1][(j+1)%3],dir[k]-dir[k^1]);
			}
		}
		static int TAT=0;
		printf("Case #%d: %s\n",++TAT,ok?"YES":"NO");
	}
	return 0;
}
