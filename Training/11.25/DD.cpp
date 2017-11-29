#include<bits/stdc++.h>
#define A first
#define B second
using namespace std;
typedef pair<double,double> expr;
const int maxn=233;

typedef double LD;
const LD eps=1e-9;
LD A[maxn][maxn];


LD a,b,c,d,r;
int n,m;

map<int,int>vis;
map<int,expr>E;
int start=0;
expr f(int n){
	//cerr<<n<<endl;
	if(vis[n]){
		start=n;
		return expr(1,0);
	}
	
	vis[n]=1;
	int nxt;
	double t=(double)n/m;
	expr ep;
	if(n<=0){
		nxt=-m-2*n;
		//fprintf(stderr,"%.5fx+%.5f\n",(b+r*t*t)/r,a/r);
		ep=f(nxt);	
		ep.A=ep.A*(b+r*t*t)/r;
		ep.B=ep.B*(b+r*t*t)/r+a/r;
	}else{
		nxt=m-2*n;
		//fprintf(stderr,"%.5fx+%.5f\n",(d+r*t*t)/r,c/r);
		ep=f(nxt);
		ep.A=ep.A*(d+r*t*t)/r;
		ep.B=ep.B*(d+r*t*t)/r+c/r;
	}
	return E[n]=ep;
}

int main(){
	int T;cin>>T;
	while(T--){
		cin>>n>>m>>a>>b>>c>>d>>r;
		
		vis.clear();		
		E.clear();
		f(n);
		double x;
//		E[start].A*x+E[start].B=x
		x=E[start].B/(1-E[start].A);
		double ans=E[n].A*x+E[n].B;
		printf("%.20f\n",ans);
	}
	return 0;
}
