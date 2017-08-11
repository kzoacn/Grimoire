#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=22;
int n;
struct P{
	LL x,y;
	P(){}
	P(LL _x,LL _y):x(_x),y(_y){}
	void read(){
		scanf("%lld%lld",&x,&y);
	}
}p[maxn],np[maxn];
P operator+(P a,P b){
	return P(a.x+b.x,a.y+b.y);
}
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
P operator*(P a,LL b){
	return P(a.x*b,a.y*b);
}
LL operator^(P a,P b){
	return a.x*b.x+a.y*b.y;
}
LL operator*(P a,P b){
	return a.x*b.y-a.y*b.x;
}
LL sgn(LL x){
	if(x>0)return 1;
	if(x<0)return -1;
	return 0;
}
int dir(P p,P a,P b){
	return sgn((p-a)*(b-a));
}
bool intersect(P a,P b,P c,P d){
	if(dir(c,a,b)*dir(d,a,b)<0&&dir(a,c,d)*dir(b,c,d)<0)
		return true;
	return false;
}

bool check(){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(intersect(p[i],p[(i+1)%n],np[j],np[(j+1)%n]))
				return false;
		}
	}
	return true;
}

bool check(P v1,P v2){
	for(int i=-2;i<=2;i++){
		for(int j=-2;j<=2;j++){
			if(i==0&&j==0)continue;
			for(int k=0;k<n;k++){
				np[k]=p[k]+v1*i+v2*j;
			}
			if(!check())
				return false;
		}
	}
	return true;
}

bool solve(){
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		p[i].read();
	
	LL ans2=0;
	for(int i=0;i<n;i++){
		ans2+=p[i]*p[(i+1)%n];
	}	
	ans2=llabs(ans2);
	if(ans2%2==1)
		return false;
	ans2/=2;
	P v1,v2;
	
	//cerr<<ans2<<endl;
	
	//TODO
	for(v1.x=-44;v1.x<=44;v1.x++)
	for(v1.y=-44;v1.y<=44;v1.y++)
	for(v2.x=-43;v2.x<=44;v2.x++)
	for(v2.y=-43;v2.y<=43;v2.y++){

		if(llabs(v1*v2)!=ans2)continue;
	
		if(check(v1,v2)){
			//cerr<<v1.x<<" "<<v1.y<<endl;
			//cerr<<v2.x<<" "<<v2.y<<endl;
			return true;
		}
	}
	return false;		
}


int main(){
	int T;cin>>T;
	for(int t=1;t<=T;t++){
		printf("Case #%d: %s\n",t,solve()?"Yes":"No");
	}
	return 0;
}
