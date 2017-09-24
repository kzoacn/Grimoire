#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
const int maxn=110;
const int inf=1e9;
int n,s,t;
double A[maxn][maxn];
double Gauss(){
	int r,k;
	for(int i=0;i<n;i++){
		r=i;
		for(int j=i+1;j<n;j++)
			if(fabs(A[j][i])>fabs(A[r][i]))r=j;
		if(r!=i)
			for(int j=0;j<=n;j++)swap(A[i][j],A[r][j]);
		for(int k=i+1;k<n;k++){
			double f=A[k][i]/A[i][i];
			for(int j=i;j<=n;j++)
				A[k][j]-=f*A[i][j];
		}
	}
	
	for(int i=n-1;i>=0;i--){
		for(int j=i+1;j<n;j++)
			A[i][n]-=A[j][n]*A[i][j];
		A[i][n]/=A[i][i];
	}
	return A[s-1][n];
}
int a[maxn][maxn],mp[maxn][maxn],b[maxn][maxn];
int sum[maxn],deg[maxn],deg2[maxn];
int sum2[maxn];
int p[maxn];
int main(){
	while(scanf("%d%d%d",&n,&s,&t)==3){
		if(!n)break;
		
		for(int i=1;i<=n;i++){
			sum[i]=deg[i]=0;
			sum2[i]=deg2[i]=0;
			for(int j=1;j<=n;j++){
				mp[i][j]=inf;
				b[i][j]=0;
			}
			mp[i][i]=0;
		}
		for(int i=1;i<=n;i++)	
			scanf("%d",&p[i]);
		
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
				scanf("%d",&a[i][j]);
				
				if(a[i][j]){
					deg[i]++;
					sum[i]+=a[i][j];
				}
				
				if(i!=j&&a[i][j]){
					mp[i][j]=a[i][j];
				}
			}
		
		
		
		for(int k=1;k<=n;k++)
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++){
					if(mp[k][j]!=inf&&mp[i][k]!=inf)
					mp[i][j]=min(mp[i][j],mp[i][k]+mp[k][j]);
				}	
		
		if(mp[s][t]>=inf){
			puts("impossible");
			continue;
		}
		
		
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
			
				if(i==j)continue;
			
				if(a[i][j])
				if(a[i][j]+mp[j][t]==mp[i][t]){
					b[i][j]=a[i][j];
					deg2[i]++;
					sum2[i]+=a[i][j];
				}
			
			}
		
		
		
		for(int i=0;i<=n;i++)
			for(int j=0;j<=n;j++)
				A[i][j]=0;
		for(int i=1;i<=n;i++){
			
		
			if(i==t){
				A[i-1][n]=0;
				A[i-1][i-1]=1;
			}else{
				if(!p[i]){
					for(int j=1;j<=n;j++)if(a[i][j]){
						A[i-1][j-1]=1;
					}
					A[i-1][i-1]+=-deg[i];
					A[i-1][n]=-sum[i];
				}else{
					for(int j=1;j<=n;j++)if(b[i][j]){
						A[i-1][j-1]=1;
					}
					A[i-1][i-1]+=-deg2[i];
					A[i-1][n]=-sum2[i];
				}
			}
		}
		
		
		//cerr<<"seg"<<endl;
		
		double ans=Gauss();
		printf("%.10f\n",ans);
	}	
	return 0;
}
