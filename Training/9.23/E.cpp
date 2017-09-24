#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=111;
struct P{
	LL x,y;
	int id;
	P(){}
	P(LL _x,LL _y):x(_x),y(_y){}
	void read(){scanf("%lld%lld",&x,&y);}
}p[maxn];

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


struct L{
	P a,b;
	L(){}
	L(P _a,P _b):a(_a),b(_b){}
}seg[maxn*maxn];

bool onLine(P p,L l){
	return (p-l.a)*(l.b-l.a)==0;
}

bool onSeg(P p,L l){
	return onLine(p,l) && ((p-l.a)^(l.b-l.a))>=0 && ((p-l.b)^(l.a-l.b))>=0;
}
int n;
int anss[maxn];


bool onLeft(P p,L l){
	return (p-l.b)*(l.b-l.a)<=0;
}

int dir(P p,L l){
	LL t=(p-l.b)*(l.b-l.a);
	if(t<0)return -1;
	if(t>0)return 1;
	return 0;
}
bool intersect(L l1,L l2){
	if(dir(l2.a,l1)*dir(l2.b,l1)<0&&dir(l1.a,l2)*dir(l1.b,l2)<0)
		return true;
	return false;
}
bool in_tri(P pt,P *p){
	if((p[1]-p[0])*(p[2]-p[0])<0)
		reverse(p,p+3);
	for(int i=0;i<3;i++){
		if(!onLeft(pt,L(p[i],p[(i+1)%3])))
			return false;
	}
	return true;
}

void solve(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		p[i].read();
		p[i].id=i;
		anss[i]=0;
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(p[i]==p[j]){
				anss[i]=1;
				goto yes;
			}
		}
	}
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)if(i!=j){
			for(int k=1;k<=n;k++)if(k!=i&&k!=j){
				if(onSeg(p[k],L(p[i],p[j]))){
					anss[k]=1;
					anss[i]=anss[j]=0;
					goto yes;
				}
			}
		}
	}
	
	if(n<=3){
		puts("NO");
		return ;
	}
	if(n==4){
		
		int s=0;
		for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			seg[++s]=L(p[i],p[j]);
		for(int i=1;i<=s;i++){
			for(int j=i+1;j<=s;j++){
				if(intersect(seg[i],seg[j])){
					anss[seg[i].a.id]=anss[seg[i].b.id]=0;
					anss[seg[j].a.id]=anss[seg[j].b.id]=1;
					goto yes;
				}
			}
		}
		
		for(int i=1;i<=n;i++){
			P tmp[3];
			int s=0;
			for(int j=1;j<=n;j++){
				if(i!=j){
					tmp[s++]=p[j];
				}
			}
			if(in_tri(p[i],tmp)){
				anss[i]=1;
				goto yes;
			}
		}
		
	}else{
		int s=0;
		for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			seg[++s]=L(p[i],p[j]);
	
		while(1){
			int x=rand()%s+1;
			int y=rand()%s+1;
			while(x==y)y=rand()%s+1;
			if(intersect(seg[x],seg[y])){
				anss[seg[x].a.id]=anss[seg[x].b.id]=0;
				anss[seg[y].a.id]=anss[seg[y].b.id]=1;
				goto yes;
			}
		}
	}
yes:	
	puts("YES");
	for(int i=1;i<=n;i++)
		putchar(anss[i]?'B':'A');
	puts("");
}
int main(){
srand(666);
	int T;
	cin>>T;
	while(T--)
		solve();
	return 0;
}
