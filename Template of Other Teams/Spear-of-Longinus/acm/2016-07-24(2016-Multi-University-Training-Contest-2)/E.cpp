#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
const int maxn=1010;
const int mo=1e9+7;
typedef long long LL;
LL gcd(LL a,LL b){
	if(!b)return a;
	return gcd(b,a%b);
}
struct P{
	LL x,y,cnt;
	P(){}
	P(LL _x,LL _y){
		x=_x;y=_y;
	}
	void read(){
		int tx,ty;
		scanf("%d%d",&tx,&ty);
		x=tx;y=ty;
	}
}p[maxn],tp[maxn];
bool operator<(const P &a,const P &b){
	return a.x!=b.x?a.x<b.x:a.y<b.y;
}
bool operator==(const P &a,const P &b){
	return a.x==b.x&&a.y==b.y;
}
P operator+(const P &a,const P &b){
	return P(a.x+b.x,a.y+b.y);
}
P operator-(const P &a,const P &b){
	return P(a.x-b.x,a.y-b.y);
}
int n;
long long two[maxn];
int siz,siz2;
P ang[maxn],tang[maxn];
long long cot[maxn];
int main(){
	two[0]=1;
	for(int i=1;i<maxn;i++)
		two[i]=(two[i-1]+two[i-1])%mo;
	int T;
	scanf("%d",&T);
	while(T--){
		long long ans=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			p[i].read();
			tp[i]=p[i];
		}
		sort(tp+1,tp+1+n);
		
		
		
		int nn=unique(tp+1,tp+1+n)-tp-1;
		
		for(int i=1;i<=nn;i++){
			cot[i]=0;
			for(int j=1;j<=n;j++){
				if(tp[i]==p[j])	
					cot[i]++;
			}
		}
		
		if(nn==1){
			ans=(two[n]-n-1+mo)%mo;
			cout<<(ans+mo)%mo<<endl;
			continue;
		}	
		
		for(int i=1;i<=nn;i++)
			ans=(ans+two[cot[i]]-cot[i]-1+mo)%mo;
//		cerr<<ans<<endl;
		
		for(int i=1;i<=nn;i++){
			siz=0,siz2=0;
			int self=cot[i];
			
			
			for(int j=1;j<=nn;j++)if(i!=j){
				siz++;
				ang[siz]=P(tp[j].x-tp[i].x,tp[j].y-tp[i].y);
				LL d=gcd(abs(ang[siz].x),abs(ang[siz].y));
				if(d != 1) {
					ang[siz].x/=d;ang[siz].y/=d;
				}
				ang[siz].cnt=cot[j];
			}
			
			
			sort(ang+1,ang+1+siz);
			for(int j=1;j<=siz;j++)
				tang[++siz2]=ang[j];
				
			siz2=unique(tang+1,tang+1+siz2)-tang-1;
				
			LL cnt=self;
			//cerr<<"self"<<" "<<self<<endl;
			two[0]=0;
			long long res=(long long)(two[self]-self-1+mo)%mo;
			for(int j=1;j<=siz;j++){
				cnt+=ang[j].cnt;
				if(ang[j].cnt>=2)
				res+=(long long)(two[ang[j].cnt]-ang[j].cnt-1+mo)%mo;
				res%=mo;
				
				if(j==siz||!(ang[j]==ang[j+1])){
					//cerr<<cnt<<" "<<(sgn(ang[j])>0)<<" "<<check(ang[j])<<endl;
					if(cnt>=2&&(ang[j].x>0||(ang[j].x==0&&ang[j].y<0))&&!binary_search(tang+1,tang+1+siz2,P(-ang[j].x,-ang[j].y))){
						ans=(ans+(long long)two[cnt]-cnt-1+mo);
						ans+=mo;
						ans=(ans-res+mo)%mo;
						ans %= mo;
						
						//cerr<<"res"<<" "<<res<<endl;
						//cerr<<"cnt"<<" "<<cnt<<endl;
					}
					res=(long long)(two[self]-self-1+mo)%mo;
					cnt=self;
				}
			}
		}
		cout<<(ans+mo)%mo<<endl;
	}
	return 0;
}


