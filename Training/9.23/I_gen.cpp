#include<bits/stdc++.h>
using namespace std;
int main(){
	puts("1");
	int k=17;
	int n=1<<k;
	cout<<k<<endl;
	for(int i=0;i<(1<<k);i++)
		printf("%d%c",rand()%2000-1000," \n"[i+1==(1<<k)]);
	int q=1<<k;
	cout<<q<<endl;
	while(q--){
		printf("%d %d %d\n",rand()%2+1,rand()%n+1,rand()%n+1);
	}
}
