#include<bits/stdc++.h>
using namespace std;

const int maxn=33;
int a[maxn][maxn],b[maxn][maxn];

int n;
void rot(){
	static int tmp[maxn][maxn];
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
		tmp[n-j+1][i]=b[i][j];
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
		b[i][j]=tmp[i][j];
}
int calc(){
	int ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			ans+=(a[i][j]==b[i][j]);
	return ans;
}
int main(){
	while(scanf("%d",&n)==1&&n){
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				scanf("%d",&a[i][j]);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				scanf("%d",&b[i][j]);
		int ans=0;
		ans=max(ans,calc());
		rot();
		ans=max(ans,calc());
		rot();
		ans=max(ans,calc());
		rot();
		ans=max(ans,calc());
		rot();
		cout<<ans<<endl;
	}
	return 0;
}
