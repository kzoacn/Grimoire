#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int main(){
srand(time(0)^getpid());
	puts("1");
	int n=50,m=rand()%40;
	printf("%d %d\n",n,m);
	int w=rand()%n+2;
	while(m--)
		printf("%d %.2f\n",rand()%n+1,rand()/double(RAND_MAX)/w);
	for(int i=2;i<=n;i++)
		printf("%d %d\n",i,rand()%(i-1)+1);
	return 0;
}
