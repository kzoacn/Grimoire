#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int n;

LL fib[1111][1111];



int solve(int n){


	memset(fib,0,sizeof fib);
	fib[1][1]=fib[1][2]=1;
	for(int i=3;i<=100;i++)	
		fib[1][i]=fib[1][i-1]+fib[1][i-2]*2;
	for(int i=2;i<=20;i++){
		for(int j=1;j<=50;j++){
			for(int k=j;k<=j+n-1;k++)
				fib[i][j]+=fib[i-1][k];
		}
	}
	
	for(int i=1;i<=7;i++)
		printf("%lld%c",fib[i][1]," \n"[i==7]);
	
	return 0;
}
int main(){
	for(int i=1;i<=15;i++){
		cout<<i<<endl;
		solve(i);
	}
}
