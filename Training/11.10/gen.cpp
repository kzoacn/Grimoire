#include<bits/stdc++.h>
using namespace std;
int main(){

	puts("1");
	int n=200,m=200;

	static int b[222][222];
	cout<<n<<" "<<m<<endl;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
		b[i][j] =rand()%40+1;
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
		printf("%d%c",rand()%b[i][j]," \n"[j==m]);
	for(int i=1;i<=n;i++)
	for(int j=1;j<=m;j++)
		printf("%d%c",b[i][j]," \n"[j==m]);


	int q=5e5;
	cout<<q<<endl;
	while(q--){
		int x1,y1,x2,y2;
		x1=rand()%n+1;
		x2=rand()%n+1;
		y1=rand()%m+1;
		y2=rand()%m+1;
		if(x1>x2)swap(x1,x2);
		if(y1>y2)swap(y1,y2);
		printf("%d %d %d %d\n",x1,y1,x2,y2);
	}
	return 0;
}
