#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
int main(){
	srand(time(0)^getpid());
	int w=100;
	int n=20;
	cout<<n<<endl;
	for(int i=1;i<=n;i++)
		printf("%d\n",rand()%w+1);
	printf("%d %d\n",rand()%(w*n),rand()%(w*n));
//	printf("%d %d\n",0,0);
	return 0;
}
