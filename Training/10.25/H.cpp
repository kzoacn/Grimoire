#include<bits/stdc++.h>
using namespace std;
const int maxn=450;
typedef long long LL;
const LL mo=1e9+7;
int n;
LL pw(LL x,LL k,LL mo=::mo){
	LL ans=1;
	for(;k;k>>=1){
		if(k&1)ans=ans*x%mo;
		x=x*x%mo;
	}
	return ans;
}

LL inv(LL x){return pw(x,mo-2,mo);}

LL A[maxn][maxn];


void print(){
	for(int i=1;i<=n;i++){
		for(int j=1;j<=2*n;j++)
			printf("%lld%c",A[i][j]," \n"[i==2*n]);
		puts("");
	}
	puts("");
}

LL Gauss(LL A[maxn][maxn],int n){
//	static LL A[maxn][maxn];
//	memcpy(A,_A,sizeof A);
	LL ans=1;
	for(int i=1;i<=n;i++){
		int r=0;
		for(int j=i;j<=n;j++){
			if(A[j][i]){
				r=j;break;
			}
		}
		if(!r)return 0;
		if(r!=i){
			swap(A[r],A[i]);
			ans=(mo-ans)%mo;
		}
		for(int j=i+1;j<=n;j++){
			LL t=A[j][i]*inv(A[i][i])%mo;
			for(int k=1;k<=n*2;k++){
				A[j][k]=(A[j][k]+mo-1ll*t*A[i][k]%mo)%mo;		
			}
		}
//		cerr<<"i="<<i<<endl;
//		print();
		ans=ans*A[i][i]%mo;
	}

	for(int i=n;i>=1;i--){
		LL t=inv(A[i][i]);
		for(int j=1;j<=n*2;j++)
			A[i][j]=A[i][j]*t%mo;
		for(int j=i-1;j>=1;j--){
			LL t=A[j][i];
			for(int k=1;k<=n*2;k++){
				A[j][k]=(A[j][k]+mo-t*A[i][k]%mo)%mo;
			}
		}
	}


	return ans;
}


int main(){
	mt19937 g(10086);
	while(scanf("%d",&n)==1&&n){
		for(int i=1;i<n;i++)
			for(int j=1;j<=n;j++)
				scanf("%lld",&A[i][j]);
		//FBI WARNING!!	
		for(int j=1;j<=n;j++)
			A[n][j]=g()%mo;

//		A[n][1]=133;A[n][2]=123;
		for(int i=1;i<=n;i++){
			for(int j=n+1;j<=n*2;j++){
				A[i][j]=0;
				if(i+n==j)A[i][j]=1;
			}
		}
//		print();
		LL det=Gauss(A,n);
//		print();

		for(int i=1;i<=n;i++)
			for(int j=n+1;j<=n*2;j++){
				A[i][j]=A[i][j]*det%mo;

				if((i+j-n)%2)
					A[i][j]=(mo-A[i][j])%mo;
			}
//		print();
//		cerr<<det<<endl;
		if(det==0){
			for(int i=1;i<=n;i++)
				printf("0%c"," \n"[i==n]);
		}else{
			for(int i=1;i<=n;i++)
				printf("%lld%c",A[i][n*2]," \n"[i==n]);
		}
	}
	return 0;
}
