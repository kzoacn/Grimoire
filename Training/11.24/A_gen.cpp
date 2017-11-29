#include<bits/stdc++.h>
using namespace std;
int main(){
	srand(time(0));

	int T=10;
	while(T--){
		int n=rand()%10+1;
		int m=rand()%10+1;
		printf("%d %d %d %d\n",n,m,rand()%n+1,rand()%m+1);
	}

	return 0;
}
