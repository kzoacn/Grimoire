#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
typedef double LD;
const LD eps=1e-10;
const int maxn=210;
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
}l[maxn],nl[maxn*maxn];
P intersect(L l1,L l2){
	return intersect(l1.a,l1.b,l2.a,l2.b);
}
bool paraell(P a,P b){
	return !sgn(a*b);
}

vector<P> convex_hull(vector<P> point){
	sort(point.begin(),point.end());
	vector<P>convex;
	vector<P>stack;
	for(int i=0;i<point.size();i++){
		while(stack.size()>=2
			&&sgn(det(stack[stack.size()-2],stack.back(),point[i]))<=0)
				stack.pop_back();
		stack.push_back(point[i]);
	}
	for(int i=0;i<stack.size();i++)
		convex.push_back(stack[i]);
	stack.clear();
	for(int i=int(point.size())-1;i>=0;i--){
		while(stack.size()>=2
			&&sgn(det(stack[stack.size()-2],stack.back(),point[i]))<=0)
				stack.pop_back();
		stack.push_back(point[i]);		
	}
	for(int i=1;i+1<stack.size();i++)
		convex.push_back(stack[i]);
	return convex;
}
bool project(P p,L l){
	return sgn((p-l.a)^(l.b-l.a))>=0&&sgn((p-l.b)^(l.a-l.b))>=0;
}
double dis(P a,P b){return (a-b).len();}
double dis(P p,L l){
	if(project(p,l)){
		return fabs((p-l.a)*l.v())/l.v().len();
	}else{
		return min(dis(p,l.a),dis(p,l.b));
	}
}
double dis(vector<P>&p1,vector<P>&p2){
	double ans=1e30;
	for(int i=0;i<p1.size();i++){
		for(int j=0;j<p2.size();j++){
			ans=min(ans,dis(p1[i],L(p2[j],p2[(j+1)%p2.size()])));
		}
	}
	swap(p1,p2);
	for(int i=0;i<p1.size();i++){
		for(int j=0;j<p2.size();j++){
			ans=min(ans,dis(p1[i],L(p2[j],p2[(j+1)%p2.size()])));
		}
	}
	swap(p1,p2);
	return ans;
}
int W,n;
vector<P>poly[maxn];
double disl[maxn],disr[maxn];
double mp[maxn][maxn];
int main(){
	while(scanf("%d%d",&W,&n)==2){
		if(!W&&!n)break;
		for(int i=1;i<=n;i++){
			int m;scanf("%d",&m);
			P p;poly[i].clear();
			while(m--){
				p.read();
				poly[i].push_back(p);
			}
			poly[i]=convex_hull(poly[i]);
			/*for(int j=0;j<poly[i].size();j++){
				printf("(%.3f,%.3f)%c",poly[i][j].x,poly[i][j].y," \n"[j+1==poly[i].size()]);
			}*/
		}
		
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++)if(i!=j){
				mp[i][j]=dis(poly[i],poly[j]);
				
			}
			mp[i][i]=0;
			
		}
				
		for(int k=1;k<=n;k++)
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					mp[i][j]=min(mp[i][j],mp[i][k]+mp[k][j]);
		
		for(int i=1;i<=n;i++){
			disl[i]=disr[i]=1e20;
			for(int j=0;j<poly[i].size();j++){
				disl[i]=min(disl[i],poly[i][j].x);
				disr[i]=min(disr[i],W-poly[i][j].x);
			}
			
			//printf("%.3f %.3f\n",disl[i],disr[i]);
		}			
		
		/*for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				printf("%.3f%c",mp[i][j]," \n"[j==n]);
			}
		}*/
		
		double ans=W;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				ans=min(ans,disl[i]+mp[i][j]+disr[j]);
		printf("%.10f\n",ans);
	}
	return 0;
}
