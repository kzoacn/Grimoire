#include<bits/stdc++.h>
using namespace std;
int main(){

	int n=5,q=5;
	
	printf("%d %d\n",n,q);
	
	for(int i=2;i<=n;i++){
		if(rand()%20000){
			printf("%d %d\n",i,i-1);
		}else{
			printf("%d %d\n",i,rand()%(i-1)+1);
		}
	}
	
	for(int i=1;i<=n;i++)
		printf("%d%c",rand()%10000," \n"[i==n]);

	while(q--){
		printf("%d %d %d\n",rand()%n+1,rand()%n+1,rand()%n+1);
	}

	return 0;
}
