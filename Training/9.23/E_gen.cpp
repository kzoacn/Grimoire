#include<bits/stdc++.h>
using namespace std;
int main(){
srand(time(0));
	puts("1");
	int n=100;
	printf("%d\n",n);
	for(int i=1;i<=n;i++)
		printf("%d %d\n",rand()%10000,rand()%10000);
	return 0;
}
