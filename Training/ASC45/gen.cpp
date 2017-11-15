#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n=1e5;
int w=1e5;
double xx[maxn];
int main(){
	printf("%d\n",n);
	int a=rand()%w,b=rand()%w;
	if(a>b)swap(a,b);
	printf("%d %d\n",a,b);


	printf("0.5\n");

	for(int i=1;i<n;i++){
		xx[i]=rand()%w+10.0/i;
	}

	sort(xx+1,xx+n);
	xx[0]=0;
	xx[n]=w;
	for(int i=0;i<=n;i++)
		printf("%f %f\n",xx[i],(double)(rand()%w));
	

	puts("0");
	return 0;
}
