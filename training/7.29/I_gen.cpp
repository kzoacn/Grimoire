#include<bits/stdc++.h>
using namespace std;
int main(){
	int n=1000;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==1&&j==1)putchar('@');
			else putchar('+');
		}
		puts("");
	}
	puts("$");

	return 0;
}
