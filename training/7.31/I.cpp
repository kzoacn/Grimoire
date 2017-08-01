#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
struct P{
	int x,y;
	P(){}
}p[maxn];

struct cmpX{
	bool operator()(int a,int b)const{
		if(p[a].x!=p[b].x)
			return p[a].x<p[b].x;
		return a<b;
	}
};

struct cmpY{
	bool operator()(int a,int b)const{
		if(p[a].y!=p[b].y)
			return p[a].y<p[b].y;
		return a<b;
	}
};

map<int,set<int,cmpX> >Y,XY,YX;
map<int,set<int,cmpY> >X;

template<class T>
int nxt(int t,T& S){
	auto it=S.lower_bound(t);
	it++;
	if(it==S.end())
		return -1;
	return *it;
}

template<class T>
int pre(int t,T& S){
	auto it=S.lower_bound(t);
	if(it==S.begin())
		return -1;
	it--;
	return *it;
}

int n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&p[i].x,&p[i].y);
	}
	p[0].x=0;
	p[0].y=0;
	
	for(int i=0;i<=n;i++){
		X[p[i].x].insert(i);
		Y[p[i].y].insert(i);
		XY[p[i].x+p[i].y].insert(i);
		YX[p[i].x-p[i].y].insert(i);
	}
	int ans=0;
	for(int i=0;i<n;i++){
		P a=p[i],b=p[i+1];
		int ok=1;
		//cerr<<"i="<<i<<endl;
		//cerr<<a.x<<" "<<a.y<<endl;
		//cerr<<b.x<<" "<<b.y<<endl;
		
		if(a.x==b.x){
			if(a.y<b.y)
				ok&=(nxt(i,X[a.x])==i+1);
			else
				ok&=(pre(i,X[a.x])==i+1);
			/*cerr<<X[a.x].size()<<endl;
			cerr<<"pre="<<pre(i,X[a.x])<<endl;
			cerr<<"nxt="<<nxt(i,X[a.x])<<endl;
			cerr<<"ok="<<ok<<endl;*/
		}else
		if(a.y==b.y){
			if(a.x<b.x)
				ok&=(nxt(i,Y[a.y])==i+1);
			else
				ok&=(pre(i,Y[a.y])==i+1);
		}else
		if(a.x+a.y==b.x+b.y){
			if(a.x<b.x)
				ok&=(nxt(i,XY[a.x+a.y])==i+1);
			else
				ok&=(pre(i,XY[a.x+a.y])==i+1);
		}else
		if(a.x-a.y==b.x-b.y){
			if(a.x<b.x)
				ok&=(nxt(i,YX[a.x-a.y])==i+1);
			else
				ok&=(pre(i,YX[a.x-a.y])==i+1);
		}else ok=0;
		
		X[p[i].x].erase(i);
		Y[p[i].y].erase(i);
		XY[p[i].x+p[i].y].erase(i);
		YX[p[i].x-p[i].y].erase(i);
		
		if(ok)ans=i+1;
		else break;
	}
	cout<<ans<<endl;	
	return 0;
}
