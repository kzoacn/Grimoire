#include<bits/stdc++.h>
using namespace std;
int main(){
	puts("1");
	int n=5e4,m=200;
	printf("%d %d\n",n,m);
	for(int i=2;i<=n;i++)
		printf("%d %d\n",i,rand()%(i-1)+1);
	return 0;
}
