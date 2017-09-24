#include<bits/stdc++.h>
using namespace std;
int main(){
	int T=1;
	cout<<T<<endl;
	while(T--){
		int n=1e5;
		printf("%d\n",n);
		for(int i=1;i<=n;i++)
			printf("%d%c",rand()%int(1e8)," \n"[i==n]);
		for(int i=1;i*2<=n;i++){
			printf("%d %d\n",i,i*2);
			if(i*2+1<=n)
				printf("%d %d\n",i,i*2+1);
		}
	}
	return 0;
}
