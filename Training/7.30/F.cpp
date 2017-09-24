#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL mo=1e9+7;

struct mat{
	LL a[3][3];
	LL *operator[](int x){return a[x];}
	
	void cl(){memset(a,0,sizeof a);}
	void unit(){
		for(int i=0;i<3;i++)	
			a[i][i]=1;
	}	
	void print(){
		for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			printf("%lld%c",a[i][j]," \n"[j==2]);
	}	
};
mat operator*(mat &a,mat &b){
	static mat c;c.cl();
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			for(int k=0;k<3;k++){
				c[i][j]=(c[i][j]+a[i][k]*b[k][j])%mo;
			}
		}
	}
	return c;
}
LL pw(LL x,LL k,LL p=::mo){
	LL ans=1%p;
	for(;k;k>>=1){
		if(k&1)ans=ans*x%p;
		x=x*x%p;
	}
	return ans;
}

mat pw(mat x,LL k){
	mat ans;ans.cl();ans.unit();
	for(;k;k>>=1){
		if(k&1)ans=ans*x;
		x=x*x;
	}
	return ans;
}

LL calcF(LL n){
	if(n==1)return 1;
	if(n==2)return 2;
	mat F;
	F[0][0]=0;F[0][1]=1;F[0][2]=0;
	F[1][0]=2;F[1][1]=1;F[1][2]=1;
	F[2][0]=0;F[2][1]=0;F[2][2]=1;
	
	F=pw(F,n-1);
	
	LL ans=0;
	ans+=F[0][0]*1+F[0][1]*2+F[0][2]*1;
	ans%=mo;
	
	return ans;
}

LL calcA(LL n,LL m){
	if(m==1)return 1;
	if(m==2)return calcF(n);
	mat A;A.cl();
	if(n%2==0){
		A[0][0]=(pw(2,n)+mo-1)%mo;A[0][1]=0;
		A[1][0]=0;A[1][1]=1;
	}else{
		A[0][0]=(pw(2,n)+mo-1)%mo;A[0][1]=(mo-calcF(n-1))%mo;
		A[1][0]=0;A[1][1]=1;
	}
//	A.print();
	
	A=pw(A,m-2);
	
//	A.print();
	
	LL ans=0;
	ans+=A[0][0]*calcF(n)+A[0][1];
	ans%=mo;
	
	return ans;
}

LL solve(LL n,LL m){
	if(n==1)return 1;
	
	return calcA(n,m);
}

int main(){

//	cout<<calcA(2,3)<<endl;
/*	for(int i=1;i<=5;i++)
		cout<<calcF(i)<<endl;
	puts("");	
	for(int i=1;i<=5;i++)
		cout<<calcA(3,i)<<endl;
	return 0;*/
/*
for(int i=1;i<=7;i++)
for(int j=1;j<=6;j++)
	printf("%lld%c",solve(i,j)," \n"[j==6]);

return 0;
*/	
	int T;cin>>T;
	while(T--){
		LL n,m;
		scanf("%lld%lld",&n,&m);
		printf("%lld\n",solve(n,m));
	}
	return 0;
}
