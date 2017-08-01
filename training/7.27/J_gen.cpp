#include<bits/stdc++.h>
using namespace std;
int main(){
	int n=500;
	puts("1");
	cout<<n<<endl;
	int w=200;
	for(int i=1;i<=n;i++)
		printf("%d %d %d %d\n",rand()%w,rand()%w,rand()%w,rand()%w);
	return 0;
}
