#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
typedef long long LL;
int n;
struct P{
	int x,y;
	int p;
	void read(){
		scanf("%d%d%d",&x,&y,&p);
	}
	double ang()const{
		return atan2(y,x);
	}
	bool operator<(const P &oth)const{
		return ang()<oth.ang();
	}
}p[maxn];

const int MAGIC=233;
int mn[maxn];

LL operator^(P a,P b){
	return 1ll*a.x*b.x+1ll*a.y*b.y;
}
LL operator*(P a,P b){
	return 1ll*a.x*b.y-1ll*a.y*b.x;
}

int sgn(LL x){return (x>0)-(x<0);}

P sp[maxn];
bool check(P a,P b,P c){
	if(sgn(a*b)!=sgn(b*c)||sgn(b*c)!=sgn(c*a)||sgn(c*a)!=sgn(a*b))
		return false;
	return true;
}

int main(){
	scanf("%d",&n);
	int m=0;
	for(int i=1;i<=n;i++){
		p[++m].read();
		if(p[m].x==0&&p[m].y==0)
			m--;
	}
	n=m;
	sort(p+1,p+1+n);
	int bcnt=0;
	for(int i=0;i<=n;i++){
		mn[i]=2e9;
	}
	for(int i=1;i<=n;i++){
		mn[i/MAGIC+1]=min(mn[i/MAGIC+1],p[i].p);
		sp[i/MAGIC+1]=p[i];
		bcnt=i/MAGIC+1;
	}

	long long ans=1LL<<60;
	for(int i=1;i<=n;i+=MAGIC){	
		for(int j=i+1;j<=n&&j<i+MAGIC;j++){
			for(int k=j+1;k<=n&&k<i+MAGIC;k++){
				if(check(p[i],p[j],p[k]))
					ans=min(ans,(long long)p[i].p+p[j].p+p[k].p);
			}
		}
	}
	for(int i=1;i<=bcnt;i++){
		for(int j=i+1;j<=bcnt;j++)
			for(int k=j+1;k<=bcnt;k++){

				if(check(sp[i],sp[j],sp[k]))
					ans=min(ans,(long long)mn[i]+mn[j]+mn[k]);
			}
	
	}
	if(ans==(1LL<<60))ans=-1;
	cout<<ans<<endl;
	
	
	return 0;
}
