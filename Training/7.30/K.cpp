#include<bits/stdc++.h>
using namespace std;
const int maxn=555;
int n;

int mp[999][999];
int step=411;

struct P{
	int x,y;
	P(){}
	P(int _x,int _y):x(_x),y(_y){}
	P turn90(){
		return P(-y,x);
	}
}p[maxn];
P operator+(P a,P b){
	return P(a.x+b.x,a.y+b.y);
}
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
int main(){
	while(scanf("%d",&n)==1){
		static int T=0;
		T++;
		for(int i=1;i<=n;i++){
			scanf("%d%d",&p[i].x,&p[i].y);
			mp[p[i].x+step][p[i].y+step]=T;
		}
		int ans=0;
		
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++)if(i!=j){
				P v=p[i]-p[j];
				P a=p[i]+v.turn90();
				P b=a+v.turn90().turn90();
				if(mp[p[i].x+step][p[i].y+step]==T)
				if(mp[p[j].x+step][p[j].y+step]==T)
				if(mp[a.x+step][a.y+step]==T)
				if(mp[b.x+step][b.y+step]==T)
					ans++;
			}
		}
		
		printf("%d\n",ans/4);
	}
	return 0;
}
