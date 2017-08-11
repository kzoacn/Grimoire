#include<bits/stdc++.h>
using namespace std;
int n,m;
int main(){
freopen("H.in","r",stdin);
	cin>>m>>n;
	int ans=0;
	for(int i=0;i<=m;i++){
		for(int j=i;j<=m;j++){
			for(int k=j;k<=m;k++){
				if(i*i+j*j==k*k)
					ans++;
			}
		}
	}
	ans+=(n-2)*(m+1);
	
	cout<<ans<<endl;
	return 0;
}
