#include<bits/stdc++.h>
using namespace std;
int main(){
	int n=10;
	cout<<n<<endl;
	for(int i=1;i<=n;i++)
		printf("%d%c",rand()%n+1," \n"[i==n]);
	for(int i=1;i<=n;i++)
		printf("%d%c",rand()%n+1," \n"[i==n]);
	puts("0");
	return 0;
}
