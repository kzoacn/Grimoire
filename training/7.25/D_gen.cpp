#include<bits/stdc++.h>
using namespace std;
int main(){
	int n=5e5,m=5e5;
	for(int i=1;i<=n;i++)
		putchar(rand()%2+'a');puts("");
	cout<<m<<endl;
	while(m--){
		int l=rand()%n+1,r=rand()%n+1;
		if(l>r)swap(l,r);
		printf("%d %d\n",l,r);
	}
	return 0;
}
