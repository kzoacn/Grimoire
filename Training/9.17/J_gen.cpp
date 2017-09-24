#include<bits/stdc++.h>
using namespace std;
int main(){
	puts("1");
	int n=1e5;
	printf("%d\n",n);
	for(int i=1;i<=n;i++)
		printf("%d%c",rand()%10000," \n"[i==n]);
	return 0;
}
