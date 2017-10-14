#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=222;
int mo;
LL pw(LL x,LL k,LL p=::mo){
	LL ans=1;
	for(;k;k>>=1){
		if(k&1)ans=ans*x%mo;
		x=x*x%mo;
	}
	return ans;
}

LL inv(LL x,LL p=::mo){
	return pw(x,p-2,p);
}

int n,m;
int b[maxn][maxn];
int a[maxn][maxn];

int Gauss(){
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++){
		a[i-1][j-1]=(b[i][j]%mo+mo)%mo;
	}
	
	int n=::m,m=::n;
	
	int r,now=-1;
	int ans=0;
	for(int i=0;i<n;i++){
		r=now+1;
		for(int j=now+1;j<m;j++){
			if(a[j][i]){
				r=j;
				break;
			}
		}
		if(!a[r][i])continue;
		now++;
		ans++;
		if(r!=now)
			swap(a[r],a[now]);
		for(int k=now+1;k<m;k++){
			LL t=a[k][i]*inv(a[now][i])%mo;
			for(int j=0;j<n;j++)
				a[k][j]=(a[k][j]-1ll*t*a[now][j]%mo+mo)%mo;
		}
	}
	
	return ans;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
			scanf("%d",&b[i][j]);
	}
	/*if(n>m){
		static int tmp[maxn][maxn];
		for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			tmp[i][j]=b[j][i];
		swap(n,m);
		for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			b[i][j]=tmp[i][j];
	}*/
	int r=0;
	mo=1e9+7;
	
	r=max(r,Gauss());
	
	mo=148898719;
	
	r=max(r,Gauss());
	cout<<r<<endl;
	return 0;
}
