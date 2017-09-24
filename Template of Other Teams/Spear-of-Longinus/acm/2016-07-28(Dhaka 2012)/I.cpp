#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=51;
const int inf=1e9;
int f[55][55][2512];
int n,m;

const double eps = 1e-8;

struct P{
	int x,y;
	double k(){
		if(x==0) {
			return 1e9;
		} else {
			return 1. * y / x;
		}
	}
}p[55];
bool operator<(P a,P b){
	return a.k() > (b.k() + eps);
}
int main(){
	int T;
	scanf("%d",&T);
	for(int t=1;t<=T;t++){
		scanf("%d%d",&n,&m);
		int sum=0;
		for(int i=1;i<=n;i++){
			scanf("%d%d",&p[i].x,&p[i].y);
			sum+=p[i].y;
		}
		sort(p+1,p+1+n);
		
		for(int i=0;i<=n;i++)
			for(int j=0;j<=m;j++)
				for(int k=0;k<=sum;k++)
					f[i][j][k]=-inf;
		
		f[0][0][0]=0;
		for(int i=0;i<n;i++) {
			for(int j = 0; j <= m; j++) {
				for(int k = 0; k <= sum; k++) {
					if(f[i][j][k] == -inf) {
						continue;
					}
					f[i + 1][j][k] = max(f[i + 1][j][k], f[i][j][k]);
				}
			}
 			for(int j=0;j<m;j++)
				for(int k=0;k<=sum;k++)
					if(f[i][j][k]!=-inf){
						if(k+p[i+1].y<=sum)
							f[i+1][j+1][k+p[i+1].y]=max(f[i+1][j+1][k+p[i+1].y],f[i][j][k]+2*k*p[i+1].x+p[i+1].x*p[i+1].y);
					}
		}
		int Max = -inf;
		for(int i = 0; i <= sum; i++) {
			Max = max(Max, f[n][m][i]);
		}
		printf("Case %d: %d\n",t, Max);
	}
	return 0;
}
