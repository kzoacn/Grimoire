#include<bits/stdc++.h>
using namespace std;

double dp[51][51][51];
int vis[51][51][51];
int n,a,b,c,d;

double logfac[100];
double logC(int n,int m){
	return logfac[n]-logfac[m]-logfac[n-m];
}


void dfs(int m,int a,int b){
	if(vis[m][a][b])
		return ;
	if(m==0&&(a==0||b==0)){
		dp[m][a][b]=0;
		return ;
	}
	vis[m][a][b]=1;
	
	double &ans=dp[m][a][b];
	double selfprob=0;
	ans=0;
	
	int rest=n-m-a-b;
	for(int x1=0;x1<=m&&x1<=d;x1++){
		for(int x2=0;x2<=a&&x1+x2<=d;x2++){
			for(int x3=0;x3<=b&&x1+x2+x3<=d;x3++){
				if(d-(x1+x2+x3)>rest)continue;
				
				double prob=0;
				
				prob=logC(m,x1)+logC(a,x2)+logC(b,x3)+logC(rest,d-(x1+x2+x3))-logC(n,d);
				
				prob=exp(prob);
				
				//cerr<<x1<<" "<<x2<<" "<<x3<<" "<<prob<<endl;
				
				//C(d;x1,x2,x3)/C(n,d)
				if(x1==0&&x2==0&&x3==0){
					selfprob=prob;
					continue;
				}
				dfs(m-x1,a-x2,b-x3);
				ans+=prob*dp[m-x1][a-x2][b-x3];
			}
		}
	}
	ans++;
	ans/=(1-selfprob);
	
	//cerr<<m<<" "<<a<<" "<<b<<endl;
	//cerr<<ans<<endl;
}

set<int>A,B;

int main(){
	logfac[0]=log(1);
	for(int i=1;i<100;i++)
		logfac[i]=logfac[i-1]+log(i);
		
		

	cin>>n>>d>>c;
	int a=c,b=c;
	for(int i=0;i<a;i++){
		int x;cin>>x;
		A.insert(x);
	}
	for(int i=0;i<b;i++){
		int x;cin>>x;
		B.insert(x);
	}
	
	int ins=0;
	for(auto x:A)
		if(B.count(x))
			ins++;
	dfs(ins,a-ins,b-ins);
	//dfs(0,1,1);
	//return 0;
	/*for(int i=0;i<=1;i++)
	for(int j=0;j<=9;j++)
	for(int k=0;k<=9;k++)
		printf("dp[%d][%d][%d]=%.5f\n",i,j,k,dp[i][j][k]);
	*/
	printf("%.10f\n",dp[ins][a-ins][b-ins]);	
	return 0;
}
