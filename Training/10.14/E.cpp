#include<bits/stdc++.h>
using namespace std;

set<int>path(int u,int top){
	set<int>S;
	for(;(u>>1)>top;u>>=1){
		S.insert(u^1);
	}
	return S;
}

int main(){
	int a,b;
	cin>>a>>b;
	
	set<int>A,B;
	for(int u=a;u;u/=2){
		A.insert(u);
	}
	int LCA=0;
	for(int u=b;u;u/=2){
		if(A.count(u)){
			LCA=u;
			break;
		}
	}
	if(LCA==a||LCA==b){
		puts("-1");
		return 0;
	}
	set<int>s1,s2,s3,S;
	s1=path(a,LCA);
	s2=path(b,LCA);	
	s3=path(LCA,0);
	for(auto x:s1)S.insert(x);
	for(auto x:s2)S.insert(x);
	for(auto x:s3)S.insert(x);
	S.insert(a);
	S.insert(b);
	int cnt=0;
	for(auto x:S){
		printf("%d%c",x," \n"[(++cnt==S.size())]);
	}
	return 0;
}
