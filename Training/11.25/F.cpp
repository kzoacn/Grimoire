#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL mo=1e9+9;
const int maxn=333;

int tot;

struct mat{
	LL a[maxn][maxn];
	LL* operator[](int x){return a[x];}
	void cl(){
		memset(a,0,sizeof a);	
	}
	void unit(){
		for(int i=1;i<=tot;i++)
			a[i][i]=1;
	}
};

mat operator*(mat &A,mat &B){
	static mat C;
	C.cl();
	for(int k=1;k<=tot;k++)
	for(int i=1;i<=tot;i++)
	for(int j=1;j<=tot;j++){
		C[i][j]=(C[i][j]+A[i][k]*B[k][j])%mo;
	}
	return C;
}
mat operator^(mat x,int k){
	static mat ans;
	ans.cl();ans.unit();
	for(;k;k>>=1){
		if(k&1)ans=ans*x;
		x=x*x;
	}
	return ans;
}
mat M;

int mp[10][10];
bool check(int n,int m){
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)if(mp[i][j])
	for(int ii=1;ii<=n;ii++)
	for(int jj=1;jj<=m;jj++)if(mp[ii][jj]){
		int d1=abs(i-ii);
		int d2=abs(j-jj);
		if((d1==1&&d2==2)||(d1==2&&d2==1))
			return false;
	}
	return true;
}
int id[1<<15];
int main(){
	int T;cin>>T;
	while(T--){
		tot=0;
		int n,m;
		cin>>n>>m;
		
		//n=1 || m=1
		
		for(int S1=0;S1<(1<<n);S1++)
		for(int S2=0;S2<(1<<n);S2++){
			memset(mp,0,sizeof mp);
			for(int i=0;i<n;i++)
				mp[i+1][1]=(S1>>i&1);
			for(int i=0;i<n;i++)
				mp[i+1][2]=(S2>>i&1);
			if(check(n,2))
				id[S1|(S2<<n)]= ++tot;
			else
				id[S1|(S2<<n)]= 0;
		}
		
		
		M.cl();
		for(int S1=0;S1<(1<<n);S1++)
		for(int S2=0;S2<(1<<n);S2++)
		for(int S3=0;S3<(1<<n);S3++){
			if(!id[S1|(S2<<n)])continue;
			if(!id[S2|(S3<<n)])continue;
			memset(mp,0,sizeof mp);
			
			for(int i=0;i<n;i++)
				mp[i+1][1]=(S1>>i&1);
			for(int i=0;i<n;i++)
				mp[i+1][2]=(S2>>i&1);
			for(int i=0;i<n;i++)
				mp[i+1][3]=(S3>>i&1);
			if(check(n,3)){
				M[id[S1|(S2<<n)]][id[S2|(S3<<n)]]=1;
			}
		}
		
		
		long long ans=0;
		
		if(m==1){
			ans=(1<<n);
		}else if(m==2){
			ans=tot;
		}else{
			mat A=M^(m-2);
			for(int i=1;i<=tot;i++){
				for(int j=1;j<=tot;j++)
					ans=(ans+A[i][j])%mo;
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
