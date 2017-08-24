#include<bits/stdc++.h>
using namespace std;
int main(){
	puts("1");
	int n=1e4;
	printf("%d\n",n);
	for(int i=2;i<=n;i++)
		printf("%d %d\n",1,i);
	
	for(int i=1;i<=n;i++)
		putchar(rand()%26+'a');
	puts("");
	for(int i=1;i<=sqrt(n);i++)
		putchar(rand()%26+'a');

	puts("");
	return 0;
}
