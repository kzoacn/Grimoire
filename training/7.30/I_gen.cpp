#include<bits/stdc++.h>
using namespace std;
int main(){
	int n=1e5;
	puts("1");
	printf("%d\n",n);
	for(int i=1;i<=n;i++)
		printf("%d ",int(rand()%int(1e4)+8e4));
	puts("");
	return 0;
}
