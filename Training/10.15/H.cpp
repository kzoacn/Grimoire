#include<bits/stdc++.h>
using namespace std;

struct P{
	double x,y;
	P(){}
	P(double _x,double _y):x(_x),y(_y){}
	double len(){return sqrt(x*x+y*y);}
	double len2(){return (x*x+y*y);}
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
P operator/(P a,double b){
	return P(a.x/b,a.y/b);
}
double operator*(P a,P b){
	return a.x*b.y-a.y*b.x;
}
double operator^(P a,P b){
	return a.x*b.x+a.y*b.y;
}
double det(P a,P b,P c){
	return (b-a)*(c-a);
}
struct L{
	P a,b;
	L(){}
	L(P _a,P _b):a(_a),b(_b){}
	P v(){return b-a;}
};
P intersect(L l1,L l2){
	double s1=det(l1.a,l1.b,l2.a);
	double s2=det(l1.a,l1.b,l2.b);
	return (l2.a*s2-l2.b*s1)/(s2-s1);
}
P project(P p,L l){
	return l.a+l.v()*((p-l.a)^l.v())/l.v().len2();
}

P oppo(P p,L l){
	P pr=project(p,l);
	return pr+(pr-p);
}

struct Obj{
	L l;
	P p;
	bool isP;
	Obj(){};
};
Obj newP(P p){
	Obj o;
	o.isP=1;
	o.p=p;
	return o;
}
Obj newL(L l){
	Obj o;
	o.isP=0;
	o.l=l;
	return o;
}
char s[2122];
int getnum(int l,int r){
	int x=0,ty=1;
	for(int i=l;i<=r;i++){
		if(s[i]=='-')ty=-1;
		else{
			x=x*10+s[i]-'0';
		}
	}
	return x*ty;
}
int dep=0;
int match[444];
Obj getexp(int l,int r){

	//cerr<<l<<" "<<r<<endl;

	//if(++dep>4){
	//	exit(0);
	//}

	while(match[l]==r)l++,r--;
	Obj obj;
	if(isdigit(s[l])||s[l]=='-'){
		int mid=-1;
		for(int i=l;i<=r;i++)if(s[i]==',')
			mid=i;
		int x=getnum(l,mid-1);
		int y=getnum(mid+1,r);
		return obj=newP(P(x,y));
	}
	
	int sum=0,mid=-1;
	for(int i=l;i<=r;i++){
		if(sum==0&&s[i]=='@'){
			mid=i;
//			break;
		}
		if(s[i]=='(')sum++;
		if(s[i]==')')sum--;
	}
	Obj lef=getexp(l,mid-1);
	Obj rig=getexp(mid+1,r);
	
	if(lef.isP&&rig.isP){
		return newL(L(lef.p,rig.p));
	}else if(!lef.isP&&!rig.isP){
		return newP(intersect(lef.l,rig.l));
	}else if(lef.isP){
		return newP(oppo(lef.p,rig.l));
	}else{
		return newP(oppo(rig.p,lef.l));
	}
}

int main(){
	while(scanf("%s",s+1)==1){
		if(s[1]=='#')break;
		
		stack<int>S;
		int n=strlen(s+1);
		for(int i=1;i<=n;i++)match[i]=0;
		for(int i=1;i<=n;i++){
			if(s[i]=='('){
				S.push(i);
			}else if(s[i]==')'){
				match[S.top()]=i;
				match[i]=S.top();
				S.pop();
			}
		}
		
		Obj ans=getexp(1,strlen(s+1));
		printf("%.10f %.10f\n",ans.p.x,ans.p.y);
	}
	return 0;
}
