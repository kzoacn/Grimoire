#include<bits/stdc++.h>
using namespace std;
const double eps=1e-9;
int sgn(double x){return (x>eps)-(x<-eps);}
struct P{
	double x,y;
	P(){}
	P(double _x,double _y):x(_x),y(_y){}
	P turn90(){return P(y,-x);}
	double len(){return sqrt(x*x+y*y);}
}p[55];
bool operator==(P a,P b){
	return sgn(a.x-b.x)==0 && sgn(a.y-b.y)==0;
}
P operator+(P a,P b){
	return P(a.x+b.x,a.y+b.y);
}
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
double operator*(P a,P b){
	return a.x*b.y-a.y*b.x;
}
double operator^(P a,P b){
	return a.x*b.x+a.y*b.y;
}
P operator*(double a,P p){
	return P(a*p.x,a*p.y);
}
P operator/(P p,double a){
	return P(p.x/a,p.y/a);
}
struct L{
	P a,b;
	P v(){return b-a;}
	L(){}
	L(P _a,P _b):a(_a),b(_b){}
};
double det(P a,P b,P c){
	return (b-a)*(c-a);
}
P intersect(P a,P b,P c,P d){
	double s1=det(a,b,c);
	double s2=det(a,b,d);
	return (s1*d-s2*c)/(s1-s2);
}
P intersect(L l1,L l2){
	return intersect(l1.a,l1.b,l2.a,l2.b);
}
P rot(P p,double rad){
	return P(p.x*cos(rad)-p.y*sin(rad),p.x*sin(rad)+p.y*cos(rad));
}
L midL(P a,P b){
	P p=(a+b)/2;
	P v=(b-a).turn90();
	return L(p,p+v);
}
int n,m,c;
int mp[55][55];
int nxt[55];
typedef long long LL;
LL pw(LL x,LL k,LL p=int(1e9)+7){
	LL ans=1;
	for(;k;k>>=1){
		if(k&1)ans=ans*x%p;
		x=x*x%p;
	}return ans;
}
LL G=0;
vector<LL>anss;
void Calc(P O,int x,int y){

	double theta = fabs(acos(((p[x]-O)^(p[y]-O))/(p[x]-O).len()/(p[y]-O).len()));

	if(sgn(theta)){
		if(sgn((p[x]-O)*(p[y]-O))>0)
			theta=theta;
		else theta=-theta;
	}//else theta=0;
	for(int i=1;i<=n;i++)nxt[i]=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)if(O+rot(p[i]-O,theta)==p[j]){
			nxt[i]=j;
			break;
		}
	}
	
	for(int i=1;i<=n;i++)
		if(!nxt[i])
			return;
	
	//cerr<< x << " " << y <<endl;
	//for(int i=1;i<=n;i++)
	//	printf("%d%c",nxt[i]," \n"[i==n]);
			
	//assert(nxt[x]==y);
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(mp[i][j] && !mp[nxt[i]][nxt[j]])
				return ;
		}
	}	
	
	//cerr << "that is ok" <<endl;
	G++;
	static int vis[55];
	static int OneMoreTimeOneMoreChance=0;
	OneMoreTimeOneMoreChance++;
	int r=0;
	for(int i=1;i<=n;i++){
		int x=i;
		if(vis[x]!=OneMoreTimeOneMoreChance){
			r++;
			while(vis[x]!=OneMoreTimeOneMoreChance){
				vis[x]=OneMoreTimeOneMoreChance;
			
				x=nxt[x];
			}
		}		
	}
	anss.push_back(r);
	//for(int i=1;i<=n;i++)
	//	printf("%d%c",nxt[i]," \n"[i==n]);
	//printf("r=%d\n",r);
}
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		G=0;
		anss.clear();
		scanf("%d%d%d",&n,&m,&c);
		double sumx=0,sumy=0;
		
		for(int i=1;i<=n;i++){
			scanf("%lf%lf",&p[i].x,&p[i].y);		
			sumx+=p[i].x;
			sumy+=p[i].y;
		}
		
		
		
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			mp[i][j]=0;
		
		for(int i=1;i<=m;i++){
			int u,v;scanf("%d%d",&u,&v);
			mp[u][v]=mp[v][u]=1;
		}
		if(n==1){
			printf("%d\n",c);
			continue;
		}
		if(n==2){
			printf("%d\n",c*(c+1)/2);
			continue;
		}
		
		P O = P(sumx/n,sumy/n);
		//fprintf(stderr,"(%.3f,%.3f)\n",O.x,O.y);
		
		int rt=1;
		for(int i=1;i<=n;i++) 
			if(!(p[i]==O)){
				rt=i;
				break;
			}
		
		
		for(int i=1;i<=n;i++){
			if(O==p[rt] || O==p[i]) continue;
			Calc(O,rt,i);
		}
		
		
		const int mo=1e9+7;
		LL ans=0;
		for(int i=0;i<anss.size();i++){
			ans=ans+pw(c,anss[i],mo);
			ans%=mo;
		}		
		ans=ans*pw(G,mo-2,mo);
		cout << ans%mo <<endl;
		//printf("%lld\n",ans%mo);
	}
	return 0;
}
