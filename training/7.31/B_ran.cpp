#include<bits/stdc++.h>
using namespace std;
int main(){
	int n=10;
	cout<<n<<endl;
	srand(time(0));
	while(n--)
		printf("%d %d\n",rand()%2000-1000,rand()%2000-1000);
	return 0;
}
