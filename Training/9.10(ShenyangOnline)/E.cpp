#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL mo=998244353;
struct mat{
	LL a[2][2];
	LL *operator[](int x){return a[x];}
	
	void cl(){memset(a,0,sizeof a);}
	void un(){
		for(int i=0;i<2;i++)
			a[i][i]=1;
	}
};
mat operator*(mat A,mat B){
	mat C;
	C.cl();
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			for(int k=0;k<2;k++){
				C[i][j]+=A[i][k]*B[k][j]%mo;
				while(C[i][j]>=mo)C[i][j]-=mo;
			}
		}
	}
	return C;
}

mat operator^(mat x,int k){
	mat ans;
	ans.cl();
	ans.un();
	for(;k;k>>=1){
		if(k&1)ans=ans*x;
		x=x*x;
	}
	return ans;
}

int main(){
	int k;
	while(cin>>k){
		mat A;
		A[0][0]=1;A[0][1]=1;
		A[1][0]=1;A[1][1]=0;
		
		A=A^(2*k+2);
		
		printf("%lld\n",(A[0][0]-1+mo)%mo);
		
	}
	return 0;
}
