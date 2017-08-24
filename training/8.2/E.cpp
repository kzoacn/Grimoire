#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
struct P{
	LL x,y;
	P(){}
	P(LL _x,LL _y):x(_x),y(_y){}
	void read(){
		scanf("%lld%lld",&x,&y);
	}
	void print(){
		printf("%lld,%lld\n",x,y);
	}
};
bool operator<(P a,P b){
	return a.x!=b.x ? a.x<b.x : a.y<b.y;
}
P operator+(P a,P b){
	return P(a.x+b.x,a.y+b.y);
}
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
LL operator*(P a,P b){
	return a.x*b.y-a.y*b.x;
}
LL det(P a,P b,P c){
	return (b-a)*(c-a);
}
vector<P>convex(vector<P>p){
	sort(p.begin(),p.end());
	vector<P>ans,S;
	for(int i=0;i<p.size();i++){
		while(S.size()>=2&&det(S[S.size()-2],S.back(),p[i])<=0)
			S.pop_back();
		S.push_back(p[i]);
	}
	ans=S;
	S.clear();
	for(int i=(int)p.size()-1;i>=0;i--){
		while(S.size()>=2&&det(S[S.size()-2],S.back(),p[i])<=0)
			S.pop_back();
		S.push_back(p[i]);
	}
	for(int i=1;i+1<S.size();i++)
		ans.push_back(S[i]);
	return ans;
}
const double sqrt2=sqrt(2);
double dis(P a,P b){
	LL dx=llabs(a.x-b.x);
	LL dy=llabs(a.y-b.y);
	double d=llabs(dx-dy)+min(dx,dy)*sqrt2;
//	a.print();
//	b.print();
//	cerr<<d<<endl;
	return d;
}


int main(){
freopen("E.in","r",stdin);
	vector<P>p;
	int n;scanf("%d",&n);
	for(int i=0;i<n;i++){
		P pt;pt.read();
		p.push_back(pt+P(1,0));
		p.push_back(pt+P(-1,0));
		p.push_back(pt+P(0,1));
		p.push_back(pt+P(0,-1));
	}
	vector<P>hull=convex(p);
//	cerr<<hull.size()<<endl;
	double ans=0;
//	for(auto pt:hull)
//		pt.print();
	
	for(int i=0;i<hull.size();i++){
		ans+=dis(hull[i],hull[(i+1)%hull.size()]);
	}
	
	printf("%.10f\n",ans);
	return 0;
}
