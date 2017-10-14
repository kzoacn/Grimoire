#include<bits/stdc++.h>
#define deb(x) cerr<<#x" = "<<x<<endl;
using namespace std;
typedef long long LL;
int x[50];
int d,h;
set<LL>S;
LL C[50][50];
LL ans;
int curh,sum;
void dfs(int dep){

	//deb(dep);
	//deb(curh);
	//deb(sum);
	if(dep==d+1){
		if(sum==h)
			S.insert(ans);
		return ;
	}
	for(int i=0;i<=x[dep-1];i++){
		x[dep]=i;
		sum+=i;
		//deb(i);
		int low,hig;
		low=sum;
		hig=sum+(d-dep)*i;
		//deb(low);
		//deb(hig);
		if(low<=h&&h<=hig){
			ans=ans*C[curh][i];
			
			//deb(C[curh][i]);
			
			curh-=i;
			dfs(dep+1);
			curh+=i;
			ans=ans/C[curh][i];
		}
		sum-=i;
	}
}


int main(){

	for(int i=0;i<50;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++){
			C[i][j]=C[i-1][j]+C[i-1][j-1];
		}
	}


	cin>>d>>h;
	h--;
	
	curh=h;
	x[0]=h;
	ans=1;
	dfs(1);
	
//	cerr<<S.size()<<endl;
	for(auto x:S)
		printf("%lld\n",x);
	return 0;
}
