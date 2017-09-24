#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;
typedef long double LD;
const LD eps=1e-6;
const int maxn=110;
LD sqr(LD x){return x*x;}
int sgn(LD x){
	return (x>eps)-(x<-eps);
}
struct P{
	LD x,y;
	P(){}
	P(LD x,LD y):x(x),y(y){}
	LD len(){
		return sqrt(sqr(x)+sqr(y));
	}
	P turn90(){
		return P(y,-x);
	}
	void read(){
		double tx,ty;
		scanf("%lf%lf",&tx,&ty);
		x=tx;
		y=ty;
	}
};
bool operator==(P a,P b){
	return !sgn(a.x-b.x)&&!sgn(a.y-b.y);
}
bool operator<(P a,P b){
	return sgn(a.x-b.x)?a.x<b.x:a.y<b.y;
}
P operator+(P a,P b){
	return P(a.x+b.x,a.y+b.y);
}
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
LD operator^(P a,P b){
	return a.x*b.x+a.y*b.y;
}
LD operator*(P a,P b){
	return a.x*b.y-a.y*b.x;
}
P operator*(P a,LD p){
	return P(a.x*p,a.y*p);
}
P operator/(P a,LD p){
	return P(a.x/p,a.y/p);
}
P rot(P p,double rad){
	return P(p.x*cos(rad)-p.y*sin(rad),p.x*sin(rad)+p.y*cos(rad));
}
LD det(P a,P b,P c){
	return (b-a)*(c-a);
}
P intersect(P a,P b,P c,P d){
	LD s1=det(a,b,c);
	LD s2=det(a,b,d);
	return (d*s1-c*s2)/(s1-s2);
}
struct L{
	P a,b;
	P v(){return b-a;}
	L(){}
	L(P a,P b):a(a),b(b){}
}l[maxn];
bool operator==(L a,L b){
	return a.a==b.a&&a.b==b.b;
}
bool operator<(L a,L b){
	return !(a.a==b.a)?a.a<b.a:a.b<b.b;
}
P intersect(L l1,L l2){
	return intersect(l1.a,l1.b,l2.a,l2.b);
}
bool parallel(P a,P b){
	return !sgn(a*b);
}
L Rev(L l){
	l.b=l.a+l.v().turn90();
	return l;
}
int n;
L binary(L l1,L l2){
	L ans;
	if(parallel(l1.v(),l2.v())){
		P v=l1.v().turn90();
		L newl=L(l1.a,l1.a+v);
		P p=intersect(newl,l2);
		ans.a=(l1.a+p)/2.0;
		ans.b=ans.a+l1.v();
	}else{
		P e1=l1.v()/l1.v().len();
		P e2=l2.v()/l2.v().len();
		P p=intersect(l1,l2);
		ans.a=p;
		ans.b=p+e1+e2;
	}
	return ans;
}
bool Online(P p,L l){
	return sgn((p-l.a)*(l.b-l.a))==0;
}
vector<L>ansL;
vector<P>ansP;
void Intersec(L l){
	vector<L>tmpL;
	vector<P>tmpP;
	
	for(int i=0;i<ansP.size();i++){
		if(Online(ansP[i],l))	
			tmpP.push_back(ansP[i]);
	}
	
	for(int i=0;i<ansL.size();i++){
		if(parallel(ansL[i].v(),l.v())){
			if(Online(l.a,ansL[i])){
				tmpL.push_back(ansL[i]);
			}
		}else{
			P p=intersect(l,ansL[i]);
			tmpP.push_back(p);
		}
	}
	
	ansP=tmpP;
	ansL=tmpL;
	sort(ansP.begin(),ansP.end());
	ansP.erase(unique(ansP.begin(),ansP.end()),ansP.end());
	sort(ansL.begin(),ansL.end());
	ansL.erase(unique(ansL.begin(),ansL.end()),ansL.end());
}
void Intersec(L l1,L l2){
	vector<L>tmpL;
	vector<P>tmpP;
	
	for(int i=0;i<ansP.size();i++){
		if(Online(ansP[i],l1) || Online(ansP[i],l2))	
			tmpP.push_back(ansP[i]);
	}
	
	for(int i=0;i<ansL.size();i++){
		if(parallel(ansL[i].v(),l1.v())){
			if(Online(l1.a,ansL[i])){
				tmpL.push_back(ansL[i]);
			}
		}else{
			P p=intersect(l1,ansL[i]);
			tmpP.push_back(p);
		}
		if(parallel(ansL[i].v(),l2.v())){
			if(Online(l2.a,ansL[i])){
				tmpL.push_back(ansL[i]);
			}
		}else{
			P p=intersect(l2,ansL[i]);
			tmpP.push_back(p);
		}
	}
	
	ansP=tmpP;
	ansL=tmpL;	
	sort(ansP.begin(),ansP.end());
	ansP.erase(unique(ansP.begin(),ansP.end()),ansP.end());
	sort(ansL.begin(),ansL.end());
	ansL.erase(unique(ansL.begin(),ansL.end()),ansL.end());
}
void printans(){
	for(int i=0;i<ansP.size();i++){
		printf("(%.3f,%.3f)%c",(double)ansP[i].x,(double)ansP[i].y," \n"[i+1==ansP.size()]);
	}
	
	for(int i=0;i<ansL.size();i++){
		printf("(%.3f,%.3f)--(%.3f,%.3f)%c",(double)ansL[i].a.x,(double)ansL[i].a.y,(double)ansL[i].b.x,(double)ansL[i].b.y," \n"[i+1==ansL.size()]);
	}
	
}
int main(){
	while(scanf("%d",&n)!=-1){
		if(!n)break;
		for(int i=1;i<=n;i++){
			l[i].a.read();
			l[i].b.read();
		}
		
		if(n<=2){
			puts("Many");
			continue;
		}
		ansL.clear();
		ansP.clear();
		
		if(sgn(l[1].v()*l[2].v())==0){
			ansL.push_back(binary(l[1],l[2]));
		}else{
			L li=binary(l[1],l[2]);
			ansL.push_back(li);
			li.b=li.a+li.v().turn90();
			ansL.push_back(li);
		}
		
		//printans();
		
		for(int i=3;i<=n;i++){			
			if(sgn(l[1].v()*l[i].v())==0){
				Intersec(binary(l[1],l[i]));
			}else{
				L li=binary(l[1],l[i]);
				L li2=li;
				li2.b=li2.a+li2.v().turn90();
				Intersec(li,li2);
			}

			//printf("ans after %d\n",i);
			//printans();

		}
		
		
		if(ansL.empty()&&ansP.empty()){
			puts("None");
		}else
		if(!ansL.empty() || ansP.size()>1){
			puts("Many");
		}else{
			printf("%.8f %.8f\n",(double)ansP[0].x,(double)ansP[0].y);
		}
	}
	return 0;
}

