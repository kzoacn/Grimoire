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
}p[1010];
P operator+(P a,P b){
	return P(a.x+b.x,a.y+b.y);
}
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
LL operator*(P a,P b){
	return a.x*b.y-a.y*b.x;
}
LL operator^(P a,P b){
	return a.x*b.x+a.y*b.y;
}
bool operator==(P a,P b){
	return a.x==b.x && a.y==b.y;
}
bool operator<(P a,P b){
	return a.x!=b.x ? a.x<b.x: a.y<b.y;
}
bool operator>(P a,P b){
	return a.x!=b.x ? a.x>b.x: a.y>b.y;
}
LL det(P a,P b,P c){
	return (b-a)*(c-a);
}
vector<P>convex(vector<P>p){
	sort(p.begin(),p.end());
	//cerr<<"build "<<p.size()<<endl;
	vector<P>ans,S;
	for(int i=0;i<p.size();i++){
		while(S.size()>=2
			&&det(S[S.size()-2],S.back(),p[i])<=0)
				S.pop_back();
		S.push_back(p[i]);
	}
	ans=S;
	S.clear();
	for(int i=(int)p.size()-1;i>=0;i--){
		while(S.size()>=2
			&&det(S[S.size()-2],S.back(),p[i])<=0)
				S.pop_back();
		S.push_back(p[i]);
	}
	for(int i=1;i+1<S.size();i++)
		ans.push_back(S[i]);
	//cerr<<"end "<<ans.size()<<endl;
	return ans;
}

bool onLine(P p,P a,P b){
	return det(p,a,b)==0;
}
bool onSeg(P p,P a,P b){
	return onLine(p,a,b) && ((p-a)^(b-a))>=0 && ((p-b)^(a-b))>=0;
}

const LL INF=1LL<<61;
struct Convex{
	int n;
	vector<P>a,upper,lower;
	Convex(){}
	Convex(vector<P>_a):a(_a){
		n=a.size();
		//cerr<<"n="<<n<<endl;
		int ptr=0;
		for(int i=1;i<n;i++)if(a[ptr]<a[i])ptr=i;
		for(int i=0;i<=ptr;i++)lower.push_back(a[i]);
		for(int i=ptr;i<n;i++)upper.push_back(a[i]);
		upper.push_back(a[0]);
	}
	int sign(LL x){return x<0?-1:x>0;}
	bool contain(P p){
		if(a.size()<=2){
			if(a.size()==1)return p==a[0];
			if(a.size()==2){
				return onSeg(p,a[0],a[1]);
			}	
		}
		if(p.x<lower[0].x||p.x>lower.back().x)return false;
		int id=lower_bound(lower.begin(),lower.end(),P(p.x,-INF))-lower.begin();
		if(lower[id].x==p.x){
			if(lower[id].y>p.y)return false;
		}else if((lower[id-1]-p)*(lower[id]-p)<0)return false;
		id=lower_bound(upper.begin(),upper.end(),P(p.x,INF),greater<P>())-upper.begin();
		if(upper[id].x==p.y){
			if(upper[id].y<p.y)return false;
		}else if((upper[id-1]-p)*(upper[id]-p)<0)return false;
		return true;
		
	}
}ch1,ch2;

int n;
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		p[i].read();
		
	return 0;
}
