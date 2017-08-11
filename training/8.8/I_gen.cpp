#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int main(){
srand(time(0)^getpid());
	int n=300,m=1000;
	puts("1");
	printf("%d %d\n",n,m);
	int w=500;
	for(int i=1;i<=n;i++)
		printf("%d %d\n",rand()%w,rand()%w);
	
	for(int i=1;i<=m;i++)
		printf("%d %d %d %d\n",rand()%w,rand()%w,rand()%w,rand()%w);
	
	return 0;
}

