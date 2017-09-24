#include<bits/stdc++.h>
using namespace std;
int n;
int w=1e6;
int main(){
	puts("2");
	int T=2;
	while(T--){
	n=2e4;
	
	cout<<n<<endl;
	for(int i=1;i<=n;i++)
		printf("%d %d\n",rand()%w,rand()%w);
	
	int R=10;
	cout<<R<<endl;
	while(R--){
		int b=20;
		int curx=0,cury=0;
		cout<<b<<endl;
		for(int i=0;i+1<b;i++){
			printf("%d %d\n",curx,cury);
			curx+=rand()%20000+12;
			cury+=rand()%10+1;
		}
		cury+=4000;
		printf("%d %d\n",curx,cury);
		
		int m=5000;
		cout<<m<<endl;
		while(m--)
			printf("%d %d\n",rand()%w,rand()%w);
			
	}
	}
	

	return 0;
}
