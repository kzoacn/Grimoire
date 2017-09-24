#include<bits/stdc++.h>
using namespace std;
int n;
int a[10001];
int main(){
	while(scanf("%d",&n)==1){
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		if(n==1){
			printf("%.8f\n",(double)a[1]);
		}else{
			int sum=0;
			for(int i=2;i<n;i++)
				sum+=a[i];
			printf("%.8f\n",(a[1]+a[n])/2.0+sum/3.0);
		}
	}
	return 0;
}
