#include<bits/stdc++.h>
using namespace std;
const int maxn=133;
int fa[maxn];

int find(int x){
	return fa[x]==x ? x :fa[x]=find(fa[x]);
}
int n,D;
int d[maxn][maxn],a[maxn];
bool test(int a[]){
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++){
		if(a[i]&&a[j]&&d[i][j]<=D){
			fa[find(i)]=find(j);
		}
	}
	for(int i=1;i<=n;i++)if(a[i]){
		if(find(1)!=find(i))
			return false;
	}
	
	
	for(int i=1;i<=n;i++)if(!a[i]){
		bool flag=false;
		for(int j=1;j<=n;j++)if(a[j]){
			if(d[i][j]*2<=D)
				flag=true;
		}
		if(!flag)
			return false;
	}
	
	return true;
}
int sqr(int x){return x*x;}
int main(){
	while(scanf("%d%d",&n,&D)==2){
		static int x[maxn],y[maxn];
		for(int i=1;i<=n;i++)
			scanf("%d%d",&x[i],&y[i]);
		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			d[i][j]=ceil(sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j])));
		}
		
		for(int i=1;i<=n;i++)
			a[i]=1;
		if(!test(a)){
			puts("-1");
			continue;
		}
		for(int i=n;i>=2;i--){
			a[i]=0;
			if(!test(a))
				a[i]=1;
		}
		bool lead=0;
		for(int i=n;i>=1;i--){
			if(a[i]==1)lead=1;
			if(lead)
				printf("%d",a[i]);
		}
		puts("");
	}
	return 0;
}
