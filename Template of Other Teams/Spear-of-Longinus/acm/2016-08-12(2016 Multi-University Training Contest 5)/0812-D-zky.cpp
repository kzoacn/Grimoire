#include<bits/stdc++.h>
using namespace std;
const int maxn=2002;
typedef long long LL;
int n;
struct P{
	int x,y;
	P(){}
	P(const int &_x,const int &_y):x(_x),y(_y){}
	void read(){
		int tx,ty;
		scanf("%d%d",&tx,&ty);
		x=tx;y=ty;
	}
	P normal(){
		LL d=__gcd(abs(x),abs(y));
		return P(x/d,y/d);
	}
	double ang;
}p[maxn];
P operator+(P a,P b){
	return P(a.x+b.x,a.y+b.y);
}
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
LL operator^(P a,P b){
	return (LL)a.x*b.x+(LL)a.y*b.y;
}
LL operator*(P a,P b){
	return (LL)a.x*b.y-(LL)a.y*b.x;
}
bool cmp(const P &a,const P &b){
	return a.ang<b.ang;
}
double atan2(P p){
	return atan2(p.y,p.x);
}
int main(){
	while(scanf("%d",&n)==1){
		
		if(!n)break;
	
		for(int i=1;i<=n;i++)
			p[i].read();
	
		LL cnt=(LL)n*(n-1)*(n-2)/6;
		LL ans=0;
		for(register int i=1;i<=n;i++){
			static P vec[maxn*2];
			int siz=0;
			for(int j=1;j<=n;j++)if(i!=j){
				vec[siz++]=(p[j]-p[i]);
				vec[siz-1].ang=atan2(vec[siz-1]);
			}
			sort(vec,vec+siz,cmp);
			int m=siz;
			for(int j=0;j<m;j++){
				vec[siz++]=(vec[j]);
				//fprintf(stderr,"(%d,%d)\n",vec[j].x,vec[j].y);
			}

			int k=0;
			for(register int j=0;j<m;j++){
				if(j==k)k++;
				LL dot=(vec[j]^vec[k]);
				LL det=vec[j]*vec[k];
				while(k<j+m && dot>0 && (det>0 || (det==0 && k<m))  ){
					k++;
					dot=vec[j]^vec[k];
					det=vec[j]*vec[k];
				}
				//cerr<<j<<" "<<k<<endl;
				//cerr<<j<<" is "<<k-j<<endl;
				ans+=k-j-1;
			}
		}	
		printf("%lld\n",ans-cnt*2);
	}
	return 0;
}
