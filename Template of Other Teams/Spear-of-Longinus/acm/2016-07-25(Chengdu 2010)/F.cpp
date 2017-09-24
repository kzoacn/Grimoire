#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
const int maxn=10010;
typedef long double LD;
const LD eps=1e-9;

int sgn(LD x){return (x>eps)-(x<-eps);}
int n;
struct curve{
	LD a,b,c;
}f[maxn];
bool check(LD mid){
	static pair<LD,LD> seg[maxn];
	int siz=0;
	for(int i=1;i<=n;i++){
		LD a=f[i].a;
		LD b=f[i].b;
		LD c=f[i].c;
		if(sgn(a)){
			LD delta=b*b-4*a*(c-mid);
			if(sgn(delta)<=0)
				return 0;
			siz++;
			seg[siz].first=(-b-sqrt(delta))/(2*a);
			seg[siz].second=(-b+sqrt(delta))/(2*a);
			seg[siz].first=max(seg[siz].first,(LD)0.0);
			seg[siz].second=min(seg[siz].second,(LD)1000.0);
		}else if(sgn(b)){
			if(sgn(b)>0){
				siz++;
				seg[siz].first=0;
				seg[siz].second=(mid-c)/b;
			}else{
				siz++;
				seg[siz].first=(mid-c)/b;
				seg[siz].second=1000.0;
			}	
		}else{
			if(sgn(c-mid)>=0)
				return 0;
				
		}
	}
	
//	for(int i=1;i<=siz;i++)
//		printf("%.3f %.3f\n",seg[i].first,seg[i].second);
	
	for(int i=1;i<=siz;i++)
		if(sgn(seg[i].first-seg[i].second)>=0)
			return 0;
	
	
	if(!siz)
		return 1;
	pair<LD,LD>se=seg[1];
	for(int i=2;i<=siz;i++){
		if(sgn(seg[i].first-se.second)>=0||sgn(seg[i].second-se.first)<=0)
			return 0;
		se.first=max(se.first,seg[i].first);
		se.second=min(se.second,seg[i].second);
	}
	return 1;
}
int main(){
	int T;scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			double a,b,c;
			scanf("%lf%lf%lf",&a,&b,&c);
			f[i].a=a;
			f[i].b=b;
			f[i].c=c;
		}
			
		LD l=-1e12,r=1e12;
		int tm=70;
		while(tm--){
			LD mid=(l+r)/2;
			if(check(mid))
				r=mid;
			else 
				l=mid;
		}
		printf("%.4f\n",(double)l);
	}
	return 0;
}
