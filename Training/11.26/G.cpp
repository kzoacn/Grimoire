#include<bits/stdc++.h>
using namespace std;
const int maxn=33;
char mp[maxn][maxn];
int n;
const double eps=1e-9;
typedef pair<int,int> Pos;
#define X first
#define Y second
struct P{
	double x,y;
	void read(){
		scanf("%lf%lf",&x,&y);
	}
	P(){}
	P(double _x,double _y):x(_x),y(_y){}
	P(Pos p){
		x=p.X;
		y=p.Y;
	}
	double len(){return sqrt(x*x+y*y);}
	P norm(){
		return P(x/len(),y/len());
	}
}p[3];
P operator-(P a,P b){
	return P(a.x-b.x,a.y-b.y);
}
P operator+(P a,P b){
	return P(a.x+b.x,a.y+b.y);
}
P operator*(P a,double b){
	return P(a.x*b,a.y*b);
}
P operator/(P a,double b){
	return P(a.x/b,a.y/b);
}
double operator*(P a,P b){
	return a.x*b.y-a.y*b.x;
}
int dir(P p,P a,P b){
	double t=(p-a)*(b-a);
	if(fabs(t)<eps)return 0;
	return t>0?1:-1;
}
bool intersect(P a1,P b1,P a2,P b2){
	if(dir(a1,a2,b2)*dir(b1,a2,b2)<0 && dir(a2,a1,b1)*dir(b2,a1,b1)<0)
		return true;
	return false;
}
bool inside(P pt,P* p){
	int cnt=0;
	for(int i=0;i<3;i++){
		cnt+=dir(pt,p[i],p[(i+1)%3]);
	}
	return abs(cnt)==3;
}
void bfs(Pos s){
	map<Pos,int>d;
	queue<Pos>q;
	q.push(s);
	d[s]=0;
	/*if(mp[0][0]=='#'){
		puts("-1");
		return ;
	}*/
	while(!q.empty()){
		Pos u=q.front();q.pop();
		const Pos dirc[8]={{0,1},{0,-1},{1,0},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};
		for(auto dr:dirc){
			Pos v(u.X+dr.X,u.Y+dr.Y);
			if(v.X<0||v.X>=n||v.Y<0||v.Y>=n||mp[v.X][v.Y]=='#')continue;
			int ok=1;
			int T=100;
			for(int i=0;i<3;i++){
				if(inside(u,p)||inside(v,p)||intersect(u,v,p[i],p[(i+1)%3]))
					ok=0;
				P uv=P(v)-P(u);
				for(int j=0;j<=T;j++){
					P pt=u+uv*j/T;
					if(inside(pt,p))
						ok=0;
				}
			}
			if(!ok)continue;
			if(d.count(v))continue;
			d[v]=d[u]+1;
			q.push(v);
		}
	}
	if(d.count({n-1,n-1})){
		printf("%d\n",d[{n-1,n-1}]);
	}else
		puts("-1");
}

int main(){
	while(scanf("%d",&n)==1){
		for(int i=0;i<3;i++)
			p[i].read();
			
			
		for(int y=n-1;y>=0;y--){
			scanf("%s",mp[y]);
		}
		bfs(Pos(0,0));
		
	}
	return 0;
}
