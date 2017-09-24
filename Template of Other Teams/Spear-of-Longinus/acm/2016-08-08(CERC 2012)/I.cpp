#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long LL;
typedef long long LD;
const LD eps=1e-15;
typedef unsigned long long UL;
const int maxn=5e4+5;
int sgn(LD x){return (x>eps)-(x<-eps);}
UL hsh[maxn],h[101][2];
int n,m;
struct P{
	LD x,y;
	P(){}
	P(LD _x,LD _y):x(_x),y(_y){}
}p[maxn];

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
struct L{
	LL A,B,C;
	L(){}
}l[maxn];
UL randUL(){
	UL x=rand();
	UL y=rand();
	UL z=rand();
	UL w=rand();
	return (x | (y << 32UL)) ^ ( z << 16UL) ^ (w << 48UL);
}

bool Cross(L l1,L l2){
	if(l1.A*l2.B==l1.B*l2.A)
		return false;
	return true;
}
bool OnLeft(P p,L l){
	return l.A*p.x+l.B*p.y+l.C<0;
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++){
			int A,B,C;
			scanf("%d%d%d",&A,&B,&C);
			l[i].A=A;
			l[i].B=B;
			l[i].C=C;
			
			h[i][0]=randUL();
			h[i][1]=randUL();
			
			//printf("(%.3f,%.3f)->(%.3f,%.3f)\n",l[i].a.x,l[i].a.y,l[i].b.x,l[i].b.y);
							
		}
		
		for(int j=1;j<=m;j++){
			hsh[j]=0;
			double tx,ty;
			scanf("%lf%lf",&tx,&ty);
			p[j].x=tx;
			p[j].y=ty;
		}
		
		int res=1;
		for(int i=1;i<=n;i++){
			res++;
			for(int j=1;j<i;j++){
				if(Cross(l[i],l[j]))
					res++;
				//else cerr<<i<<" "<<j<<endl;
			}	
		}
		
		for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			hsh[j]^=h[i][OnLeft(p[j],l[i])?1:0];
		}
		sort(hsh+1,hsh+1+m);
		int ans=unique(hsh,hsh+1+m)-hsh-1;
		
		//cerr<<res<<" "<<ans<<endl;
					
		puts(ans>=res ? "PROTECTED" : "VULNERABLE");
	}
	return 0;
}
